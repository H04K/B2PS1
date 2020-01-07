#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

using namespace sf;
using namespace std;

static struct Ressources
{
	Ressources();

	struct windowSize
	{
		windowSize() = default;
		windowSize(int width, int height) : width(width), height(height) {};
		
		int width = 0;
		int height = 0;
	};

	static windowSize WindowSize;

	static float MoveVelocity;

	static Texture Texture_LogicBrain;
	static Texture Texture_LogicWall;

	static Texture Texture_LogicIs;
	static Texture Texture_LogicAnd;

	static Texture Texture_LogicYou;
	static Texture Texture_LogicStop;
	static Texture Texture_LogicPush;

	static Font Font_Arial;
	static Font Font_BlackGround;
	static Font Font_LemonJuice;
	static Font Font_Ouders;
	static Font Font_TheAbsolute;
	static Font Font_TheAbsoluteBrush;
	static Font Font_MedievalScroll;

	static Vector2f realTextSize(Text& text);
};