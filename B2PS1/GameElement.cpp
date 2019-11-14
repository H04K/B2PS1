#include "Motor.h"

GameElement::GameElement() 
{

}

bool GameElement::GetEvent(Event& _event, Event::EventType eventType)
{
	for (Event event : *events)
	{
		if (event.type == eventType)
		{
			_event = event;
			return true;
		}
	}

	return false;
}

void GameElement::Start(list<Event>* events)
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




Player::Player() 
{

}

void Player::Start(list<Event>* events)
{
	cout << "--- Starting " + name << endl;

	this->events = events;

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
	Event event;
	if (GetEvent(event, Event::KeyPressed))
	{
		cout << event.key.code << endl;
	}
}

void Player::Draw(RenderWindow& window)
{
	//cout << "Drawing " + name << endl;
	window.draw(sprite);
}

void Player::Destroy()
{
	cout << "Destroying " + name << endl;
}