#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Audio.hpp>
#include <SFML/GpuPreference.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <list>

using namespace sf;
using namespace std;

enum LogicalEvent
{
	None,
	Win,
	Loose
};

class GameElement {
protected:
	//void Win();
	//void Loose();
public:
	string name = "UnamedGameElement";
	Vector2f position = Vector2f(100, 100);

	Texture texture;
	Sprite sprite;

	//void LogicalEvent(LogicalEvent logicalEvent);

	list<Event>* events = nullptr;
	bool GetEvent(Event& _event, Event::EventType eventType);

	GameElement();

	virtual void Start(list<Event>* events);
	virtual void Update();
	virtual void Draw(RenderWindow &window);
	virtual void Destroy();
};

class Player : public GameElement {
public:
	string name = "UnamedPlayer";

	Player();

	void Start(list<Event>* events);
	void Update();
	void Draw(RenderWindow& window);
	void Destroy();
};