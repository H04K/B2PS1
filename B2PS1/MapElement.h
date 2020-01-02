#pragma once
#include "Components.h"

// pour pouvoir acceder au type Motor
class Motor;

class MapElement
{
public :
	Sprite sprite;
	static Texture* texture;
	
	
	
	Motor* motor = nullptr;

	

	virtual void Start();
	virtual void LoadSprites();
	virtual void Update();
	virtual void Draw();
};

class Floor : public MapElement
{
public:

	void LoadSprites();

	void Start();
	void Update();
	void Draw();
};

class Bounds : public MapElement
{
public:

	void LoadSprites();
	void Start();
	void Update();
	void Draw();
};




//class Bounds : public MapElement
//{
//public:
//
//	void LoadSprites();
//	void Start();
//	void Update();
//	void Draw();
//};
//class Bounds : public MapElement
//{
//public:
//
//	void LoadSprites();
//	void Start();
//	void Update();
//	void Draw();
//};
//class Bounds : public MapElement
//{
//public:
//
//	void LoadSprites();
//	void Start();
//	void Update();
//	void Draw();
//};
//class Bounds : public MapElement
//{
//public:
//
//	void LoadSprites();
//	void Start();
//	void Update();
//	void Draw();
//};
//class Bounds : public MapElement
//{
//public:
//
//	void LoadSprites();
//	void Start();
//	void Update();
//	void Draw();
//};
//class Bounds : public MapElement
//{
//public:
//
//	void LoadSprites();
//	void Start();
//	void Update();
//	void Draw();
//};
//class Bounds : public MapElement
//{
//public:
//
//	void LoadSprites();
//	void Start();
//	void Update();
//	void Draw();
//};