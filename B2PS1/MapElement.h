#pragma once
#include "Components.h"

// pour pouvoir acceder au type Motor
class Motor;

class MapElement
{
public :
	Sprite sprite;
	Motor* motor = nullptr;

	virtual void LoadSprites();

	virtual void Start();
	virtual void Update();
	virtual void Draw();
};

class Floor : public MapElement
{
public:
	
	static Texture* texture;
	//Sprite sprite;

	void LoadSprites();

	void Start();
	void Update();
	void Draw();

};