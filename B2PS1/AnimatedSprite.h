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
	map<Direction, vector<Sprite>> spritesMap = map<Direction, vector<Sprite>>();

	Clock clock = Clock();

	AnimatedSprite(GameElement& gameElement) : gameElement(&gameElement) {};
	~AnimatedSprite() {};

	int maxFrame = NULL;
	int currentFrame = 0;
	int animDelay = 100;

	Sprite getSprite();
	FloatRect getLocalBounds();

	static void loadTexturesFromRange(map<AnimatedSprite::Direction, list<Texture*>>* texturesMap, list<Range>& ranges, string path, string pathend);

	void SetTextures(list<Texture*>& textures);
	void SetTextures(map<Direction, list<Texture*>>& texturesMap);

	void Animate();
	void Animate(bool isMoving);
	void Animate(bool isMoving, Direction direction);

	void Draw();
};