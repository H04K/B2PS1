#pragma once
#include "GameElement.h"

enum class NavigationChoice { Stay, MainMenu, SelectSaveSlot, LevelSelect, Options, Credits, Play, Quit };

struct NavPair {
	NavigationChoice NavChoice;
	string Wording;
	NavPair(NavigationChoice NavChoice, string Wording) : NavChoice(NavChoice), Wording(Wording) {}
};

struct Level 
{
	list<GameElement*> GameElements = list<GameElement*>();
	list<MapElement*> MapElements = list<MapElement*>();
	bool isWin = false;
	float timeDone = 0.f;

	int mapIndex = -1, levelIndex = -1;
	string pathTileMap = "", pathElements = "";
};

class Motor {
private:
	//Met a jours les events a chaque appel
	void RefreshEvents();

	// Contient tout les evenements actuel
	list<Event> events = list<Event>();

	void LoadLevel(string pathTileMap, string pathElements, int mapIndex, int levelIndex);
	void LoadElements(string path);
	void LoadTileMap(string path);
	void RestartLevel();

	// Gere les sauvgardes
	SaveManager* saveManager = nullptr;

	// Gere les sequences logiques
	LogicSequenceManager logicSequenceManager = LogicSequenceManager(*this);
public:

	Motor(RenderWindow& window) : window(&window){}
	~Motor() { delete level; delete saveManager; }
	
	NavigationChoice MainMenu();
	NavigationChoice SelectSaveSlot();
	NavigationChoice LevelSelect();
	NavigationChoice Options();
	NavigationChoice Credits();

	NavigationChoice Play();
	NavigationChoice PauseMenu(NavPair buttonsData[3]);

	// Fade the screan while @param
	void Fade(Int64 fadeSpeed);

	// La fenetre dans laquelle tout les objets sont rendu
	RenderWindow* window = nullptr;

	// le niveau actuel
	Level* level = nullptr;

	/*
	Utilisation Type de GetEvent() :
	Event event;
	if (GetEvent(event, Event::##l'event voulu)
	{
		## si il y a eut l'evenement
		## toutes les donn�es de l'�venement sont dans event
	}
	*/
	bool GetEvent(Event& _event, Event::EventType eventType);
};