#include "Motor.h"
#include "Levels.cpp"

int main()
{
	InitFonts();
	
	RenderWindow window(VideoMode(800, 600), "Baba is You 2", Style::Close | Style::Resize | Style::Titlebar);

	Motor GameMotor;

	GameMotor.SetLevel(0);
	GameMotor.Play(window);

	return EXIT_SUCCESS;
}