#include "LogicSequenceManager.h"
#include "Motor.h"

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
		if (logicString == "player" || logicString == "Player")
			logicSequence.push_back(Logic(ElementType::Player));
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

		if (i != 0 && i == logicSequence.size() &&
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
	bool isFistInstruction = true;

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
			switch (element)
			{
			case ElementType::Player:
				if (isFistInstruction) Player::LogicInstructions.clear();
				Player::LogicInstructions.push_back(logic.instructionType);
				break;
			case ElementType::Wall:
				/*if (isFistInstruction) Wall::LogicInstructions.clear();
				Wall::LogicInstructions.push_back(logic.instructionType);*/
				break;
			}

			if (isFistInstruction) isFistInstruction = false;
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
			case ElementType::Player:
				newGameElement = new Player();
				break;
			case ElementType::Wall:
				//newGameElement = new Wall();
				break;
			}

			newGameElement->position.x = gameElement->position.x;
			newGameElement->position.y = gameElement->position.y;
			newGameElement->motor = gameElement->motor;
			newGameElement->LoadSprites();
			newGameElement->Start();

			newGameElements.push_back(newGameElement);
		}
		else
		{
			newGameElements.push_back(gameElement);
		}
	}

	motor->level->GameElements = newGameElements;
}