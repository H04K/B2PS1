#pragma once
#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;

class GameElement;

class Collider
{
	Vector2f* position = nullptr;
	FloatRect localBounds;
public:
	Collider(Vector2f* position, FloatRect localBounds);
	
	bool CheckCollison(Collider& other);
	bool CheckCollison(Collider& other, float push);

	void Move(float offsetx, float offsety) { Move(Vector2f(offsetx, offsety)); }
	void Move(Vector2f offset) { *position += offset; }

	Vector2f getPosition() { return *position; }
	Vector2f getSize() { return Vector2f(localBounds.height, localBounds.width); }
};
