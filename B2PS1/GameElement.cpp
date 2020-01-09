#include "Motor.h"

void GameElement::Stop() 
{
	for (GameElement* other : motor->level->GameElements)
		if (this != other)
			collider.CheckStopCollison(other->getCollider(), Ressources::MoveVelocity);
}
void GameElement::Push()
{
	for (GameElement* other : motor->level->GameElements)
		if (this != other)
			collider.CheckPushCollison(other->getCollider(), 1);

	for (LogicBloc* logicBloc : motor->level->LogicBlocs)
		collider.CheckPushCollison(*logicBloc->collider, 1);
}
void GameElement::Win()
{
	for (GameElement* other : motor->level->GameElements)
		if (other->Is(InstructionType::You))
			if(collider.CheckCollison(other->getCollider()))
				motor->level->isWin = true;
}
void GameElement::Death()
{
	bool isEnd = false;

	while(!isEnd)
	{
		GameElement* target = nullptr;

		for (auto itr = motor->level->GameElements.begin() ; itr != motor->level->GameElements.end(); itr++)
		{
			GameElement* other = itr._Ptr->_Myval;

			if (other->Is(InstructionType::You) && collider.CheckCollison(other->getCollider()))
			{
				target = other;
				break;
			}

			auto itrCheck = itr;
			if (++itrCheck == motor->level->GameElements.end())
				isEnd = true;
		}

		list<GameElement*> newGameElements = list<GameElement*>();

		for (GameElement* gameElement : motor->level->GameElements)
			if (gameElement != target)
				newGameElements.push_back(gameElement);

		motor->level->GameElements = newGameElements;
	}
	

	/*for (GameElement* other : motor->level->GameElements)
	{
		if (other != nullptr && other->Is(InstructionType::You))
			if (collider.CheckCollison(other->getCollider()))
			{
				list<GameElement*> newGameElements = list<GameElement*>();

				for (GameElement* gameElement : motor->level->GameElements)
					if (gameElement != other)
						newGameElements.push_back(gameElement);

				motor->level->GameElements = newGameElements;
			}
	}*/
}

void GameElement::ApplyLogicInstructions()
{
	for (InstructionType instruction : logicInstructions)
	{
		switch (instruction)
		{
		case InstructionType::Stop: Stop(); break;
		case InstructionType::You: You(); break;
		case InstructionType::Push: Push(); break;
		case InstructionType::Win: Win(); break;
		case InstructionType::Death: Death(); break;
		}
	}
}

void GameElement::You()
{
	if (Keyboard::isKeyPressed(Keyboard::Down))
		Move(0, Ressources::MoveVelocity);

	if (Keyboard::isKeyPressed(Keyboard::Up))
		Move(0, -Ressources::MoveVelocity);

	if (Keyboard::isKeyPressed(Keyboard::Right))
		Move(Ressources::MoveVelocity, 0.f);

	if (Keyboard::isKeyPressed(Keyboard::Left))
		Move(-Ressources::MoveVelocity, 0.f);

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

map<AnimatedSprite::Direction, list<Texture*>>* Brain::texturesMap = nullptr;

void Brain::You()
{
	bool isMoving = false;
	AnimatedSprite::Direction direction = AnimatedSprite::Direction::None;

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		Move(0, Ressources::MoveVelocity);
		isMoving = true;
		direction = AnimatedSprite::Direction::Down;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		Move(0, -Ressources::MoveVelocity);
		isMoving = true;
		direction = AnimatedSprite::Direction::Up;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		Move(Ressources::MoveVelocity, 0.f);
		isMoving = true;
		direction = AnimatedSprite::Direction::Right;
	}
	if (Keyboard::isKeyPressed(Keyboard::Left))
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
	collider = Collider(&this->position, Vector2f(animatedSprite.getSize().x, animatedSprite.getSize().y));
	Start();
}

Vector2f Brain::getSize()
{
	return Vector2f(animatedSprite.getSize().x, animatedSprite.getSize().y);
}

void Brain::setSize(Vector2f size)
{
	animatedSprite.setSize(size);
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
	collider = Collider(&this->position, Vector2f(animatedSprite.getSize().x, animatedSprite.getSize().y));
	Start();
}

Vector2f Wall::getSize()
{
	return Vector2f(animatedSprite.getSize().x, animatedSprite.getSize().x);
}

void Wall::setSize(Vector2f size)
{
	animatedSprite.setSize(size);
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

	animatedSprite.animDelay = 350;
	animatedSprite.SetTextures(*Wall::texturesMap, Vector2f(64, 64));
}

void Wall::Start() {}
void Wall::Update() {}

void Wall::Draw()
{
	animatedSprite.Animate();
	animatedSprite.Draw();
}






Neurone::Neurone(Motor* motor, Vector2f position, ElementType type)
{
	this->motor = motor;
	this->position = position;
	this->type = type;
	this->size = Vector2f(64, 64);

	LoadSprites();
	collider = Collider(&this->position, shape.getSize());
	Start();
}

Vector2f Neurone::getSize()
{
	return shape.getSize();
}

void Neurone::setSize(Vector2f size)
{
	this->size = size;
	shape.setSize(size);
}

Texture* Neurone::texture = nullptr;

void Neurone::LoadSprites()
{
	if (Neurone::texture == nullptr)
	{
		texture = new Texture();

		if (Neurone::texture->loadFromFile("Assets/Sprites/neurone.png"))
		{
			texture->setRepeated(true);
			texture->setSmooth(true);
		}
	}

	shape.setTexture(Neurone::texture);
	shape.setOrigin(size / 2.0f);
	shape.setPosition(position);
	shape.setSize(size);
	shape.setScale(getScale());
}

void Neurone::Start() {}
void Neurone::Update() {}

void Neurone::Draw()
{
	shape.setPosition(position);
	motor->window->draw(shape);
}



Door::Door(Motor* motor, Vector2f position, ElementType type)
{
	this->motor = motor;
	this->position = position;
	this->type = type;
	this->size = Vector2f(64, 64);

	LoadSprites();
	collider = Collider(&this->position, shape.getSize());
	Start();
}

Vector2f Door::getSize()
{
	return shape.getSize();
}

void Door::setSize(Vector2f size)
{
	this->size = size;
	shape.setSize(size);
}

Texture* Door::texture = nullptr;

void Door::LoadSprites()
{
	if (Door::texture == nullptr)
	{
		texture = new Texture();

		if (Door::texture->loadFromFile("Assets/Sprites/door.png"))
		{
			texture->setRepeated(true);
			texture->setSmooth(true);
		}
	}

	shape.setTexture(Door::texture);
	shape.setOrigin(size / 2.0f);
	shape.setPosition(position);
	shape.setSize(size);
	shape.setScale(getScale());
}

void Door::Start() {}
void Door::Update() {}

void Door::Draw()
{
	shape.setPosition(position);
	motor->window->draw(shape);
}





Key::Key(Motor* motor, Vector2f position, ElementType type)
{
	this->motor = motor;
	this->position = position;
	this->type = type;
	this->size = Vector2f(64, 64);

	LoadSprites();
	collider = Collider(&this->position, shape.getSize());
	Start();
}

Vector2f Key::getSize()
{
	return shape.getSize();
}

void Key::setSize(Vector2f size)
{
	this->size = size;
	shape.setSize(size);
}

Texture* Key::texture = nullptr;

void Key::LoadSprites()
{
	if (Key::texture == nullptr)
	{
		texture = new Texture();

		if (Key::texture->loadFromFile("Assets/Sprites/key.png"))
		{
			texture->setRepeated(true);
			texture->setSmooth(true);
		}
	}

	shape.setTexture(Key::texture);
	shape.setOrigin(size / 2.0f);
	shape.setPosition(position);
	shape.setSize(size);
	shape.setScale(getScale());
}

void Key::Start() {}
void Key::Update() {}

void Key::Draw()
{
	shape.setPosition(position);
	motor->window->draw(shape);
}





Spike::Spike(Motor* motor, Vector2f position, ElementType type)
{
	this->motor = motor;
	this->position = position;
	this->type = type;
	this->size = Vector2f(64, 64);

	LoadSprites();
	collider = Collider(&this->position, shape.getSize());
	Start();
}

Vector2f Spike::getSize()
{
	return shape.getSize();
}

void Spike::setSize(Vector2f size)
{
	this->size = size;
	shape.setSize(size);
}

Texture* Spike::texture = nullptr;

void Spike::LoadSprites()
{
	if (Spike::texture == nullptr)
	{
		texture = new Texture();

		if (Spike::texture->loadFromFile("Assets/Sprites/spike.png"))
		{
			texture->setRepeated(true);
			texture->setSmooth(true);
		}
	}

	shape.setTexture(Spike::texture);
	shape.setOrigin(size / 2.0f);
	shape.setPosition(position);
	shape.setSize(size);
	shape.setScale(getScale());
}

void Spike::Start() {}
void Spike::Update() {}

void Spike::Draw()
{
	shape.setPosition(position);
	motor->window->draw(shape);
}




Pillar::Pillar(Motor* motor, Vector2f position, ElementType type)
{
	this->motor = motor;
	this->position = position;
	this->type = type;
	this->size = Vector2f(64, 64);

	LoadSprites();
	collider = Collider(&this->position, shape.getSize());
	Start();
}

Vector2f Pillar::getSize()
{
	return shape.getSize();
}

void Pillar::setSize(Vector2f size)
{
	this->size = size;
	shape.setSize(size);
}

Texture* Pillar::texture = nullptr;

void Pillar::LoadSprites()
{
	if (Pillar::texture == nullptr)
	{
		texture = new Texture();

		if (Pillar::texture->loadFromFile("Assets/Sprites/pillar.png"))
		{
			texture->setRepeated(true);
			texture->setSmooth(true);
		}
	}

	shape.setTexture(Pillar::texture);
	shape.setOrigin(size / 2.0f);
	shape.setPosition(position);
	shape.setSize(size);
	shape.setScale(getScale());
}

void Pillar::Start() {}
void Pillar::Update() {}

void Pillar::Draw()
{
	shape.setPosition(position);
	motor->window->draw(shape);
}