#pragma once
#include "GameElement.h"

enum class NavigationChoice { MainMenu, LevelSelect, Options, Credits, Quit };

class Level {
public:
	list<GameElement*> GameElements = list<GameElement*>();
	bool isFinished = false;
};

class Motor {
private:

	//Met a jours les events a chaque appels
	void RefreshEvents();

	// Contient tout les evenements actuels
	list<Event> events = list<Event>();
public:

	Motor(RenderWindow& window) : window(&window){}
	
	NavigationChoice MainMenu();
	NavigationChoice LevelSelector();
	NavigationChoice Options();
	NavigationChoice Credits();

	void LoadLevel(string path);
	NavigationChoice Play();
	void PauseMenu();

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
		## toutes les données de l'évenement sont dans event
	}
	*/
	bool GetEvent(Event& _event, Event::EventType eventType);
};