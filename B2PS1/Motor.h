#pragma once
#include "GameElement.h"

constexpr auto WindowWidth = 800;;
constexpr auto WindowHeight = 600;;

class Level {
public:
	list<GameElement*> GameElements = list<GameElement*>();
};

class Motor {
public:
	Motor();

	void LoadLevel(string path);
	void Play(RenderWindow &window);

	// La fenetre dans laquelle tout les objets sont rendu
	RenderWindow* window = nullptr;
	
	// Le niveau actuel
	Level* level = nullptr;
	bool isLevelEnded = false;

	bool isLogicSequenceValid(vector<Logic>& sequence);

	// Contient tout les evenements actuels
	list<Event> events = list<Event>();

	/*
	Recupere et met a jours les events a chaque tour de boucle
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