#include "Motor.h"

bool Collider::CheckCollison(Collider& other) { return CheckPushCollison(other, 0); }
bool Collider::CheckPushCollison(Collider& other, float push)
{
	if (position == nullptr) { cout << this << " can't CheckPushCollision position is null" << endl; return false; }

	Vector2f otherPosition = other.getPosition();
	Vector2f otherHalfSize = other.getSize() / 2.f;

	Vector2f thisPosition = getPosition();
	Vector2f thisHalfSize = getSize() / 2.f;	// <-------

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

bool Collider::CheckStopCollison(Collider& other, float otherVelocity)
{
	if (position == nullptr) { cout << this << " can't CheckStopCollision position is null" << endl; return false; }

	Vector2f otherPosition = other.getPosition();
	Vector2f otherHalfSize = other.getSize() / 2.f;

	Vector2f thisPosition = getPosition();
	Vector2f thisHalfSize = getSize() / 2.f;	// <-------

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);	// abs = valeur absolue
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		//push = min(max(push, 0.0f), 1.0f);	//clamping

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
				other.Move(-intersectX * otherVelocity, 0.0f);
			else
				other.Move(intersectX * otherVelocity, 0.0f);
		}
		else
		{
			if (deltaY > 0.0f)
				other.Move(0.0f, -intersectY * otherVelocity);
			else
				other.Move(0.0f, intersectY * otherVelocity);
		}
		return true;
	}
	return false;
}