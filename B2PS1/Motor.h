#pragma once
#include "GameElement.h"

class Level {
public:
	int TileMap[10][10];

	list<GameElement*> GameElements = list<GameElement*>();
};

class Motor {
public:
	Motor();

	void SetLevel(int index);
	void Play(RenderWindow &window);

//private:
	// La fenetre dans laquelle tout les objets sont rendu
	RenderWindow* window;
	
	// Le niveau actuel
	Level* level;

	// Contient tout les evenements actuels
	list<Event> events = list<Event>();

	void RefreshEvents();

	/****/
	bool GetEvent(Event& _event, Event::EventType eventType);
};