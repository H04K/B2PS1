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

void GameElement::Move(float offsetx, float offsety)
{
	position.x += offsetx;
	position.y += offsety;
}

void GameElement::Move(Vector2f offset)
{
	position += offset;
}

bool GameElement::Is(InstructionType instructionType)
{
	for (InstructionType& instruction : logicInstructions)
		if (instruction == instructionType)
			return true;
	return false;
}

void GameElement::ApplyLogicInstructions()
{
	for (InstructionType instruction : logicInstructions)
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

map<AnimatedSprite::Direction, list<Texture*>>* Brain::texturesMap = nullptr;

void Brain::LoadSprites()
{
	if (Brain::texturesMap == nullptr)
	{
		texturesMap = new map<AnimatedSprite::Direction, list<Texture*>>();

		list<AnimatedSprite::Range> ranges =
		{
			AnimatedSprite::Range(AnimatedSprite::Direction::Up, 0, 3),
			AnimatedSprite::Range(AnimatedSprite::Direction::Down, 4, 7),
			AnimatedSprite::Range(AnimatedSprite::Direction::Right, 8, 11),
			AnimatedSprite::Range(AnimatedSprite::Direction::Left, 12, 15)
		};

		AnimatedSprite::loadTexturesFromRange(Brain::texturesMap, ranges, "Assets/Sprites/Brain/brain", ".png");
	}
	
	animatedSprite.animDelay = 100;
	animatedSprite.SetTextures(*Brain::texturesMap);
}

void Brain::Start(){}

void Brain::Update()
{
}

void Brain::Draw()
{
	animatedSprite.Draw();
}

map<AnimatedSprite::Direction, list<Texture*>>* Wall::texturesMap = nullptr;

void Wall::LoadSprites()
{
	if (Wall::texturesMap == nullptr)
	{
		texturesMap = new map<AnimatedSprite::Direction, list<Texture*>>();

		list<AnimatedSprite::Range> ranges =
		{
			AnimatedSprite::Range(AnimatedSprite::Direction::None, 0, 2)
		};

		AnimatedSprite::loadTexturesFromRange(Wall::texturesMap, ranges, "Assets/Sprites/Wall/wall", ".png");
	}

	animatedSprite.animDelay = 500;
	animatedSprite.SetTextures(*Wall::texturesMap);
}

void Wall::Start(){}

void Wall::Update()
{
	
}

void Wall::Draw()
{
	animatedSprite.Animate();
	animatedSprite.Draw();
}