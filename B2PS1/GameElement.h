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
	virtual void You();
	virtual void Push();
	virtual void Stop();
	virtual void Win();
	virtual void Death();

	void Move(float offsetx, float offsety);
	void Move(Vector2f offset);

	Vector2f position;
	Vector2f scale = Vector2f(1,1);
	Collider collider;
	
	Motor* motor = nullptr;

	virtual void LoadSprites() {};

public:

	ElementType type = ElementType::None;
	bool Is(InstructionType instructionType);
	list<InstructionType> logicInstructions = list<InstructionType>();		
	void ApplyLogicInstructions();

	Vector2f getPosition() { return position; }	void setPosition(Vector2f position) { this->position = position; }
	Vector2f getScale() { return scale; } void setScale(Vector2f scale) { this->scale = scale; }
	virtual Vector2f getSize() { return Vector2f(); };
	virtual void setSize(float sizeX, float sizeY) {}
	virtual void setSize(Vector2f size) {}

	Collider& getCollider() { return collider; }

	Motor* getMotor() { return motor; }

	GameElement() = default;
	GameElement(Motor* motor, Vector2f position, ElementType type);
	~GameElement() {}

	virtual void Start() {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual void Destroy() {}
};

class Brain : public GameElement 
{
	void You();
	AnimatedSprite animatedSprite = AnimatedSprite(*this);
public:

	Brain(Motor* motor, Vector2f position, ElementType type);

	Vector2f getSize();
	void setSize(Vector2f size);

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
	AnimatedSprite animatedSprite = AnimatedSprite(*this);
public:

	Wall(Motor* motor, Vector2f position, ElementType type);

	Vector2f getSize();
	void setSize(Vector2f size);

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