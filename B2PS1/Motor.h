#pragma once
#include "GameElement.h"

enum class NavigationChoice { MainMenu, SelectSaveSlot, LevelSelect, Options, Credits, Play, Quit };

class Level {
public:
	list<GameElement*> GameElements = list<GameElement*>();
	list<MapElement*> MapElements = list<MapElement*>();
	bool isWin = false;
	float timeDone = 0.f;
};

class Motor {
private:
	//Met a jours les events a chaque appel
	void RefreshEvents();

	// Contient tout les evenements actuel
	list<Event> events = list<Event>();

	void LoadLevel(string pathTileMap, string pathElements);
	void LoadElements(string path);
	void LoadTileMap(string path);

	SaveManager* saveManager = nullptr;

public:

	Motor(RenderWindow& window) : window(&window){}
	~Motor() { delete level; delete saveManager; }
	
	NavigationChoice MainMenu();
	NavigationChoice SelectSaveSlot();
	NavigationChoice LevelSelect();
	NavigationChoice Options();
	NavigationChoice Credits();

	NavigationChoice Play();
	NavigationChoice PauseMenu();

	// La fenetre dans laquelle tout les objets sont rendu
	RenderWindow* window = nullptr;

	Level* level = nullptr;

	// Permet de gerer les sequences logiques
	LogicSequenceManager logicSequenceManager = LogicSequenceManager(*this);

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