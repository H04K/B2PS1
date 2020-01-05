#include "Motor.h"

Collider::Collider(Vector2f* position, FloatRect localBounds)
{
	this->position = position;
	this->localBounds = localBounds;
}

bool Collider::CheckCollison(Collider& other) { return CheckCollison(other, 0); }

bool Collider::CheckCollison(Collider& other, float push)
{
	Vector2f otherPosition = other.getPosition();
	Vector2f otherHalfSize = other.getSize() / 2.f;

	Vector2f thisPosition = getPosition();
	Vector2f thisHalfSize = getSize() / 2.f;

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);	// abs = valeur absolue
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f) 
	{
		push = min(max(push, 0.0f), 1.0f);	//clamping

		if (intersectX > intersectY)
		{ 
			// dans le cas ou il a plus de collision en y que en x pour eviter que ca pousse en diagonale 

			if (deltaX > 0.0f) 
			{
				Move(intersectX * (1.0f, push), 0.0f);
				other.Move(-intersectX * push, 0.0f);
			}
			else
			{
				Move(-intersectX * (1.0f, push), 0.0f);
				other.Move(intersectX * push, 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * (1.0f, push));
				other.Move(0.0f, -intersectY * push);
			}
			else
			{
				Move(0.0f, -intersectY * (1.0f, push));
				other.Move(0.0f, intersectY * push);
			}
		}
		return true;
	}
	return false;
}
