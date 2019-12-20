#include "Motor.h"

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
			sprite.setPosition(gameElement->position);

			sprites.push_back(sprite);
		}

		spritesMap.insert(make_pair(itr->first, sprites));
	}

	if (spritesMap.count(currentDirection))
		maxFrame = spritesMap[currentDirection].size();
	else if (spritesMap.count(Direction::None))
		maxFrame = spritesMap[Direction::None].size();
	else
		cout << "can't found sprite Direction " << (int)currentDirection << " in sprites map" << endl;
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
	}*/
}

void AnimatedSprite::Draw()
{
	static Direction lastDirection;

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
		spritesMap[currentDirection][currentFrame].setPosition(gameElement->position);
		gameElement->motor->window->draw(spritesMap[currentDirection][currentFrame]);
	}
	else
		cout << "Draw : can't found sprite Direction " << (int)currentDirection << " in sprites map" << endl;

	lastDirection = currentDirection;
}