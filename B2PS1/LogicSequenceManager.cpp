#include "Motor.h"

LogicBloc::LogicBloc(Texture* texture, Vector2f size, Vector2f position, Logic logicType) : logicType(logicType)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
	this->position = position;

	// initialise needClampMap
	for (int i = 0; i < 4; i++)
		needClampMap.insert(make_pair((HitDirection)i, false));
}

LogicBloc::LogicBloc(Texture* texture, Color color, Vector2f size, Vector2f position, Logic logicType) : logicType(logicType)
{
	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setFillColor(color);
	body.setPosition(position);
	this->position = position;

	// initialise needClampMap
	for (int i = 0; i < 4; i++)
		needClampMap.insert(make_pair((HitDirection)i, false));
}

void LogicBloc::CheckCollision(list<LogicBloc*>& logicBlocs)
{
	// les positions des differents endroits a tester
	int positions[4][2] =
	{
		{position.x + body.getSize().x / 2, position.y - 30},	// up
		{position.x + body.getSize().x / 2, position.y + body.getSize().y + 30},	// down

		{position.x - 30, position.y + body.getSize().y / 2},	// left
		{position.x + body.getSize().x + 30, position.y + body.getSize().y / 2}  // right
	};

	// pour le clamp
	map<HitDirection, LogicBloc*> compareCollidedMap = collidedMap;
	collidedMap.clear();

	for (int direction = 0; direction < 4; direction++)
	{
		Vector2f pos = Vector2f(positions[direction][0], positions[direction][1]);

	 	for (LogicBloc* logicBloc : logicBlocs)
		{
			if (logicBloc != this)
			{
				if (pos.x >= logicBloc->position.x && pos.x <= logicBloc->position.x + logicBloc->body.getSize().x &&
					pos.y >= logicBloc->position.y && pos.y <= logicBloc->position.y + logicBloc->body.getSize().y)
				{
					collidedMap.insert(make_pair((HitDirection)direction, logicBloc));
					
					// si l'element n'est pas deja clamp ou en cours de clamp
					if (compareCollidedMap[(HitDirection)direction] != logicBloc)
					{
						needClampMap[HitDirection::Left] = true;
						needClampMap[HitDirection::Right] = true;
					}
				}
			}
		}
	}

	// is end
	if (collidedMap.count(HitDirection::Left) == 1 && collidedMap.count(HitDirection::Right) == 0)
		sequencePosition = SequencePosition::End;

	// is intermediate
	if (collidedMap.count(HitDirection::Left) == 1 && collidedMap.count(HitDirection::Right) == 1)
		sequencePosition = SequencePosition::Intermediate;

	// is begin
	if (collidedMap.count(HitDirection::Left) == 0 && collidedMap.count(HitDirection::Right) == 1)
		sequencePosition = SequencePosition::Begin;
}

void LogicBloc::Draw()
{
	/*if (sequencePosition == SequencePosition::Intermediate)
	{
		for (auto itr = needClampMap.begin(); itr != needClampMap.end(); itr++)
		{
			// si il y a besoin d'un clamp
			if (itr->second && (itr->first == HitDirection::Right || itr->first == HitDirection::Left))
			{
				if (collidedMap[itr->first] != nullptr)
				{
					if (collidedMap[itr->first]->position.y < position.y)
						collidedMap[itr->first]->position.y++;

					if (collidedMap[itr->first]->position.y > position.y)
						collidedMap[itr->first]->position.y--;

					// si le logicBloc est clamp
					if (collidedMap[itr->first]->position.y == position.y)
						itr->second = false;
				}
			}
		}
	}*/

	body.setPosition(position);
	motor->window->draw(body);
}


/*PROTOTYPING pour ajouter manuelement des evenements logiques*/
void LogicSequenceManager::sendSequence(string code)
{
	if (code == "" || code == " ")
		return;

	string instruction = "";
	list<string> logicSequenceString = list<string>();
	for (unsigned i = 0; i < code.size(); i++)
	{
		if (code[i] == ' ')
		{
			logicSequenceString.push_back(instruction);
			instruction = "";
		}
		else
			instruction += code[i];

		if (i + 1 == code.size() && instruction != "")
			logicSequenceString.push_back(instruction);
	}

	list<Logic> logicSequence = list<Logic>();

	for (string logicString : logicSequenceString)
	{
		if (logicString == "brain" || logicString == "Brain")
			logicSequence.push_back(Logic(ElementType::Brain));
		else if (logicString == "wall" || logicString == "Wall")
			logicSequence.push_back(Logic(ElementType::Wall));
		else if (logicString == "is" || logicString == "Is")
			logicSequence.push_back(Logic(OperateurType::Is));
		else if (logicString == "and" || logicString == "And")
			logicSequence.push_back(Logic(OperateurType::And));
		else if (logicString == "stop" || logicString == "Stop")
			logicSequence.push_back(Logic(InstructionType::Stop));
		else if (logicString == "you" || logicString == "You")
			logicSequence.push_back(Logic(InstructionType::You));
		else if (logicString == "stop" || logicString == "Stop")
			logicSequence.push_back(Logic(InstructionType::Stop));


		// error manager
		else
		{
			cout << "--- Logic_Sequence Unexpected error at :" << endl;
			for (string s : logicSequenceString)
			{
				cout << s + " ";
				if (s == logicString)
				{
					cout << "<--" << endl;
					return;
				}
			}
		}
	}

	bool isValid = isSequenceValid(logicSequence);
	cout << "Sequence " << (isValid ? "valide" : "invalide") << endl;
	if (!isValid)
		return;

	applySequence(logicSequence);
}

void LogicSequenceManager::buildSequence(list<LogicBloc*>& logicBlocs)
{
	bool haveToClear = true;

	for (LogicBloc* logicBloc : logicBlocs)
	{
		if (logicBloc->sequencePosition == SequencePosition::End)
		{
			list<Logic> logicSequence = list<Logic>();
			LogicBloc* look = logicBloc;

			while (look != nullptr)
			{
				logicSequence.push_front(look->logicType);
				look = look->collidedMap[HitDirection::Left];
			}

			if (isSequenceValid(logicSequence))
			{
				if (haveToClear)
				{
					for (GameElement* gameElement : motor->level->GameElements)
						gameElement->logicInstructions.clear();
					haveToClear = false;
				}
				applySequence(logicSequence);
			}
		}
	}
}

bool LogicSequenceManager::isSequenceValid(list<Logic>& logicSequence)
{
	int i = 0;
	for (Logic logic : logicSequence)
	{
		if (i == 0 &&
			logic.logicType != LogicType::Element)
		{
			return false;
		}

		else if (i != 0 && i % 2 != 0 &&
			logic.logicType != LogicType::Operateur)
		{
			return false;
		}

		else if (i != 0 && i % 2 == 0 &&
			(logic.logicType != LogicType::Element && logic.logicType != LogicType::Instruction))
		{
			return false;
		}

		else if (i != 0 && i == logicSequence.size() &&
			logic.logicType != LogicType::Operateur)
		{
			return false;
		}
		i++;
	}

	return true;
}

void LogicSequenceManager::applySequence(list<Logic>& logicSequence)
{
	ElementType element = ElementType::None;

	bool isFistElement = true;

	for (Logic logic : logicSequence)
	{
		if (logic.logicType == LogicType::Element)
		{
			if (isFistElement)
			{
				element = logic.elementType;
				isFistElement = false;
			}
			else
			{
				morphGameElement(element, logic.elementType);
			}
		}

		if (logic.logicType == LogicType::Instruction)
		{
			for (GameElement* gameElement : motor->level->GameElements)
			{
				if (gameElement->type == element)
				{
					gameElement->logicInstructions.push_back(logic.instructionType);
				}
			}
		}
	}
}

void LogicSequenceManager::morphGameElement(ElementType oldType, ElementType newType)
{
	list<GameElement*> newGameElements = list<GameElement*>();

	for (GameElement* gameElement : motor->level->GameElements)
	{
		if (gameElement->type == oldType)
		{
			GameElement* newGameElement = nullptr;

			switch (newType)
			{
			case ElementType::Brain :
				newGameElement = new Brain(gameElement->getMotor(), gameElement->getPosition(), ElementType::Brain);
				break;
			case ElementType::Wall :
				newGameElement = new Wall(gameElement->getMotor(), gameElement->getPosition(), ElementType::Brain);
				break;
			}

			newGameElements.push_back(newGameElement);
		}
		else
			newGameElements.push_back(gameElement);
	}

	for (GameElement* gameElement : motor->level->GameElements) delete gameElement;
	motor->level->GameElements = newGameElements;
}