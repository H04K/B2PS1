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

	/*reset save manager*/
	delete saveManager;
	saveManager = nullptr;

	while (window->isOpen())
	{
		static int mouseX = -1;
		static int mouseY = -1;

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
				return NavigationChoice::SelectSaveSlot;
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

NavigationChoice Motor::SelectSaveSlot()
{
	struct Slot
	{
		int index = -1;
		bool isEmpty;
		RectangleShape body;
		Text text;
		Color color;
		Color hoverColor;
		
		Slot(int index, bool isEmpty, float tx, float ty, float x, float y, Color color, Color hoverColor,string text, Color textColor) : index(index), isEmpty(isEmpty), color(color), hoverColor(hoverColor)
		{
			body = RectangleShape(Vector2f(tx, ty));
			body.setPosition(x - body.getSize().x / 2, y - body.getSize().y / 2);
			body.setFillColor(color);

			body.setOutlineThickness(body.getSize().y / 30);
			body.setOutlineColor(Color(78, 90, 148));

			this->text = Text(text, Ressources::Font_Arial);
			this->text.setFillColor(textColor);

			this->text.setPosition
			(
				(body.getPosition().x + body.getSize().x / 2) - Ressources::realTextSize(this->text).x / 2,
				(body.getPosition().y + body.getSize().y / 2) - Ressources::realTextSize(this->text).y / 2
			);
		}
		void Draw(RenderWindow& window) { window.draw(body); window.draw(text); }
	};

	list<Slot> slots = list<Slot>();

	int intervalScale = window->getSize().y / 24;
	int intervalStart = 7;
	int interval = 4;

	for (int i = 0; i < 3; i++)
	{
		ifstream slotFile("Assets/Saves/Slot" + to_string(i) + ".json", ifstream::binary);
		Json::Value slotValue;
		slotFile >> slotValue;

		if (!slotValue["isEmpty"])
		{
			slots.push_back(
				Slot
				(
					i, false, (window->getSize().x / 3) * 2, 150, window->getSize().x / 2, intervalScale* (intervalStart + interval * i),
					Color(78, 90, 148), Color(100, 130, 190),
					"Slot " + to_string(i) + " - " + slotValue["name"].asString(), Color::White
				)
			);
		}
		else
		{
			slots.push_back(
				Slot
				(
					i, true, (window->getSize().x / 3) * 2, 150, window->getSize().x / 2, intervalScale * (intervalStart + interval * i),
					Color(35, 41, 67), Color(60, 75, 110),
					"Slot " + to_string(i) + " - Empty", Color::White
				)
			);
		}
	}

	saveManager = new SaveManager(*this);

	while (window->isOpen())
	{
		static int mouseX = -1;
		static int mouseY = -1;

		RefreshEvents();

		Event event;
		if (GetEvent(event, Event::Closed))
			window->close();

		if (GetEvent(event, Event::MouseMoved))
		{
			mouseX = event.mouseMove.x;
			mouseY = event.mouseMove.y;
		}

		if (GetEvent(event, Event::KeyPressed), event.key.code == Keyboard::Escape)
			return NavigationChoice::MainMenu;
		
		for (Slot& slot : slots)
		{
			if (mouseX >= slot.body.getPosition().x && mouseX <= slot.body.getPosition().x + slot.body.getSize().x &&
				mouseY >= slot.body.getPosition().y && mouseY <= slot.body.getPosition().y + slot.body.getSize().y)
			{
				slot.body.setFillColor(slot.hoverColor);

				Event event;
				if (GetEvent(event, Event::MouseButtonPressed) && event.mouseButton.button == Mouse::Button::Left)
				{
					if (!slot.isEmpty)
					{
						saveManager->SaveSlot = slot.index;
						saveManager->LoadGame();
						return NavigationChoice::LevelSelect;
					}
					else
					{
						saveManager->SaveSlot = slot.index;
						saveManager->BuildNewSave();
						return NavigationChoice::LevelSelect;
					}
				}
			}
			else
			{
				slot.body.setFillColor(slot.color);
			}
		}

		window->clear();

		for (Slot& slot : slots)
			slot.Draw(*window);

		window->display();
	}

	return NavigationChoice::Quit;
}

NavigationChoice Motor::LevelSelect()
{
	struct UILevelData
	{
		Vector2f position;
		bool isMapChanger = false;
		int Map = -1;
		string TileMapPath;
		string ElementsMapPath;
		
		UILevelData(Vector2f position, string TileMapPath, string ElementsMapPath) : position(position), TileMapPath(TileMapPath), ElementsMapPath(ElementsMapPath){}
		UILevelData(Vector2f position, int Map) : position(position), isMapChanger(true), Map(Map){}
	};

	struct UIMapData
	{
		string backgroundPath;
		vector<UILevelData> UIlevels;

		UIMapData(vector<UILevelData> UIlevels, string backgroundPath) : UIlevels(UIlevels), backgroundPath(backgroundPath) {}
	};

	Texture backgroundTexture = Texture();
	backgroundTexture.loadFromFile("Assets/Sprites/Menu/1.png");
	backgroundTexture.setSmooth(true);

	Sprite background = Sprite();
	background.setTexture(backgroundTexture);
	background.setScale(1.5, 1.5);

	background.setPosition(
		Vector2f(window->getSize().x / 2 - (background.getLocalBounds().width / 2) * background.getScale().x,
			window->getSize().y / 2 - (background.getLocalBounds().height / 2) * background.getScale().y)
	);

	float wMargin = background.getPosition().x;
	float hMargin = background.getPosition().y;

	ifstream* mapsConfigFile = new ifstream("Assets/Levels/mapsConfig.json", ifstream::binary);
	Json::Value* maps = new Json::Value();
	*mapsConfigFile >> *maps;

	vector<UIMapData> UIMaps = vector<UIMapData>();

	for (Json::Value& map : *maps)
	{
		vector<UILevelData> uiLevelsDatas = vector<UILevelData>();

		for (Json::Value& level : map["levels"])
		{
			Vector2f position = Vector2f(level["x"].asInt() + wMargin, level["y"].asInt() + hMargin);

			if (!level["map"])
				uiLevelsDatas.push_back(UILevelData(position, level["tileMapPath"].asString(), level["elementsMapPath"].asString()));
			else
				uiLevelsDatas.push_back(UILevelData(position, level["map"].asInt()));
		}

		UIMaps.push_back( UIMapData(uiLevelsDatas, map["backgroundPath"].asString()) );
	}

	delete maps;
	delete mapsConfigFile;

	Texture cursorTexture = Texture();
	if(!cursorTexture.loadFromFile("Assets/Sprites/Menu/Cursor.png"))
		cout << "can't load Cursor image" << endl;
	
	Sprite cursor = Sprite();
	cursor.setTexture(cursorTexture);

	while (window->isOpen())
	{
		static int mouseX = -1;
		static int mouseY = -1;

		static int currentMap = 0;
		static int currentLevel = 0;

		RefreshEvents();

		Event event;
		if (GetEvent(event, Event::Closed))
			window->close();

		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Escape)
			return NavigationChoice::SelectSaveSlot;	// temporaire remplacer par MainMenu

		if (GetEvent(event, Event::MouseMoved))
		{
			mouseX = event.mouseMove.x;
			mouseY = event.mouseMove.y;

			// ligne de maping pour savoir ou placer le curseur
			cout << "Mouse position : " << mouseX - wMargin << ',' << mouseY - hMargin<< endl;
		}

		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Right)
		{
			if (currentLevel < UIMaps[currentMap].UIlevels.size() - 1)
				currentLevel++;
			else if (UIMaps[currentMap].UIlevels[currentLevel].isMapChanger)
			{
				currentMap = UIMaps[currentMap].UIlevels[currentLevel].Map;
				currentLevel = 0;
				
				if (!backgroundTexture.loadFromFile(UIMaps[currentMap].backgroundPath))
					cout << "can't load next map : background path incorrect" << endl;
			}
		}

		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Left)
		{
			if (currentLevel > 0)
				currentLevel--;

			else if(UIMaps[currentMap].UIlevels[currentLevel].isMapChanger)
			{
				currentMap = UIMaps[currentMap].UIlevels[currentLevel].Map;
				currentLevel = UIMaps[currentMap].UIlevels.size() - 1;

				if (!backgroundTexture.loadFromFile(UIMaps[currentMap].backgroundPath))
					cout << "can't load next map : background path incorrect" << endl;
			}
		}

		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Enter ||
			GetEvent(event, Event::MouseButtonPressed) && event.mouseButton.button == Mouse::Button::Left)
		{
			if (!UIMaps[currentMap].UIlevels[currentLevel].isMapChanger)
			{
				LoadLevel(UIMaps[currentLevel].UIlevels[currentLevel].TileMapPath, UIMaps[currentLevel].UIlevels[currentLevel].ElementsMapPath);
				
				return NavigationChoice::Play;
			}
		}

		cursor.setPosition(UIMaps[currentMap].UIlevels[currentLevel].position);

		window->clear(Color::Black);

		window->draw(background);
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

	while (window->isOpen() && !level->isWin)
	{
		RefreshEvents();

		Event event;
		if (GetEvent(event, Event::Closed))
			window->close();

		/*Ouvir le menu pause*/
		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Escape)
		{
			NavigationChoice navChoice = PauseMenu();
			if (navChoice != NavigationChoice::Play)
				return navChoice;

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
}

NavigationChoice Motor::PauseMenu()
{
	Texture backgroundText = Texture();
	backgroundText.create(window->getSize().x, window->getSize().y);
	backgroundText.update(*window);

	Sprite background = Sprite();
	background.setPosition(0, 0);
	background.setTexture(backgroundText);
	background.setColor(Color(128, 128, 128, 100));

	// Main Menu

	Text mainMenuText = Text("Main Menu", Ressources::Font_Ouders);
	mainMenuText.setCharacterSize(100);

	Vector2f mainMenuTextPostion = Vector2f(window->getSize().x / 2 - Ressources::realTextSize(mainMenuText).x / 2,
		(window->getSize().y / 40) * 16 - Ressources::realTextSize(mainMenuText).y / 2);

	mainMenuText.setPosition(mainMenuTextPostion);
	mainMenuText.setFillColor(Color::White);

	// Options

	Text levelSectionText = Text("Level Selection", Ressources::Font_Ouders);
	levelSectionText.setCharacterSize(100);

	Vector2f levelSectionTextPostion = Vector2f(window->getSize().x / 2 - Ressources::realTextSize(levelSectionText).x / 2,
		(window->getSize().y / 40) * 23 - Ressources::realTextSize(levelSectionText).y / 2);

	levelSectionText.setPosition(levelSectionTextPostion);
	levelSectionText.setFillColor(Color::White);

	// Quit

	Text quitText = Text("Save & Quit", Ressources::Font_Ouders);
	quitText.setCharacterSize(100);

	Vector2f quitTextPostion = Vector2f(window->getSize().x / 2 - Ressources::realTextSize(quitText).x / 2,
		(window->getSize().y / 40) * 29 - Ressources::realTextSize(quitText).y / 2);

	quitText.setPosition(quitTextPostion);
	quitText.setFillColor(Color::White);

	while (window->isOpen())
	{
		static int mouseX = -1;
		static int mouseY = -1;

		RefreshEvents();

		Event event;
		if (GetEvent(event, Event::Closed))
			window->close();

		if (GetEvent(event, Event::MouseMoved))
		{
			mouseX = event.mouseMove.x;
			mouseY = event.mouseMove.y;
		}

		if (GetEvent(event, Event::KeyPressed), event.key.code == Keyboard::Escape)
			return NavigationChoice::Play;

		if (mouseX >= mainMenuText.getPosition().x && mouseX <= mainMenuText.getPosition().x + Ressources::realTextSize(mainMenuText).x &&
			mouseY >= mainMenuText.getPosition().y && mouseY <= mainMenuText.getPosition().y + Ressources::realTextSize(mainMenuText).y)
		{
			mainMenuText.setFillColor(Color(255, 255, 255, 128));

			if (GetEvent(event, Event::MouseButtonPressed) && event.mouseButton.button == Mouse::Button::Left)
				return NavigationChoice::MainMenu;
		}
		else
			mainMenuText.setFillColor(Color(255, 255, 255, 255));


		if (mouseX >= levelSectionText.getPosition().x && mouseX <= levelSectionText.getPosition().x + Ressources::realTextSize(levelSectionText).x &&
			mouseY >= levelSectionText.getPosition().y && mouseY <= levelSectionText.getPosition().y + Ressources::realTextSize(levelSectionText).y)
		{
			levelSectionText.setFillColor(Color(255, 255, 255, 128));

			if (GetEvent(event, Event::MouseButtonPressed) && event.mouseButton.button == Mouse::Button::Left)
				return NavigationChoice::LevelSelect;
		}
		else
			levelSectionText.setFillColor(Color(255, 255, 255, 255));

		if (mouseX >= quitText.getPosition().x && mouseX <= quitText.getPosition().x + Ressources::realTextSize(quitText).x &&
			mouseY >= quitText.getPosition().y && mouseY <= quitText.getPosition().y + Ressources::realTextSize(quitText).y)
		{
			quitText.setFillColor(Color(255, 255, 255, 128));

			if (GetEvent(event, Event::MouseButtonPressed) && event.mouseButton.button == Mouse::Button::Left)
			{
				//SaveGame();
				return NavigationChoice::Quit;
			}
		}
		else
			quitText.setFillColor(Color(255, 255, 255, 255));

		window->draw(background);

		window->draw(mainMenuText);
		window->draw(levelSectionText);
		window->draw(quitText);

		window->display();
	}
}

void Motor::LoadLevel(string pathTileMap, string pathElements)
{
	events.clear();
	delete level;
	level = new Level();

	LoadElements(pathElements);
	LoadTileMap(pathTileMap);
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
void Motor::LoadElements(string path)
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
				// utiliser un if car les case ne sont pas des bloc

				if (csvLevel[y][x] == 1)
				{
					Brain* brain = new Brain();
					brain->position.x = xTilesSize * x;
					brain->position.y = yTilesSize * y;
					level->GameElements.push_back(brain);
				}
			}
		}

		cout << "Successful Loaded Elements " << path << endl;
	}
	catch (exception & ex)
	{
		cout << "Failed Load Elements : Elements " << path << " not found " << ex.what() << endl;
	}
}

/*
Methode pour rajouter un nouvel element : (apres l'avoir rajouter dans une map)
- rajouter le template de code suivant a la suite du if :
if (csvLevel[y][x] == ##ID de l'element dans la map)
{
}
*/
void Motor::LoadTileMap(string path)
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

		for (unsigned y = 0; y < csvLevel.size(); y++)
		{
			for (unsigned x = 0; x < csvLevel[y].size(); x++)
			{
				// utiliser un if car les case ne sont pas des bloc
				if (csvLevel[y][x] == 2)
				{
					Floor* Sol = new Floor();
					Sol->sprite.setPosition(xTilesSize * x, yTilesSize * y);

					level->MapElements.push_back(Sol);
				}
			}
		}

		cout << "Successful Loaded TileMap " << path << endl;
	}
	catch (exception & ex)
	{
		cout << "Failed Loading TileMap : TileMap " << path << " not found " << ex.what() << endl;
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