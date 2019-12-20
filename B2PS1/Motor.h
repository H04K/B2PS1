#pragma once
#include "GameElement.h"

class Level {
public:
	list<GameElement*> GameElements = list<GameElement*>();
	list<MapElement*> MapElements = list<MapElement*>();
};

enum class MainMenuChoice { Quit, Play, Options, Credits };

class Motor {
private:
	// Contient tout les evenements actuels
	list<Event> events = list<Event>();
public:

	Motor(RenderWindow& window) : window(&window){}
	
	MainMenuChoice MainMenu();
	void LevelSelector();
	void LoadGame(string pathMap, string pathLevel);
	void LoadLevel(string path);
	void LoadMap(string path);
	void Play();
	void PauseMenu();

	// La fenetre dans laquelle tout les objets sont rendu
	RenderWindow* window = nullptr;

	Level* level = nullptr;
	bool isLevelEnded = false;

	// Permet de gerer les sequences logiques
	LogicSequenceManager logicSequenceManager = LogicSequenceManager(*this);

	/*
	Met a jours les events a chaque appels
	*/
	void RefreshEvents();
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