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

void GameElement::Init(RenderWindow* window, list<Event>* events)
{
	this->window = window;
	this->events = events;
}

void GameElement::Start()
{
	cout << "Starting " + name << endl;
}

void GameElement::Update()
{
	cout << "Updating " + name << endl;
}

void GameElement::Draw() {
	cout << "Drawing " + name << endl;
};

void GameElement::Destroy()
{
	cout << "Destroying " + name << endl;
}




Player::Player() 
{

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
	if (Keyboard::isKeyPressed(Keyboard::S)) 
	{
		sprite.move(0, 1 / 3.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Z))
	{
		sprite.move(0, -1 / 3.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		sprite.move(1 / 3.f, 0.f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		sprite.move(-1 / 3.f, 0.f);
	}
}

void Player::Draw()
{
	window->draw(sprite);
}

void Player::Destroy()
{
	cout << "Destroying " + name << endl;
}

void Lim::Start()
{
	Limite.setPosition(Lpos);
}

void Lim::Update()
{
	
}
void Lim::Draw()
{
	window->draw(Limite);
}

void Instructions::Start()
{
	Inst.setPosition(InstPos);
	
	
}

void Instructions::Update()
{
	Vector2i mpos = Mouse::getPosition(*window);
	FloatRect Opos = Inst.getGlobalBounds();
	if (Mouse::isButtonPressed(Mouse::Left) && Opos.contains(mpos.x, mpos.y))
	{

		Inst.setPosition(mpos.x - 30, mpos.y - 30);
		if (Opos.top >= 700.f)
		{
			Inst.setPosition(0.f, 700.f);
		}

	}
}

void Instructions::Draw()
{
	window->draw(Inst);
}