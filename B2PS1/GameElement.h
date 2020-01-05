#pragma once

#include "LogicSequenceManager.h"
#include "SaveManager.h"
#include "Ressources.h"
#include "MapElement.h"

// Pour que le type Motor soit accessible depuis la declaration de GameElement
class Motor;

class GameElement 
{
protected:
	void Stop();
	void You();

	void Move(float offsetx, float offsety);
	void Move(Vector2f offset);

public:
	ElementType type = ElementType::None;

	bool Is(InstructionType instructionType);
	list<InstructionType> logicInstructions = list<InstructionType>();
	void ApplyLogicInstructions();
	
	Vector2f position = Vector2f();
	Motor* motor = nullptr;

	AnimatedSprite animatedSprite = AnimatedSprite(*this);
	virtual void LoadSprites() {}

	Collider* collider = nullptr;

	GameElement() : type(ElementType::None) {}
	~GameElement() { delete collider;};

	virtual void Start() {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual void Destroy() {}
};

class Brain : public GameElement 
{
public:

	Brain() { type = ElementType::Brain; }

	static map<AnimatedSprite::Direction, list<Texture*>>* texturesMap;
	void LoadSprites();

	void Start();
	void Update();
	void Draw();
	void Destroy()
	{
		if (texturesMap != nullptr)
		{
			delete texturesMap;
			texturesMap = nullptr;
		}
	}
};

class Wall : public GameElement 
{
public:

	Wall() { type = ElementType::Wall; }

	static map<AnimatedSprite::Direction, list<Texture*>>* texturesMap;

	void LoadSprites();
	void Start();
	void Update();
	void Draw();
	void Destroy()
	{
		if (texturesMap != nullptr)
		{
			delete texturesMap;
			texturesMap = nullptr;
		}
	}
};