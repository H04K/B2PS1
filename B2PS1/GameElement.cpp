#include "Motor.h"

GameElement::GameElement() {}
void GameElement::Stop() {}
void GameElement::You() {}

list<InstructionType>* GameElement::instructions = new list<InstructionType>();

void GameElement::ApplyLogicalEvents()
{
	for (InstructionType instruction : *instructions)
	{
		switch (instruction)
		{
		case InstructionType::Stop:
			Stop();
			break;
		case InstructionType::You:
			You();
			break;
		case InstructionType::None:
			break;
		}
	}
}
Texture* GameElement::texture = nullptr;

void GameElement::LoadSprites() {}

bool GameElement::GetEvent(Event& _event, Event::EventType eventType)
{
	for (Event event : motor->events)
	{
		if (event.type == eventType)
		{
			_event = event;
			return true;
		}
	}

	return false;
}

void GameElement::Start() {}
void GameElement::Update() {}
void GameElement::Draw() {};



void Player::LoadSprites()
{
	string path = "Assets/Sprites/Player/baba_0_1.png";

	if (texture == nullptr)
	{
		texture = new Texture();

		if (texture->loadFromFile(path))
		{
			sprite.setTexture(*texture);
			sprite.setPosition(*position);

			cout << "Successful Loaded " << path << endl;
		}
	}
	else
	{
		sprite.setTexture(*texture);
		sprite.setPosition(*position);

		cout << "Successful Loaded " << path << endl;
	}
}

void Player::Start()
{

}

void Player::Update()
{
	/*TEMPORAIRE en attendant que le system d'evenements logiques soit fini*/

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
	motor->window->draw(sprite);
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
	motor->window->draw(Limite);
}

void Instructions::Start()
{
	Inst.setPosition(InstPos);
	
	
}

void Instructions::Update()
{
	Vector2i mpos = Mouse::getPosition(*motor->window);
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
	motor->window->draw(Inst);
}