#include "Motor.h"

Texture* Floor::texture = nullptr;

void Floor::LoadSprites()
{
	if (texture == nullptr)
	{
		texture = new Texture;
		string path = "Assets/Sprites/TileMap/tileset2.png";

		if (texture->loadFromFile(path))
		{
			texture->setSmooth(true);
			texture->setRepeated(true);
		}
		else
		{
			cout << "can't load " + path << endl;
		}
	}

	sprite.setTexture(*texture);
}

void Floor::Update() {}

void Floor::Draw()
{
	motor->window->draw(sprite);
}

void Floor::Start() {}


Texture* Bound::texture = nullptr;

void Bound::LoadSprites()
{
	if (texture == nullptr)
	{
		texture = new Texture;
		string path = "Assets/Sprites/TileMap/tileset1.png";

		if (texture->loadFromFile(path))
		{
			texture->setSmooth(true);
			texture->setRepeated(true);
		}
		else
		{
			cout << "can't load " + path << endl;
		}
	}

	sprite.setTexture(*texture);
}

void Bound::Update() {}

void Bound::Draw()
{
	motor->window->draw(sprite);
}

void Bound::Start() {}