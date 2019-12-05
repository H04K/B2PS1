#include "Motor.h"

void GameElement::Stop() 
{
	cout << "�a stop bien la" << endl;
}
void GameElement::You()
{
	/*IntRect rectSourceSprite(0, 0, 28, 32);*/

	bool isMoving = false;

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		Move(0, 1 / 10.f);
		isMoving = true;
		/*sprite.move(0, 1 / 10.f); 
		sprite.setTextureRect(rectSourceSprite);*/
		
	}
	if (Keyboard::isKeyPressed(Keyboard::Z))
	{
		Move(0, -1 / 5.f);
		isMoving = true;
		/*sprite.move(0, -1 / 10.f);
		rectSourceSprite.top += 96;
		sprite.setTextureRect(rectSourceSprite);*/
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		Move(1 / 5.f, 0.f);
		isMoving = true;
		/*sprite.move(1 / 10.f, 0.f);
		rectSourceSprite.top += 64;
		sprite.setTextureRect(rectSourceSprite);*/
	}
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		Move(-1 / 5.f, 0.f);
		isMoving = true;
		/*sprite.move(-1 / 10.f, 0.f);
		rectSourceSprite.top += 32;
		sprite.setTextureRect(rectSourceSprite);*/
	}
	
	if (isMoving)
	{
		animatedSprite.Animate();
	}

}

void GameElement::Move(float x, float y)
{
	position.x += x;
	position.y += y;
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
void GameElement::Start() {}
void GameElement::Update() {}
void GameElement::Draw() {}

list<InstructionType> Player::LogicInstructions = list<InstructionType>();

//Texture* Player::texture = nullptr;
list<Texture*>* Player::textures = nullptr;

void Player::LoadSprites()
{
	string path = "Assets/Sprites/Player/baba";
	int count = 12;
	string pathEnd = ".png";

	if (Player::textures == nullptr)
	{
		Player::textures = new list<Texture*>();
		for (int i = 0; i < count; i++)
		{
			Texture* texture = new Texture();

			if (texture->loadFromFile(path + to_string(i) + pathEnd))
			{
				texture->setRepeated(true);
				texture->setSmooth(true);
				Player::textures->push_back(texture);
				
				cout << "Sucessfull Loaded " << path << i << pathEnd << endl;
			}
			else
			{
				cout << "Can't load " << path << i << pathEnd << endl;
				delete Player::textures;
				Player::textures = nullptr;
				return;
			}
		}
	}

	animatedSprite.SetTextures(*Player::textures);

	/*string path = "Assets/Sprites/Player/sprite2.png";
	IntRect rectSourceSprite(0, 0, 28, 32);

	if (Player::texture == nullptr)
	{
		Player::texture = new Texture();
		GameElement::texture = Player::texture;

		if (Player::texture->loadFromFile(path))
			cout << "Successful Loaded " << path << endl;
		else
			return;

		texture->setRepeated(true);
		texture->setSmooth(true);
	}

	sprite.setPosition(startPosition);
	sprite.setTexture(*Player::texture);
	sprite.setTextureRect(rectSourceSprite);*/
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
	animatedSprite.Draw();
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