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

	IntRect rectSourceSprite(0, 0, 28, 32);
	
	if (!texture.loadFromFile("Assets/baba/sprite2.png"))
	{
		// erreur...
	}
	texture.setRepeated(true);
	texture.setSmooth(true);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(rectSourceSprite));
}

void Player::Start()
{

}

void Player::Update()
{
	/*TEMPORAIRE en attendant que le system d'evenements logiques soit fini*/
	IntRect rectSourceSprite(0, 0, 28, 32);

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		sprite.setTextureRect(rectSourceSprite);
		sprite.move(0, 1 / 10.f);
		
	}
	if (Keyboard::isKeyPressed(Keyboard::Z))
	{
		sprite.move(0, -1 / 10.f);
		rectSourceSprite.top += 96;
		sprite.setTextureRect(rectSourceSprite);
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		sprite.move(1 / 10.f, 0.f);
		rectSourceSprite.top += 64;
		sprite.setTextureRect(rectSourceSprite);
	}
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		
		sprite.move(-1 / 10.f, 0.f);
		rectSourceSprite.top += 32;
		sprite.setTextureRect(rectSourceSprite);
		
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