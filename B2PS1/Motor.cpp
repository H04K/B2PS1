#include "Motor.h"

Motor::Motor() {}
/*
Methode pour rajouter un nouvel element : (apres l'avoir rajouter dans une map)
- rajouter le template de code suivant a la suite du if :
if (ElementsMaps[index][y][x] == ##ID de l'element dans la map)
{
	## creation / ajout de parametres a l'element bref le code spécifique a element
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
				// Obliger d'utiliser un if car les case ne sont pas des bloc et donc pas possible de faire des declarations a l'interieur

				if (csvLevel[y][x] == 1)
				{
					Player* player = new Player();
					player->position->x = xTilesSize * x;
					player->position->y = yTilesSize * y;
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
			isLevelEnded == true;
		}

		window.clear(Color::Black);

		for (GameElement* gameElement : level->GameElements)
		{
			gameElement->Update();
		}

		for (GameElement* gameElement : level->GameElements)
		{
			gameElement->Draw();
		}

		window.display();
	}
}
/*
fonction voué a changer de place pour aller dans la class que gerera les evenements logiques
*/
bool Motor::isLogicSequenceValid(vector<Logic>& sequence)
{
	for (int i = 0; i < sequence.size(); i++)
	{ 
		if (i == 0 && 
			sequence[i].type != Type::Element)
		{
			return false;
		}

		else if (i != 0 && i % 2 != 0 &&
			sequence[i].type != Type::Operateur)
		{
			return false;
		}

		else if (i != 0 && i % 2 == 0 && 
			(sequence[i].type != Type::Element && sequence[i].type != Type::Instruction))
		{
			return false;
		}

		if (i != 0 && i == sequence.size() &&
			sequence[i].type != Type::Operateur)
		{
			return false;
		}
	}

	return true;
}

void Motor::RefreshEvents()
{
	events.clear();
	
	Event event;
	int eventsCount = 0;
	
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