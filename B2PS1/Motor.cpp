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
		Color borderColor;
		
		Slot(int index, bool isEmpty, float tx, float ty, float x, float y, Color color, Color hoverColor, Color borderColor, string text, Color textColor) 
			: index(index), isEmpty(isEmpty), color(color), hoverColor(hoverColor), borderColor(borderColor)
		{
			body = RectangleShape(Vector2f(tx, ty));
			body.setPosition(x - body.getSize().x / 2, y - body.getSize().y / 2);
			body.setFillColor(color);

			body.setOutlineThickness(body.getSize().y / 30);
			body.setOutlineColor(borderColor);

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

	saveManager = new SaveManager(*this);

	list<Slot> slots = list<Slot>();

	int intervalScale = window->getSize().y / 24;
	int intervalStart = 7;
	int interval = 4;

	// initialiser les 3 slots
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
					i, false, (window->getSize().x / 3) * 2, (window->getSize().y / 14) * 2, window->getSize().x / 2, intervalScale* (intervalStart + interval * i),
					Color(78, 90, 148), Color(100, 130, 190), Color(78, 90, 148),
					"Slot " + to_string(i) + " - " + slotValue["name"].asString() + " | Level " + to_string(slotValue["levelsDone"].asInt()) + " / " + to_string(saveManager->getLevelsCount()),
					Color::White
				)
			);
		}
		else
		{
			slots.push_back(
				Slot
				(
					i, true, (window->getSize().x / 3) * 2, (window->getSize().y / 14) * 2, window->getSize().x / 2, intervalScale * (intervalStart + interval * i),
					Color(35, 41, 67), Color(60, 75, 110), Color(78, 90, 148),
					"Slot " + to_string(i) + " - Empty", Color::White
				)
			);
		}
	}

	// il serais preferable de faire un ensemble de class pour les UI avec collection des event ect mais pas le temps
	Slot eraseModeButton = Slot
	(
		-1, false, (window->getSize().x / 3) * 2, 60, window->getSize().x / 2, intervalScale * 20,
		Color(78, 90, 148), Color(35, 41, 67), Color(35, 41, 67),
		"Empty slot", Color::White
	);

	int mouseX = -1;
	int mouseY = -1;

	bool eraseMode = false;

	while (window->isOpen())
	{
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
			// hovering
			if (mouseX >= slot.body.getPosition().x && mouseX <= slot.body.getPosition().x + slot.body.getSize().x &&
				mouseY >= slot.body.getPosition().y && mouseY <= slot.body.getPosition().y + slot.body.getSize().y)
			{
				// load mode
				if (!eraseMode)
				{
					slot.body.setFillColor(slot.hoverColor);
					slot.body.setOutlineColor(slot.borderColor);

					if (GetEvent(event, Event::MouseButtonPressed) && event.mouseButton.button == Mouse::Button::Left)
					{
						if (!slot.isEmpty)
						{
							cout << "Loading Slot " + to_string(slot.index) << endl;
							saveManager->SaveSlot = slot.index;
							saveManager->LoadGame();
							return NavigationChoice::LevelSelect;
						}
						else
						{
							cout << "Loading Build Slot " + to_string(slot.index) << endl;
							saveManager->SaveSlot = slot.index;
							saveManager->SaveGame();
							return NavigationChoice::SelectSaveSlot;
						}
					}
				}
				// erase Mode
				else
				{
					slot.body.setFillColor(Color(229, 83, 59));
					slot.body.setOutlineColor(Color(103, 37, 27));

					Event event;
					if (GetEvent(event, Event::MouseButtonPressed) && event.mouseButton.button == Mouse::Button::Left)
					{
						cout << "Empty Slot " + to_string(slot.index) << endl;
						saveManager->EmptySlot(slot.index);
						// pas opti du tout mais y'a pas le temps
						return NavigationChoice::SelectSaveSlot;
					}
				}
			}
			// not hovering
			else
			{
				// load mode
				if (!eraseMode)
				{
					slot.body.setFillColor(slot.color);
					slot.body.setOutlineColor(slot.borderColor);
				}
				// erase mode
				else
				{
					slot.body.setFillColor(Color(103, 37, 27));
					slot.body.setOutlineColor(Color(229, 83, 59));
				}
			}
		}

		if (mouseX >= eraseModeButton.body.getPosition().x && mouseX <= eraseModeButton.body.getPosition().x + eraseModeButton.body.getSize().x &&
			mouseY >= eraseModeButton.body.getPosition().y && mouseY <= eraseModeButton.body.getPosition().y + eraseModeButton.body.getSize().y)
		{
			if(!eraseMode)
				eraseModeButton.body.setFillColor(eraseModeButton.hoverColor);
			else
				eraseModeButton.body.setFillColor(eraseModeButton.color);

			if (GetEvent(event, Event::MouseButtonPressed) && event.mouseButton.button == Mouse::Button::Left)
				eraseMode = !eraseMode;
		}
		else
		{
			if (!eraseMode)
				eraseModeButton.body.setFillColor(eraseModeButton.color);
			else
				eraseModeButton.body.setFillColor(eraseModeButton.hoverColor);
		}

		window->clear();

		for (Slot& slot : slots)
			slot.Draw(*window);

		eraseModeButton.Draw(*window);

		window->display();
	}

	return NavigationChoice::Quit;
}

NavigationChoice Motor::LevelSelect()
{
#pragma region Declaration Struct

	struct UILevelData
	{
		Vector2f position;
		bool isMapChanger = false;
		bool isUnlocked = true;
		int Map = -1;
		string TileMapPath;
		string ElementsMapPath;
		
		Sprite sprite;
		Text text;

		void Draw(RenderWindow& window) { window.draw(sprite); window.draw(text); }

		UILevelData(Texture& texture, string text, bool isUnlocked, Vector2f position, string TileMapPath, string ElementsMapPath)
			: sprite(Sprite(texture)), isUnlocked(isUnlocked), position(position), TileMapPath(TileMapPath), ElementsMapPath(ElementsMapPath)
		{ 
			sprite.setPosition(position);

			this->text = Text(text, Ressources::Font_BlackGround);
			this->text.setCharacterSize(40);
			this->text.setStyle(Text::Bold);

			if(!isUnlocked)
				this->text.setFillColor(Color::Red);
			this->text.setPosition
			(
				(sprite.getPosition().x + sprite.getLocalBounds().width / 2) - Ressources::realTextSize(this->text).x / 2,
				(sprite.getPosition().y + sprite.getLocalBounds().height / 2) - Ressources::realTextSize(this->text).y / 2
			);
		}

		UILevelData(Texture& texture, Vector2f position, int Map)
			: sprite(Sprite(texture)), position(position), isMapChanger(true), Map(Map)
		{
			sprite.setPosition(position);
		}
	};

	struct UIMapData
	{
		string backgroundPath;
		vector<UILevelData> UIlevels;
		UILevelData operator[](int index) { return  UIlevels[index]; }

		UIMapData(vector<UILevelData> UIlevels, string backgroundPath) : UIlevels(UIlevels), backgroundPath(backgroundPath) {}
	};

#pragma endregion

#pragma region Creation Sprites

	Texture UILevelsTextures[3];

	Texture* UILevelsTexture = new Texture; UILevelsTexture->loadFromFile("Assets/Sprites/Menu/LevelBack.png");
	UILevelsTextures[0] = *UILevelsTexture;
	delete UILevelsTexture;
	
	UILevelsTexture = new Texture; UILevelsTexture->loadFromFile("Assets/Sprites/Menu/arrow_right.png");
	UILevelsTextures[1] = *UILevelsTexture;
	delete UILevelsTexture;

	UILevelsTexture = new Texture; UILevelsTexture->loadFromFile("Assets/Sprites/Menu/arrow_left.png");
	UILevelsTextures[2] = *UILevelsTexture;
	delete UILevelsTexture;

	Texture cursorTexture = Texture();
	if (!cursorTexture.loadFromFile("Assets/Sprites/Menu/Cursor.png"))
		cout << "can't load Cursor image" << endl;

	Sprite cursor = Sprite();
	cursor.setTexture(cursorTexture);

	Texture lockTexture = Texture();
	if (!lockTexture.loadFromFile("Assets/Sprites/Menu/lock2.png"))
		cout << "can't load lock image" << endl;

	Sprite lock = Sprite();
	lock.setTexture(lockTexture);
	lock.setColor(Color(255, 255, 255, 200));

#pragma endregion

	static int currentMap = 0;
	static int currentLevel = 0;

#pragma region Init BackGround

	Texture backgroundTexture = Texture();
	backgroundTexture.loadFromFile("Assets/Sprites/Menu/" + to_string(currentMap) +".gif");
	backgroundTexture.setSmooth(true);

	Sprite background = Sprite();
	background.setTexture(backgroundTexture);
	background.setScale(1.5, 1.5);

	background.setPosition(
		Vector2f(window->getSize().x / 2 - (background.getLocalBounds().width / 2) * background.getScale().x,
			window->getSize().y / 2 - (background.getLocalBounds().height / 2) * background.getScale().y)
	);

#pragma endregion

	float wMargin = background.getPosition().x;
	float hMargin = background.getPosition().y;

#pragma region Build UIMaps

	ifstream* mapsConfigFile = new ifstream("Assets/Levels/mapsConfig.json", ifstream::binary);
	Json::Value* maps = new Json::Value();
	*mapsConfigFile >> *maps;

	vector<UIMapData> UIMaps = vector<UIMapData>();

	int globalLevelsCount = 0;
	int saveMap = 0;

	for (Json::Value& map : *maps)
	{
		vector<UILevelData> uiLevelsDatas = vector<UILevelData>();
		int saveLevel = 0;

		for (Json::Value& level : map["levels"])
		{
			Vector2f position = Vector2f(level["x"].asInt() + wMargin, level["y"].asInt() + hMargin);

			if (!level["map"])
			{
				string UIlevelText;

				if (globalLevelsCount >= 10)
					UIlevelText = to_string(globalLevelsCount);
				else
					UIlevelText = '0' + to_string(globalLevelsCount);

				uiLevelsDatas.push_back(
					UILevelData(UILevelsTextures[level["backgroundType"].asInt()],
						UIlevelText, saveManager->Maps[saveMap][saveLevel].isUnlocked,
						position, level["tileMapPath"].asString(), level["elementsMapPath"].asString())
				);
				saveLevel++;
				globalLevelsCount++;
			}
			else
			{
				uiLevelsDatas.push_back(
					UILevelData(UILevelsTextures[level["backgroundType"].asInt()],
						position, level["map"].asInt())
				);
			}
		}

		UIMaps.push_back( UIMapData(uiLevelsDatas, map["backgroundPath"].asString()) );
		saveMap++;
	}

	delete maps;
	delete mapsConfigFile;

#pragma endregion

	if (saveManager->getLevelsDone() == 1)
	{
		LoadLevel(UIMaps[0][0].TileMapPath, UIMaps[0][0].ElementsMapPath, 0, 0);
		return NavigationChoice::Play;
	}
	
	int mouseX = -1;
	int mouseY = -1;

	while (window->isOpen())
	{
		RefreshEvents();

		Event event;
		if (GetEvent(event, Event::Closed))
			window->close();

		//Ouvir le menu pause
		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Escape)
		{
			saveManager->SaveGame();
			NavPair pauseButtons[3] = 
			{ 
				NavPair(NavigationChoice::MainMenu, "Main Menu"),
				NavPair(NavigationChoice::SelectSaveSlot, "Saves"),
				NavPair(NavigationChoice::Quit, "Quit")
			};

			NavigationChoice navChoice = PauseMenu(pauseButtons);
			if (navChoice != NavigationChoice::Stay)
				return navChoice;
		}

		if (GetEvent(event, Event::MouseMoved)) { mouseX = event.mouseMove.x; mouseY = event.mouseMove.y; }

		// ligne de maping pour savoir ou placer le curseur
		if (GetEvent(event, Event::MouseButtonPressed))
			cout << "Mouse position : " << mouseX - wMargin << ',' << mouseY - hMargin << endl;

		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Right)
		{
			if (currentLevel < UIMaps[currentMap].UIlevels.size() - 1 && UIMaps[currentMap][currentLevel + 1].isUnlocked)
			{
				currentLevel++;
			}
			else if (UIMaps[currentMap][currentLevel].isMapChanger)
			{
				currentMap = UIMaps[currentMap][currentLevel].Map;
				currentLevel = 0;
				
				if (!backgroundTexture.loadFromFile(UIMaps[currentMap].backgroundPath))
					cout << "can't load next map : background path incorrect" << endl;
			}
		}

		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Left)
		{
			if (currentLevel > 0 && UIMaps[currentMap][currentLevel - 1].isUnlocked)
			{
				currentLevel--;
			}

			else if(UIMaps[currentMap][currentLevel].isMapChanger)
			{
				currentMap = UIMaps[currentMap][currentLevel].Map;
				currentLevel = UIMaps[currentMap].UIlevels.size() - 1;

				if (!backgroundTexture.loadFromFile(UIMaps[currentMap].backgroundPath))
					cout << "can't load next map : background path incorrect" << endl;
			}
		}

		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Enter)
		{
			if (!UIMaps[currentMap][currentLevel].isMapChanger)
			{
				LoadLevel(UIMaps[currentMap][currentLevel].TileMapPath, UIMaps[currentMap][currentLevel].ElementsMapPath, currentMap, currentLevel);
				return NavigationChoice::Play;
			}
		}

		cursor.setPosition(UIMaps[currentMap][currentLevel].position);

		window->clear(Color::Black);
		window->draw(background);

		for (UILevelData& level : UIMaps[currentMap].UIlevels)
		{
			level.Draw(*window);

			if (!level.isMapChanger && !level.isUnlocked)
			{
				lock.setPosition(level.position);
				window->draw(lock);
			}
		}
		
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

	for (LogicBloc* logicBlock : level->LogicBlocs)
	{
		logicBlock->motor = this;
		logicBlock->collider = new Collider(&logicBlock->position,
			Vector2f(logicBlock->body.getLocalBounds().width, logicBlock->body.getLocalBounds().height));
	}

	for (MapElement* mapElement : level->MapElements)
	{
		mapElement->motor = this;
		mapElement->LoadSprites();
		mapElement->Start();
	}

	while (window->isOpen())
	{
		// refresh events list
		RefreshEvents();

		Event event;
		if (GetEvent(event, Event::Closed))
			window->close();

		if (level->isWin)
		{
			// get mapConfig
			ifstream mapsConfigFile("Assets/Levels/mapsConfig.json", ifstream::binary);
			Json::Value maps; mapsConfigFile >> maps;

			// save timedone
			saveManager->Maps[level->mapIndex][level->levelIndex].timeDone = level->timeDone;

			// unlock next map
			int unlockMap = maps[level->mapIndex]["levels"][level->mapIndex]["unLockLevel"][0].asInt();
			int unlockLevel = maps[level->mapIndex]["levels"][level->mapIndex]["unLockLevel"][1].asInt();
			
			saveManager->Maps[unlockMap][unlockLevel].isUnlocked = true;

			// save & return
			saveManager->SaveGame();
			return NavigationChoice::LevelSelect;
		}

		//Ouvir le menu pause
		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::Escape)
		{
			saveManager->SaveGame();
			NavPair pauseButtons[3] =
			{
				NavPair(NavigationChoice::Play, "Restart Level"),
				NavPair(NavigationChoice::LevelSelect, "Level Selection"),
				NavPair(NavigationChoice::Quit, "Quit")
			};

			NavigationChoice navChoice = PauseMenu(pauseButtons);
			if (navChoice != NavigationChoice::Stay)
			{
				if (navChoice == NavigationChoice::Play)
					RestartLevel();
				
				return navChoice;
			}
		}

		//PROTOTYPING pour ajouter manuelement des evenements logiques
		if (GetEvent(event, Event::KeyPressed) && event.key.code == Keyboard::F)
		{
			cout << "Entrer un sequence logique : ";
			char tabCode[50];
			cin.getline(tabCode, 50);
			logicSequenceManager.sendSequence(tabCode);
		}

		window->clear(Color::Black);

#pragma region Update/Draw

		for (MapElement* mapElement : level->MapElements)
		{
			mapElement->Update();
			mapElement->Draw();
		}

		for (GameElement* gameElement : level->GameElements)
		{
			gameElement->ApplyLogicInstructions();
			gameElement->Update();

			for (LogicBloc* logicBloc : level->LogicBlocs)
					gameElement->getCollider().CheckPushCollison(*logicBloc->collider, 1);
			
			gameElement->Draw();
		}

		for (LogicBloc* logicBloc : level->LogicBlocs)
		{
			logicBloc->CheckCollision(level->LogicBlocs);

			for (LogicBloc* other : level->LogicBlocs)
				if (logicBloc != other)
					logicBloc->collider->CheckPushCollison(*other->collider, 1);

			for (GameElement* gameElement : level->GameElements)
			{
				if (gameElement->Is(InstructionType::Push))
					gameElement->getCollider().CheckPushCollison(*logicBloc->collider, 1);
				if (gameElement->Is(InstructionType::Stop))
					gameElement->getCollider().CheckStopCollison(*logicBloc->collider, Ressources::MoveVelocity);
			}

			logicBloc->Draw();
		}


		logicSequenceManager.buildSequence(level->LogicBlocs);

#pragma endregion

		window->display();
	}

	saveManager->SaveGame();
	return NavigationChoice::Quit;
}

NavigationChoice Motor::PauseMenu(NavPair buttonsData[3])
{
	// Fond
	Texture backgroundText = Texture();
	backgroundText.create(window->getSize().x, window->getSize().y);
	backgroundText.update(*window);

	Sprite background = Sprite();
	background.setPosition(0, 0);
	background.setTexture(backgroundText);
	background.setColor(Color(128, 128, 128, 100));

	Text buttons[3];

	int intervalScale = window->getSize().y / 40;
	int intervalStart = 16;
	int interval = 7;

	// init buttons
	for (int i = 0; i < 3; i++)
	{
		Text button = Text(buttonsData[i].Wording, Ressources::Font_Ouders);
		button.setCharacterSize(100);

		Vector2f buttonPostion = Vector2f(window->getSize().x / 2 - Ressources::realTextSize(button).x / 2,
			intervalScale * (intervalStart + interval * i) - Ressources::realTextSize(button).y / 2);

		button.setPosition(buttonPostion);
		button.setFillColor(Color::White);

		buttons[i] = button;
	}

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
			return NavigationChoice::Stay;

		for (int i = 0; i < 3; i++)
		{
			if (mouseX >= buttons[i].getPosition().x && mouseX <= buttons[i].getPosition().x + Ressources::realTextSize(buttons[i]).x &&
				mouseY >= buttons[i].getPosition().y && mouseY <= buttons[i].getPosition().y + Ressources::realTextSize(buttons[i]).y)
			{
				buttons[i].setFillColor(Color(255, 255, 255, 128));

				if (GetEvent(event, Event::MouseButtonPressed) && event.mouseButton.button == Mouse::Button::Left)
					return buttonsData[i].NavChoice;
			}
			else
				buttons[i].setFillColor(Color(255, 255, 255, 255));
		}

		window->draw(background);

		for (Text& button : buttons)
			window->draw(button);

		window->display();
	}
}

void Motor::LoadLevel(string pathTileMap, string pathElements, int mapIndex, int levelIndex)
{
	events.clear();
	
	delete level;
	level = new Level();
	level->mapIndex = mapIndex;
	level->levelIndex = levelIndex;
	level->pathTileMap = pathTileMap;
	level->pathElements = pathElements;

	LoadElements(pathElements);
	LoadTileMap(pathTileMap);
}

void Motor::LoadElements(string path)
{
	/*
	Methode pour rajouter un nouvel element :
	- LogicSequenceManager : rajouter le nom du gameElement dans l'enum
	- rajouter le template de code suivant a la suite du if :
	if (csvLevel[y][x] == ##ID de l'element dans la map)
	{
		## creation / ajout de parametres a l'element bref le code sp�cifique a element
		## /!\ doit etre instancier par un new /!\ # ex : Player* player = new Player() #

		level->GameElements.push_back( ##Element );
	}
	*/
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
		float ySpriteScale = ((csvLevel.size() / 10) / 2) + xTilesSize / 100.f;

		for (size_t y = 0; y < csvLevel.size(); y++)
		{
			for (size_t x = 0; x < csvLevel[y].size(); x++)
			{
				// utiliser un if car les case ne sont pas des bloc

				if (csvLevel[y][x] == 1)
				{
					Brain* brain = new Brain(this, Vector2f(xTilesSize * x, yTilesSize * y), ElementType::Brain);
					level->GameElements.push_back(brain);
				}
				if (csvLevel[y][x] == 2)
				{
					Wall* wall = new Wall(this, Vector2f(xTilesSize * x, yTilesSize * y), ElementType::Wall);
					level->GameElements.push_back(wall);
				}

				if (csvLevel[y][x] == 10)
				{
					LogicBloc* logicBlock = new LogicBloc(&Ressources::Texture_LogicBrain, 
						Vector2f(64, 64), Vector2f(xTilesSize * x, yTilesSize * y),
						Logic(ElementType::Brain));
					level->LogicBlocs.push_back(logicBlock);
				}
				if (csvLevel[y][x] == 11)
				{
					LogicBloc* logicBlock = new LogicBloc(&Ressources::Texture_LogicWall, 
						Vector2f(64, 64), Vector2f(xTilesSize * x, yTilesSize * y),
						Logic(ElementType::Wall));
					level->LogicBlocs.push_back(logicBlock);
				}

				if (csvLevel[y][x] == 20)
				{
					LogicBloc* logicBlock = new LogicBloc(&Ressources::Texture_LogicIs, 
						Vector2f(64, 64), Vector2f(xTilesSize * x, yTilesSize * y),
						Logic(OperateurType::Is));
					level->LogicBlocs.push_back(logicBlock);
				}

				if (csvLevel[y][x] == 30)
				{
					LogicBloc* logicBlock = new LogicBloc(&Ressources::Texture_LogicYou,
						Vector2f(64, 64), Vector2f(xTilesSize * x, yTilesSize * y),
						Logic(InstructionType::You));
					level->LogicBlocs.push_back(logicBlock);
				}
				if (csvLevel[y][x] == 31)
				{
					LogicBloc* logicBlock = new LogicBloc(&Ressources::Texture_LogicStop,
						Vector2f(64, 64), Vector2f(xTilesSize * x, yTilesSize * y),
						Logic(InstructionType::Stop));
					level->LogicBlocs.push_back(logicBlock);
				}
				if (csvLevel[y][x] == 32)
				{
					LogicBloc* logicBlock = new LogicBloc(&Ressources::Texture_LogicPush,
						Vector2f(64, 64), Vector2f(xTilesSize * x, yTilesSize * y),
						Logic(InstructionType::Push));
					level->LogicBlocs.push_back(logicBlock);
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

void Motor::LoadTileMap(string path)
{
	/*
	Methode pour rajouter une nouvelle tile :
	- rajouter le template de code suivant a la suite du if :
	if (csvLevel[y][x] == ##ID de l'element dans la map)
	{
	}
	*/
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
		float ySpriteScale = ((csvLevel.size() / 10) / 2) + xTilesSize / 100.f;
		
		for (size_t y = 0; y < csvLevel.size(); y++)
		{
			for (size_t x = 0; x < csvLevel[y].size(); x++)
			{
				// utiliser un if car les case ne sont pas des bloc
				if (csvLevel[y][x] == 1)
				{
					Bound* bound = new Bound();
					bound->sprite.setPosition(xTilesSize * x, yTilesSize * y);
					bound->sprite.setScale(xSpriteScale, ySpriteScale);

					level->MapElements.push_back(bound);
				}
				if (csvLevel[y][x] == 2)
				{
					Floor* Sol = new Floor();
					Sol->sprite.setPosition(xTilesSize * x, yTilesSize * y);
					Sol->sprite.setScale(xSpriteScale, ySpriteScale);

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

void Motor::RestartLevel()
{
	LoadLevel(level->pathTileMap, level->pathElements, level->mapIndex, level->levelIndex);
}

void Motor::Fade(Int64 fadeSpeed, int coef)
{
	Clock fadeClock;

	// Fond
	Texture backgroundTexture;
	backgroundTexture.create(window->getSize().x, window->getSize().y);
	backgroundTexture.update(*window);

	Sprite background;
	background.setPosition(0, 0);
	background.setTexture(backgroundTexture);

	int fade = 255;

	while (window->isOpen() && fade > 50)
	{
		// toutes les fadeSpeed
		if (fadeClock.getElapsedTime().asMicroseconds() % fadeSpeed == 0)
		{
			fade -= coef;
			background.setColor(Color(255, 255, 255, fade));
		}

		window->clear(Color::Black);
		window->draw(background);
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