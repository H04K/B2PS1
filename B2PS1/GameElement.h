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
	Texture texture;
	Sprite sprite;
	Vector2f position = Vector2f(100, 100);

	//void LogicalEvent(LogicalEvent logicalEvent);

	list<Event>* events = nullptr;
	RenderWindow* window = nullptr;

	bool GetEvent(Event& _event, Event::EventType eventType);

	GameElement();

	virtual void Init(RenderWindow* window, list<Event>* events);
	virtual void Start();
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
};

class Player : public GameElement {
public:
	string name = "UnamedPlayer";

	Player();
	void Start();
	void Update();
	void Draw();
	void Destroy();
};

class Lim : public GameElement
{
public:

	Vector2i mpos = Mouse::getPosition();
	RectangleShape Limite = RectangleShape(Vector2f(1024.f, 10.f));
	Vector2f Lpos = Vector2f(0.f, 700.f);
	void Start();
	void Update();
	void Draw();
};

class Instructions : public GameElement
{
public:
	
	
	
	RectangleShape Inst = RectangleShape(Vector2f(70.f, 70.f));
	Vector2f InstPos = Vector2f(500.f, 500.f);
	
	void Start();
	void Update();
	void Draw();

 };