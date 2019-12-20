#include "Motor.h"

void GameElement::Stop() 
{
	cout << "ca stop bien la" << endl;
}
void GameElement::You()
{
	bool isMoving = false;
	AnimatedSprite::Direction direction = AnimatedSprite::Direction::None;

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		Move(0, 0.75f);
		isMoving = true;
		direction = AnimatedSprite::Direction::Down;
	}
	if (Keyboard::isKeyPressed(Keyboard::Z))
	{
		Move(0, -0.75f);
		isMoving = true;
		direction = AnimatedSprite::Direction::Up;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		Move(0.75f, 0.f);
		isMoving = true;
		direction = AnimatedSprite::Direction::Right;
	}
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		Move(-0.75f, 0.f);
		isMoving = true;
		direction = AnimatedSprite::Direction::Left;
	}
	
	animatedSprite.Animate(isMoving, direction);
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
GameElement::~GameElement() {}
void GameElement::Start() {}
void GameElement::Update() {}
void GameElement::Draw() {}

list<InstructionType> Brain::LogicInstructions = list<InstructionType>();
map<AnimatedSprite::Direction, list<Texture*>>* Brain::texturesMap = nullptr;

void Brain::LoadSprites()
{
	string path = "Assets/Sprites/Brain/brain";
	string pathEnd = ".png";

	list<AnimatedSprite::Range> ranges = 
	{
		AnimatedSprite::Range(AnimatedSprite::Direction::Up, 0, 3),
		AnimatedSprite::Range(AnimatedSprite::Direction::Down, 4, 7),
		AnimatedSprite::Range(AnimatedSprite::Direction::Right, 8, 11),
		AnimatedSprite::Range(AnimatedSprite::Direction::Left, 12, 15)
	};

	if (Brain::texturesMap == nullptr)
	{
		Brain::texturesMap = new map<AnimatedSprite::Direction, list<Texture*>>();

		for (AnimatedSprite::Range range : ranges)
		{
			list<Texture*> textures = list<Texture*>();

			for (int i = range.min; i <= range.max; i++)
			{
				Texture* texture = new Texture();

				if (texture->loadFromFile(path + to_string(i) + pathEnd))
				{
					texture->setRepeated(true);
					texture->setSmooth(true);
					textures.push_back(texture);
					cout << "Sucessfull Loaded " << path << i << pathEnd << endl;
				}
				else
				{
					delete Brain::texturesMap;
					Brain::texturesMap = nullptr;
					cout << "Can't load " << path << i << pathEnd << endl;
					return;
				}
			}

			Brain::texturesMap->insert(make_pair(range.direction, textures));
		}
	}

	animatedSprite.animDelay = 100;
	animatedSprite.SetTextures(*Brain::texturesMap);
}

void Brain::Start()
{
	logicInstructions = &Brain::LogicInstructions;
}

void Brain::Update()
{
}

void Brain::Draw()
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