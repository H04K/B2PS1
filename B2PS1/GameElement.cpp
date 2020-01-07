#include "Motor.h"

void GameElement::Stop() 
{
	for (GameElement* other : motor->level->GameElements)
		if (this != other)
			collider.CheckStopCollison(other->getCollider(), Ressources::MoveVelocity);
}
void GameElement::You()
{
	if (Keyboard::isKeyPressed(Keyboard::S))
		Move(0, Ressources::MoveVelocity);

	if (Keyboard::isKeyPressed(Keyboard::Z))
		Move(0, -Ressources::MoveVelocity);

	if (Keyboard::isKeyPressed(Keyboard::D))
		Move(Ressources::MoveVelocity, 0.f);

	if (Keyboard::isKeyPressed(Keyboard::Q))
		Move(-Ressources::MoveVelocity, 0.f);

	for (LogicBloc* logicBloc : motor->level->LogicBlocs)
		collider.CheckPushCollison(*logicBloc->collider, 1);
}

void GameElement::Push()
{
	for (GameElement* other : motor->level->GameElements)
		if (this != other)
			collider.CheckPushCollison(other->getCollider(), 1);

	for (LogicBloc* logicBloc : motor->level->LogicBlocs)
		collider.CheckPushCollison(*logicBloc->collider, 1);
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

GameElement::GameElement(Motor* motor, Vector2f position, ElementType type) : motor(motor), position(position), type(type) 
{
	LoadSprites();
	Start();
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
		case InstructionType::Push:
			Push();
			break;
		}
	}
}

map<AnimatedSprite::Direction, list<Texture*>>* Brain::texturesMap = nullptr;

void Brain::You()
{
	bool isMoving = false;
	AnimatedSprite::Direction direction = AnimatedSprite::Direction::None;

	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		Move(0, Ressources::MoveVelocity);
		isMoving = true;
		direction = AnimatedSprite::Direction::Down;
	}
	if (Keyboard::isKeyPressed(Keyboard::Z))
	{
		Move(0, -Ressources::MoveVelocity);
		isMoving = true;
		direction = AnimatedSprite::Direction::Up;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		Move(Ressources::MoveVelocity, 0.f);
		isMoving = true;
		direction = AnimatedSprite::Direction::Right;
	}
	if (Keyboard::isKeyPressed(Keyboard::Q))
	{
		Move(-Ressources::MoveVelocity, 0.f);
		isMoving = true;
		direction = AnimatedSprite::Direction::Left;
	}

	animatedSprite.Animate(isMoving, direction);

	for (LogicBloc* logicBloc : motor->level->LogicBlocs)
		collider.CheckPushCollison(*logicBloc->collider, 1);
}

Brain::Brain(Motor* motor, Vector2f position, ElementType type)
{
	this->motor = motor;
	this->position = position;
	this->type = type;

	LoadSprites();
	collider = Collider(&this->position, Vector2f(animatedSprite.getLocalBounds().width, animatedSprite.getLocalBounds().height));
	Start();
}

Vector2f Brain::getSize()
{
	return Vector2f(animatedSprite.getLocalBounds().width, animatedSprite.getLocalBounds().height);
}

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

void Brain::Start() {}

void Brain::Update() {}

void Brain::Draw()
{
	animatedSprite.Draw();
}

map<AnimatedSprite::Direction, list<Texture*>>* Wall::texturesMap = nullptr;

Wall::Wall(Motor* motor, Vector2f position, ElementType type)
{
	this->motor = motor;
	this->position = position;
	this->type = type;

	LoadSprites();
	cout << "Wall LocalBounds : " << animatedSprite.getLocalBounds().width << ',' << animatedSprite.getLocalBounds().height << endl;
	collider = Collider(&this->position, Vector2f(animatedSprite.getLocalBounds().width, animatedSprite.getLocalBounds().height));
	Start();
}

Vector2f Wall::getSize()
{
	return Vector2f(animatedSprite.getLocalBounds().width, animatedSprite.getLocalBounds().height);
}

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

void Wall::Start() {}
void Wall::Update() {}

void Wall::Draw()
{
	animatedSprite.Animate();
	animatedSprite.Draw();
}