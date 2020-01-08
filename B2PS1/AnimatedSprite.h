#pragma once
#include <SFML/Graphics.hpp>
#include <list>


using namespace sf;
using namespace std;

// pour pouvoir acceder au type GameElement
class GameElement;

class AnimatedSprite
{
private:
	GameElement* gameElement = nullptr;
	list<Texture>* textures = nullptr;
public:
	
	enum class Direction { Right, Left, Up, Down, None };

	struct Range
	{
		Direction direction;
		int min;
		int max;
		Range(Direction direction, int min, int max) : direction(direction), min(min), max(max) {}
	};

	Direction currentDirection = Direction::None;
	Direction lastDirection;
	map<Direction, vector<RectangleShape>> spritesMap = map<Direction, vector<RectangleShape>>();

	Clock clock = Clock();

	AnimatedSprite(GameElement& gameElement) : gameElement(&gameElement) {};
	~AnimatedSprite() {};

	int maxFrame = NULL;
	int currentFrame = 0;
	int animDelay = 100;

	RectangleShape getSprite();
	Vector2f getSize();
	
	void setSize(float sizeX, float sizeY);
	void setSize(Vector2f size);

	static void loadTexturesFromRange(map<AnimatedSprite::Direction, list<Texture*>>* texturesMap, list<Range>& ranges, string path, string pathend);

	void SetTextures(list<Texture*>& textures);
	void SetTextures(list<Texture*>& textures, Vector2f size);
	void SetTextures(map<Direction, list<Texture*>>& texturesMap);
	void SetTextures(map<Direction, list<Texture*>>& texturesMap, Vector2f size);

	void Animate();
	void Animate(bool isMoving);
	void Animate(bool isMoving, Direction direction);

	void Draw();
};