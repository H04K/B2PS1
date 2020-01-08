#pragma once
#include "Components.h"

// pour pouvoir acceder au type Motor
class Motor;

class MapElement
{
public :
	Sprite sprite;
	Motor* motor = nullptr;

	virtual void LoadSprites() {};

	virtual void Start() {};
	virtual void Update() {};
	virtual void Draw() {};
	virtual void Destroy() {};
};

class Floor : public MapElement
{
public:
	static Texture* texture;

	void LoadSprites();

	void Start();
	void Update();
	void Draw();
	void Destroy()
	{
		if (texture != nullptr)
		{
			delete texture;
			texture = nullptr;
		}
	}
};

class Bound : public MapElement
{
	static Texture* texture;
public:

	void LoadSprites();
	void Start();
	void Update();
	void Draw();
	void Destroy()
	{
		if (texture != nullptr)
		{
			delete texture;
			texture = nullptr;
		}
	}
};