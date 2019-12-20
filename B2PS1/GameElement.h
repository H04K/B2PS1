#pragma once

#include "LogicSequenceManager.h"
#include "Ressources.h"
#include "MapElement.h"

// Pour que le type Motor soit accessible depuis la declaration de GameElement
class Motor;

class GameElement {
protected:
	void Stop();
	void You();

	void Move(float x, float y);

public:
	ElementType type = ElementType::None;

	list<InstructionType>* logicInstructions = nullptr;
	void ApplyLogicInstructions();

	string name = "Unamed";
	Vector2f position = Vector2f();
	Motor* motor = nullptr;

	AnimatedSprite animatedSprite = AnimatedSprite(*this);
	virtual void LoadSprites();

	GameElement() : type(ElementType::None) {}
	~GameElement();

	virtual void Start();
	virtual void Update();
	virtual void Draw();
};


class Brain : public GameElement {
public:
	static list<InstructionType> LogicInstructions;

	//static Texture* texture;
	static map<AnimatedSprite::Direction, list<Texture*>>* texturesMap;

	Brain() { type = ElementType::Brain; }
	~Brain() {}

	void LoadSprites();

	void Start();
	void Update();
	void Draw();
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