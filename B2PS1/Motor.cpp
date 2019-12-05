#include "Motor.h"

Motor::Motor() {}
/*
Methode pour rajouter un nouvel element : (apres l'avoir rajouter dans une map)
- rajouter le template de code suivant a la suite du if :
if (csvLevel[y][x] == ##ID de l'element dans la map)
{
	## creation / ajout de parametres a l'element bref le code sp�cifique a element
	## /!\ doit etre instancier par un new /!\ # ex : Player* player = new Player() #

	level->GameElements.push_back( ##Element );
}
*/

void Motor::LoadLevel(string path)
{
	events.clear();
	delete level;
	isLevelEnded = false;
	level = new Level();

	try
	{
		ifstream fileStream = ifstream(path);
		vector<vector<int>> csvLevel = vector<vector<int>>();

		string line;
		while (getline(fileStream, line))
		{
			vector<int> levelRow = vector<int>();
			stringstream lineStream = stringstream(line);

			string cell;
			while (getline(lineStream, cell, ','))
				levelRow.push_back(stoi(cell));
			csvLevel.push_back(levelRow);
		}

		int xTilesSize = WindowWidth / csvLevel[0].size();
		int yTilesSize = WindowHeight / csvLevel.size();

		for (unsigned y = 0; y < csvLevel.size(); y++)
		{
			for (unsigned x = 0; x < csvLevel[y].size(); x++)
			{
				// utiliser un if car les case ne sont pas des bloc

				if (csvLevel[y][x] == 1)
				{
					Player* player = new Player();
					player->position.x = xTilesSize * x;
					player->position.y = yTilesSize * y;
					level->GameElements.push_back(player);
				}
			}
		}

		cout << "Successful Loaded Level " << path << endl;
	}
	catch (exception & ex)
	{
		cout << "Failed Loading Level : Level " << path << " not found " << ex.what() << endl;
	}
}

void Motor::Play(RenderWindow &window) {

	this->window = &window;

	for (GameElement* gameElement : level->GameElements)
	{
		gameElement->motor = this;
		gameElement->LoadSprites();
		gameElement->Start();
	}

	while (window.isOpen() && !isLevelEnded)
	{
		RefreshEvents();

		Event event;
		if (GetEvent(event, Event::Closed))
			window.close();
		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Escape) 
		{
			isLevelEnded = true;
		}
		/*PROTOTYPING pour tester si le code de verification des chaines d'instructions*/
		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::F)
		{
			cout << "Entrer un sequence logique : ";
			char tabCode[50];
			cin.getline(tabCode, 50);
			string code(tabCode);
			sendLogicalSequence(code);
		}

		window.clear(Color::Black);

		for (GameElement* gameElement : level->GameElements)
		{
			gameElement->ApplyLogicInstructions();
			gameElement->Update();
			gameElement->Draw();
		}

		window.display();
	}
}
/*
fonction voué a changer de place pour aller dans la class que gerera les evenements logiques
/*PROTOTYPING pour tester le code de verification des chaines d'instructions*/
void Motor::sendLogicalSequence(string code)
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

	bool isSequenceValid = isLogicSequenceValid(logicSequence);
	cout << "Sequence " << (isSequenceValid ? "valide" : "invalide") << endl;
	if (!isSequenceValid)
		return;

	applyLogicSequence(logicSequence);
}

//fonction voué a changer de place pour aller dans la class que gerera les evenements logiques
bool Motor::isLogicSequenceValid(list<Logic>& logicSequence)
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

void Motor::applyLogicSequence(list<Logic>& logicSequence)
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
				// appel de la fonction qui transforme des elements en d'autres
				cout << "Elements type " << (int)element << " is now type " << (int)logic.elementType << endl;
			}
		}
		if (logic.logicType == LogicType::Instruction)
		{
			switch(element)
			{
			case ElementType::Player :
				if(isFistInstruction) Player::LogicInstructions.clear();
				Player::LogicInstructions.push_back(logic.instructionType);
				break;
			case ElementType::Wall:
				/*if (isFistInstruction) Wall::logicInstructions.clear();
				Wall::logicInstructions.push_back(logic.instructionType);*/
				break;
			}

			if (isFistInstruction) isFistInstruction = false;
		}
	}
}

void Motor::RefreshEvents()
{
	events.clear();
	Event event;
	while (window->pollEvent(event))
		events.push_back(event);
}

bool Motor::GetEvent(Event& _event, Event::EventType eventType)
{
	for (Event event : events)
	{
		if (event.type == eventType) 
		{
			_event = event;
			return true;
		}
	}

	return false;
}