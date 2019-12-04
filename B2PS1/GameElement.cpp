#include "Motor.h"

void GameElement::Stop() 
{
	cout << "�a stop bien la" << endl;
}
void GameElement::You() 
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

void GameElement::ApplyLogicInstructions()
{
	for (InstructionType instruction : *logicInstructions)
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

GameElement::GameElement() {}
GameElement::~GameElement() {}

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
void GameElement::Draw() {}

list<InstructionType> Player::LogicInstructions = list<InstructionType>();

Texture* Player::texture = nullptr;

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
	logicInstructions = &Player::LogicInstructions;
}

void Player::Update()
{
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