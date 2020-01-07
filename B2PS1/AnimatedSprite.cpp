#include "Motor.h"

Sprite AnimatedSprite::getSprite()
{
	for (int direction = 0; direction <= (int)Direction::None; direction++)
	{
		if (spritesMap.count((Direction)direction))
			return spritesMap[(Direction)direction][0];
	}

	return Sprite();
}

FloatRect AnimatedSprite::getLocalBounds()
{
	for (int direction = 0; direction <= (int)Direction::None; direction++)
	{
		if (spritesMap.count((Direction)direction))
			return spritesMap[(Direction)direction][0].getLocalBounds();
	}

	return FloatRect();
}

void AnimatedSprite::loadTexturesFromRange(map<AnimatedSprite::Direction, list<Texture*>>* texturesMap, list<Range>& ranges, string path, string pathend)
{
	for (AnimatedSprite::Range& range : ranges)
	{
		list<Texture*> textures = list<Texture*>();

		for (int i = range.min; i <= range.max; i++)
		{
			Texture* texture = new Texture();

			if (texture->loadFromFile(path + to_string(i) + pathend))
			{
				texture->setRepeated(true);
				texture->setSmooth(true);
				textures.push_back(texture);
				cout << "Sucessfull Loaded " << path << i << pathend << endl;
			}
			else
			{
				delete texturesMap;
				texturesMap = nullptr;
				cout << "Can't load " << path << i << pathend << endl;
				return;
			}
		}

		texturesMap->insert(make_pair(range.direction, textures));
	}
}

void AnimatedSprite::SetTextures(list<Texture*>& textures)
{
	map<Direction, list<Texture*>> _textures = map<Direction, list<Texture*>>();
	_textures.insert(make_pair(Direction::None, textures));

	SetTextures(_textures);
}

void AnimatedSprite::SetTextures(map<Direction, list<Texture*>>& texturesMap)
{
	for (auto itr = texturesMap.begin(); itr != texturesMap.end(); itr++)
	{
		vector<Sprite> sprites = vector<Sprite>();

		for (Texture* texture : itr->second)
		{
			Sprite sprite = Sprite();
			sprite.setTexture(*texture);
			sprite.setOrigin((Vector2f)texture->getSize() / 2.0f);
			sprite.setPosition(gameElement->getPosition());
			sprite.setScale(gameElement->getScale());

			sprites.push_back(sprite);
		}

		spritesMap.insert(make_pair(itr->first, sprites));
	}

	if (spritesMap.count(currentDirection))
		maxFrame = spritesMap[currentDirection].size();

	else if (spritesMap.count(Direction::None))
		maxFrame = spritesMap[Direction::None].size();
}

void AnimatedSprite::Animate() { Animate(true, Direction::None); }
void AnimatedSprite::Animate(bool isMoving) { Animate(isMoving, Direction::None); }
void AnimatedSprite::Animate(bool isMoving, Direction direction)
{
	Time time = clock.getElapsedTime();

	if (spritesMap.count(direction))
		currentDirection = direction;

	if (time.asMilliseconds() >= animDelay)
	{
		if (isMoving)
			currentFrame = (currentFrame + 1) % maxFrame;
		else if (currentFrame != 0)
			currentFrame--;

		clock.restart();
	}
}

void AnimatedSprite::Draw()
{
	if (currentDirection != lastDirection)
	{
		currentFrame = 0;
		if (spritesMap.count(currentDirection))
			maxFrame = spritesMap[currentDirection].size();

		else if (spritesMap.count(lastDirection))
		{
			maxFrame = spritesMap[lastDirection].size();
			currentDirection = lastDirection;
		}
		else if (spritesMap.count(Direction::None))
		{
			maxFrame = spritesMap[Direction::None].size();
			currentDirection = Direction::None;
		}
		else
			cout << "Change direction : can't found sprite Direction " << (int)currentDirection << " in sprites map" << endl;
	}

	if (spritesMap.count(currentDirection))
	{
		spritesMap[currentDirection][currentFrame].setPosition(gameElement->getPosition());
		gameElement->getMotor()->window->draw(spritesMap[currentDirection][currentFrame]);
	}
	else
		cout << "Draw : can't found sprite Direction " << (int)currentDirection << " in sprites map" << endl;

	lastDirection = currentDirection;
}