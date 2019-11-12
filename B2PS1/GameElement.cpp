#include "GameElement.h"

void GameElement::Start() 
{
	cout << "Starting " + name << endl;
}

void GameElement::Update()
{
	cout << "Updating " + name << endl;
}

void GameElement::Draw(RenderWindow& window) {
	cout << "Drawing " + name << endl;
};

void GameElement::Destroy() 
{
	cout << "Destroying " + name << endl;
}

void Player::Start() 
{
	cout << "--- Starting " + name << endl;

	string path = "Assets/baba_0_1.png";

	if (texture.loadFromFile(path))
	{
		sprite.setTexture(texture);
		sprite.setPosition(position);

		cout << "Successful Loaded " << path << endl;
	}
	else {}
}

void Player::Update()
{
	//cout << "Updating " + name << endl;

}

void Player::Draw(RenderWindow &window) 
{
	//cout << "Drawing " + name << endl;
	window.draw(sprite);
}

void Player::Destroy() 
{
	cout << "Destroying " + name << endl;
}