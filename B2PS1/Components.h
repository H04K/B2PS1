#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Audio.hpp>
#include <SFML/GpuPreference.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <thread>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
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
public :

	AnimatedSprite(GameElement& gameElement) : gameElement(&gameElement){};
	~AnimatedSprite() {};
	
	vector<Sprite> sprites = vector<Sprite>();
	
	Clock clock = Clock();

	int maxFrame = NULL;
	int currentFrame = 0;
	int animDelay = 50000;

	void SetTextures(list<Texture*>& textures);
	void Animate();
	void Draw();
};