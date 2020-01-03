#include "Motor.h"

NavigationChoice Motor::MainMenu()
{
	// Play

	Text playText = Text("PLAY", Ressources::Font_Ouders);
	playText.setCharacterSize(150);

	Vector2f playTextPostion = Vector2f(window->getSize().x / 2 - Ressources::realTextSize(playText).x / 2, 
										(window->getSize().y / 40) * 16 - Ressources::realTextSize(playText).y / 2);
	
	playText.setPosition(playTextPostion);
	playText.setFillColor(Color::White);

	// Options
	
	Text optionText = Text("OPTIONS", Ressources::Font_Ouders);
	optionText.setCharacterSize(110);

	Vector2f optionTextPostion = Vector2f(window->getSize().x / 2 - Ressources::realTextSize(optionText).x / 2,
											(window->getSize().y / 40) * 23 - Ressources::realTextSize(optionText).y / 2);

	optionText.setPosition(optionTextPostion);
	optionText.setFillColor(Color::White);

	// Credits

	Text creditsText = Text("CREDITS", Ressources::Font_Ouders);
	creditsText.setCharacterSize(100);

	Vector2f creditsTextPostion = Vector2f(window->getSize().x / 2 - Ressources::realTextSize(creditsText).x / 2,
											(window->getSize().y / 40) * 29 - Ressources::realTextSize(creditsText).y / 2);

	creditsText.setPosition(creditsTextPostion);
	creditsText.setFillColor(Color::White);

	// Quit

	Text quitText = Text("QUIT", Ressources::Font_Ouders);
	quitText.setCharacterSize(130);

	Vector2f quitTextPostion = Vector2f(window->getSize().x / 2 - Ressources::realTextSize(quitText).x / 2,
										(window->getSize().y / 40) * 36 - Ressources::realTextSize(quitText).y / 2);

	quitText.setPosition(quitTextPostion);
	quitText.setFillColor(Color::White);

	// Adventure

	Text adventureText = Text("Adventure", Ressources::Font_BlackGround);
	adventureText.setCharacterSize(140);
	adventureText.setStyle(Text::Bold);

	Vector2f adventureTextPostion = Vector2f(window->getSize().x / 2 - Ressources::realTextSize(adventureText).x / 2,
												(window->getSize().y / 40) * 6 - Ressources::realTextSize(adventureText).y / 2);

	adventureText.setPosition(adventureTextPostion);
	adventureText.setFillColor(Color(74, 168, 80));

	// Brain

	Text brainText = Text("Brain", Ressources::Font_LemonJuice);
	brainText.setCharacterSize(210);
	brainText.setStyle(Text::Bold);

	Vector2f brainTextPostion = Vector2f(adventureText.getPosition().x - Ressources::realTextSize(brainText).x - adventureText.getLetterSpacing(),
											(window->getSize().y / 20) * 2 - Ressources::realTextSize(brainText).y / 2);

	brainText.setPosition(brainTextPostion);
	brainText.setFillColor(Color(246, 152, 157));
	
	// Brain Corner Image

	Texture brainCornerTexture = Texture();
	Sprite brainCornerSprite = Sprite();
	if (brainCornerTexture.loadFromFile("Assets/Sprites/Menu/brainLogo.png"))
	{
		brainCornerTexture.setRepeated(true);
		brainCornerTexture.setSmooth(true);
		brainCornerSprite.setTexture(brainCornerTexture);
	}
	else
	{
		cout << "init Menu error : can't load image" << endl;
		return NavigationChoice::Quit;
	}

	Vector2f brainCornerPostion = Vector2f(window->getSize().x - brainCornerSprite.getLocalBounds().width, 0);

	brainCornerSprite.setPosition(brainCornerPostion);
	 
	// Brain Select Image

	Texture brainSelectTexture = Texture();
	Sprite brainSelectSprite = Sprite();
	if (brainSelectTexture.loadFromFile("Assets/Sprites/Menu/litleBrain.png"))
	{
		brainSelectTexture.setRepeated(true);
		brainSelectTexture.setSmooth(true);
		brainSelectSprite.setTexture(brainSelectTexture);
	}
	else
	{
		cout << "init Menu error : can't load image" << endl;
		return NavigationChoice::Quit;
	}

	int mouseX = -1;
	int mouseY = -1;

	while (window->isOpen())
	{
		RefreshEvents();
		
		Event event;
		if (GetEvent(event, Event::Closed))
			window->close();

		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Escape)
			return NavigationChoice::Quit;

		if (GetEvent(event, Event::MouseMoved))
		{
			mouseX = event.mouseMove.x;
			mouseY = event.mouseMove.y;
		}

		if (mouseX >= playText.getPosition().x && mouseX <= playText.getPosition().x + Ressources::realTextSize(playText).x &&
			mouseY >= playText.getPosition().y && mouseY <= playText.getPosition().y + Ressources::realTextSize(playText).y)
		{
			Vector2f brainSelectPostion = Vector2f(window->getSize().x - brainSelectSprite.getLocalBounds().width, 0);
			brainSelectSprite.setPosition(brainSelectPostion);

			playText.setFillColor(Color(255,255,255,128));

			if (GetEvent(event, Event::MouseButtonPressed) && event.mouseButton.button == Mouse::Button::Left)
				return NavigationChoice::LevelSelect;
		}
		else
			playText.setFillColor(Color(255, 255, 255, 255));


		if (mouseX >= optionText.getPosition().x && mouseX <= optionText.getPosition().x + Ressources::realTextSize(optionText).x &&
			mouseY >= optionText.getPosition().y && mouseY <= optionText.getPosition().y + Ressources::realTextSize(optionText).y)
		{
			Vector2f brainSelectPostion = Vector2f(window->getSize().x - brainSelectSprite.getLocalBounds().width, 0);
			brainSelectSprite.setPosition(brainSelectPostion);

			optionText.setFillColor(Color(255, 255, 255, 128));

			if (GetEvent(event, Event::MouseButtonPressed) && event.mouseButton.button == Mouse::Button::Left)
				return NavigationChoice::Options;
		}
		else
			optionText.setFillColor(Color(255, 255, 255, 255));

		if (mouseX >= creditsText.getPosition().x && mouseX <= creditsText.getPosition().x + Ressources::realTextSize(creditsText).x &&
			mouseY >= creditsText.getPosition().y && mouseY <= creditsText.getPosition().y + Ressources::realTextSize(creditsText).y)
		{
			Vector2f brainSelectPostion = Vector2f(window->getSize().x - brainSelectSprite.getLocalBounds().width, 0);
			brainSelectSprite.setPosition(brainSelectPostion);

			creditsText.setFillColor(Color(255, 255, 255, 128));

			if (GetEvent(event, Event::MouseButtonPressed) && event.mouseButton.button == Mouse::Button::Left)
				return NavigationChoice::Credits;
		}
		else
			creditsText.setFillColor(Color(255, 255, 255, 255));

		if (mouseX >= quitText.getPosition().x && mouseX <= quitText.getPosition().x + Ressources::realTextSize(quitText).x &&
			mouseY >= quitText.getPosition().y && mouseY <= quitText.getPosition().y + Ressources::realTextSize(quitText).y)
		{
			Vector2f brainSelectPostion = Vector2f(window->getSize().x - brainSelectSprite.getLocalBounds().width, 0);
			brainSelectSprite.setPosition(brainSelectPostion);

			quitText.setFillColor(Color(255, 255, 255, 128));

			if (GetEvent(event, Event::MouseButtonPressed) && event.mouseButton.button == Mouse::Button::Left)
				return NavigationChoice::Quit;
		}
		else
			quitText.setFillColor(Color(255, 255, 255, 255));

		window->clear(Color::Black);
		
		window->draw(playText);
		window->draw(optionText);
		window->draw(creditsText);
		window->draw(quitText);
		window->draw(brainText);
		window->draw(adventureText);
		window->draw(brainCornerSprite);
		//window->draw(brainSelectSprite);

		window->display();
	}

	return NavigationChoice::Quit;
}

NavigationChoice Motor::LevelSelector()
{
	RectangleShape cursor = RectangleShape(Vector2f(50, 50));
	cursor.setFillColor(Color::Red);



	int mouseX = -1;
	int mouseY = -1;

	while (window->isOpen())
	{
		RefreshEvents();

		Event event;
		if (GetEvent(event, Event::Closed))
			window->close();

		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Escape)
			return NavigationChoice::MainMenu;

		if (GetEvent(event, Event::MouseMoved))
		{
			mouseX = event.mouseMove.x;
			mouseY = event.mouseMove.y;
		}

		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Z)
		{
			cursor.move(0, -cursor.getSize().y);
		}
		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Q)
		{
			cursor.move(-cursor.getSize().x, 0);
		}
		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::S)
		{
			cursor.move(0, cursor.getSize().y);
		}
		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::D)
		{
			cursor.move(cursor.getSize().x, 0);
		}

		window->clear(Color::Black);

		window->draw(cursor);

		window->display();
	}

	return NavigationChoice::Quit;
}

NavigationChoice Motor::Options()
{
	int mouseX = -1;
	int mouseY = -1;

	while (window->isOpen())
	{
		RefreshEvents();

		Event event;
		if (GetEvent(event, Event::Closed))
			window->close();

		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Escape)
			return NavigationChoice::MainMenu;

		if (GetEvent(event, Event::MouseMoved))
		{
			mouseX = event.mouseMove.x;
			mouseY = event.mouseMove.y;
		}

		window->clear(Color::Black);

		window->display();
	}

	return NavigationChoice::Quit;
}

NavigationChoice Motor::Credits()
{
	int mouseX = -1;
	int mouseY = -1;

	while (window->isOpen())
	{
		RefreshEvents();

		Event event;
		if (GetEvent(event, Event::Closed))
			window->close();

		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Escape)
			return NavigationChoice::MainMenu;

		if (GetEvent(event, Event::MouseMoved))
		{
			mouseX = event.mouseMove.x;
			mouseY = event.mouseMove.y;
		}

		window->clear(Color::Black);

		window->display();
	}

	return NavigationChoice::Quit;
}

void Motor::LoadGame(string pathMap,string pathLevel)
{
	events.clear();
	delete level;
	level = new Level();

	
	
	

	LoadLevel(pathLevel);
	LoadMap(pathMap);
	//LoadMisc(pathMisc);
}

/*
Methode pour rajouter un nouvel element : (apres l'avoir rajouter dans une map)
- LogicSequenceManager : rajouter le nom du gameElement dans l'enum
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

		int xTilesSize = Ressources::WindowSize.width / csvLevel[0].size();
		int yTilesSize = Ressources::WindowSize.height / csvLevel.size();

		for (auto y = 0; y < csvLevel.size(); y++)
		{
			for (auto x = 0; x < csvLevel[y].size(); x++)
			{
				cout << csvLevel[y][x];
				// utiliser un if car les case ne sont pas des bloc

				if (csvLevel[y][x] == 1)
				{
					Brain* brain = new Brain();
					brain->position.x = xTilesSize * x;
					brain->position.y = yTilesSize * y;
					level->GameElements.push_back(brain);
				}
			}
			cout << endl;
		}

		cout << "Successful Loaded Level " << path << endl;
	}
	catch (exception & ex)
	{
		cout << "Failed Load Level : Level " << path << " not found " << ex.what() << endl;
	}
}

/*
Methode pour rajouter un nouvel element : (apres l'avoir rajouter dans une map)
- rajouter le template de code suivant a la suite du if :
if (csvLevel[y][x] == ##ID de l'element dans la map)
{
}
*/
void Motor::LoadMap(string path)
{
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

		int xTilesSize = Ressources::WindowSize.width / csvLevel[0].size();
		int yTilesSize = Ressources::WindowSize.height / csvLevel.size();
		float xSpriteScale = (csvLevel.size() / 10) + yTilesSize / 100.f;
		float  ySpriteScale = ((csvLevel.size() / 10)/2) + xTilesSize / 100.f;
		for (unsigned y = 0; y < csvLevel.size(); y++)
		{
			for (unsigned x = 0; x < csvLevel[y].size(); x++)
			{
				// utiliser un if car les case ne sont pas des blocs
				//Là on a un soucis du type wtf les tiles se superposent pas 
				// et jcomprend pas 

				cout << csvLevel[y][x];
				if (csvLevel[y][x] == 3)
				{
					Bounds* Uwall = new Bounds();
					Uwall->sprite.setPosition(xTilesSize * x, yTilesSize * y);
					Uwall->sprite.setScale(xSpriteScale, ySpriteScale);
					level->MapElements.push_back(Uwall);

				}
				if (csvLevel[y][x] == 2)
				{
					Floor* Sol = new Floor();
					Sol->sprite.setPosition(xTilesSize * x, yTilesSize * y);
					Sol->sprite.setScale(xSpriteScale, ySpriteScale);
					level->MapElements.push_back(Sol);

				}
				cout << endl;
			}
		}

		cout << "Successful Loaded TileMap " << path << endl;
		cout << xTilesSize <<" "  << yTilesSize / 100 << endl;
		
	}
	catch (exception & ex)
	{
		cout << "Failed Loading TileMap : TileMap " << path << " not found " << ex.what() << endl;
	}
}
//void Motor::LoadMisc(string path)
//{
//	try
//	{
//		ifstream fileStream = ifstream(path);
//		vector<vector<int>> csvLevel = vector<vector<int>>();
//
//		string line;
//		while (getline(fileStream, line))
//		{
//			vector<int> levelRow = vector<int>();
//			stringstream lineStream = stringstream(line);
//
//			string cell;
//			while (getline(lineStream, cell, ','))
//				levelRow.push_back(stoi(cell));
//			csvLevel.push_back(levelRow);
//		}
//
//		int xTilesSize = Ressources::WindowSize.width / csvLevel[0].size();
//		int yTilesSize = Ressources::WindowSize.height / csvLevel.size();
//		float xSpriteScale = (csvLevel.size() / 10) + yTilesSize / 100.f;
//		float  ySpriteScale = ((csvLevel.size() / 10) / 2) + xTilesSize / 100.f;
//		for (unsigned y = 0; y < csvLevel.size(); y++)
//		{
//			for (unsigned x = 0; x < csvLevel[y].size(); x++)
//			{
//				// utiliser un if car les case ne sont pas des bloc
//				if (csvLevel[y][x] == 2)
//				{
//					Bounds* UpWall = new Bounds();
//					UpWall->sprite.setPosition(xTilesSize * x, yTilesSize * y);
//					UpWall->sprite.setScale(xSpriteScale, ySpriteScale);
//					level->MapElements.push_back(UpWall);
//
//				}
//				if (csvLevel[y][x] == 4)
//				{
//					Bounds* ULcorner = new Bounds();
//					ULcorner->sprite.setPosition(xTilesSize * x, yTilesSize * y);
//					ULcorner->sprite.setScale(xSpriteScale, ySpriteScale);
//					level->MapElements.push_back(ULcorner);
//
//				}
//				if (csvLevel[y][x] == 3)
//				{
//					Bounds* LWall = new Bounds();
//					LWall->sprite.setPosition(xTilesSize * x, yTilesSize * y);
//					LWall->sprite.setScale(xSpriteScale, ySpriteScale);
//					level->MapElements.push_back(LWall);
//
//				}
//				if (csvLevel[y][x] == 5)
//				{
//					Bounds* BLcorner = new Bounds();
//					BLcorner->sprite.setPosition(xTilesSize * x, yTilesSize * y);
//					BLcorner->sprite.setScale(xSpriteScale, ySpriteScale);
//					level->MapElements.push_back(BLcorner);
//
//				}
//				if (csvLevel[y][x] == 8)
//				{
//					Bounds* BottWall = new Bounds();
//					BottWall->sprite.setPosition(xTilesSize * x, yTilesSize * y);
//					BottWall->sprite.setScale(xSpriteScale, ySpriteScale);
//					level->MapElements.push_back(BottWall);
//
//				}
//				if (csvLevel[y][x] == 6)
//				{
//					Bounds* BRcorner = new Bounds();
//					BRcorner->sprite.setPosition(xTilesSize * x, yTilesSize * y);
//					BRcorner->sprite.setScale(xSpriteScale, ySpriteScale);
//					level->MapElements.push_back(BRcorner);
//
//				}
//				if (csvLevel[y][x] == 1)
//				{
//					Bounds* RWall = new Bounds();
//					RWall->sprite.setPosition(xTilesSize * x, yTilesSize * y);
//					RWall->sprite.setScale(xSpriteScale, ySpriteScale);
//					level->MapElements.push_back(RWall);
//
//				}
//				if (csvLevel[y][x] == 7)
//				{
//					Bounds* URcorner = new Bounds();
//					URcorner->sprite.setPosition(xTilesSize * x, yTilesSize * y);
//					URcorner->sprite.setScale(xSpriteScale, ySpriteScale);
//					level->MapElements.push_back(URcorner);
//
//
//				}
//
//			}
//		}
//
//		cout << "Successful Loaded TileMap " << path << endl;
//		cout << xTilesSize << " " << yTilesSize / 100 << endl;
//
//	}
//	catch (exception & ex)
//	{
//		cout << "Failed Loading TileMap : TileMap " << path << " not found " << ex.what() << endl;
//	}
//}

NavigationChoice Motor::Play() {

	if (level == nullptr) { cout << "Failed Play : Level is null" << endl; return NavigationChoice::Quit; }

	for (GameElement* gameElement : level->GameElements)
	{
		gameElement->motor = this;
		gameElement->LoadSprites();
		gameElement->Start();
	}

	for (MapElement* mapElement : level->MapElements)
	{
		mapElement->motor = this;

		mapElement->LoadSprites();
		mapElement->Start();
	}

	while (window->isOpen() && !level->isFinished)
	{
		RefreshEvents();

		Event event;
		if (GetEvent(event, Event::Closed))
			window->close();

		/*Ouvir le menu pause*/
		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Escape)
		{
			PauseMenu();
		}

		/*PROTOTYPING pour ajouter manuelement des evenements logiques*/
		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::F)
		{
			cout << "Entrer un sequence logique : ";
			char tabCode[50];
			cin.getline(tabCode, 50);
			string code(tabCode);

			logicSequenceManager.sendSequence(code);
		}

		window->clear(Color::Black);

		for (MapElement* mapElement : level->MapElements)
		{
			mapElement->Update();
			mapElement->Draw();
		}

		for (GameElement* gameElement : level->GameElements)
		{
			gameElement->ApplyLogicInstructions();
			gameElement->Update();
			gameElement->Draw();
		}

		window->display();
	}

	return NavigationChoice::LevelSelect;

	delete level;
	level = nullptr;
}

void Motor::PauseMenu()
{
	Texture backgroundText = Texture();
	backgroundText.create(window->getSize().x, window->getSize().y);
	backgroundText.update(*window);

	Sprite background = Sprite();
	background.setTexture(backgroundText);
	
	RectangleShape shape = RectangleShape(Vector2f(50, 50));
	shape.setFillColor(Color::Red);

	while (window->isOpen())
	{
		RefreshEvents();

		Event event;
		if (GetEvent(event, Event::Closed))
			window->close();
		
		if (GetEvent(event, Event::MouseMoved))
		{
			shape.setPosition(event.mouseMove.x, event.mouseMove.y);
		}

		if (GetEvent(event, Event::KeyPressed), event.key.code == Keyboard::Escape)
			return;

		window->draw(background);

		window->draw(shape);
		window->display();
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
