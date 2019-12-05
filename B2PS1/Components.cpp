#include "Components.h"
#include "Motor.h"

void AnimatedSprite::SetTextures(list<Texture*>& textures)
{
	maxFrame = textures.size() - 1;

	for (Texture* texture : textures)
	{
		Sprite sprite = Sprite();
		sprite.setTexture(*texture);
		sprite.setPosition(gameElement->position);
		sprites.push_back(sprite);
	}
}

void AnimatedSprite::Animate()
{
	Time time = clock.getElapsedTime();

	if (time.asMicroseconds() >= animDelay)
	{
		if (currentFrame >= maxFrame)
			currentFrame = 0;
		else
			currentFrame++;
		clock.restart();
	}
}

void AnimatedSprite::Draw()
{
	for (int i = 0; i < maxFrame + 1; i++)
		sprites[i].setPosition(gameElement->position);

	gameElement->motor->window->draw(sprites[currentFrame]);
}
