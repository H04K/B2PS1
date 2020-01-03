#include "Motor.h"

void MapElement::Start() {}
void MapElement::LoadSprites(){}

void MapElement::Update(){}
void MapElement::Draw(){}

Texture* Floor::texture = nullptr;

void Floor::LoadSprites()
{

	if (texture == nullptr)
	{
		texture = new Texture;
		string path = "Assets/tileset2.png";
	
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

void Floor::Start() {
	
}

Texture* Bounds::texture = nullptr;

void Bounds::LoadSprites()
{
	if (texture == nullptr)
	{
		texture = new Texture;
		string path = "Assets/tileset1.png";

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

void Bounds::Update() {}

void Bounds::Draw()
{
	motor->window->draw(sprite);
}

void Bounds::Start() {

}
