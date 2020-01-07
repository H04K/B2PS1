#pragma once
#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;

class GameElement;

class Collider
{
	Vector2f* position = nullptr;
	Vector2f size;
public:
	Collider() = default;
	Collider(Vector2f* position, Vector2f size);
	
	bool CheckPushCollison(Collider& other);
	bool CheckPushCollison(Collider other, float push);

	bool CheckStopCollison(Collider other, float otherVelocity);

	void Move(float offsetx, float offsety) { Move(Vector2f(offsetx, offsety)); }
	void Move(Vector2f offset) { *position += offset; }

	Vector2f getPosition() { return *position; }
	Vector2f getSize() { return Vector2f(size.x, size.y); }
};
