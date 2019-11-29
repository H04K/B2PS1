#include "Motor.h"

int main()
{
	RenderWindow window(VideoMode(WindowWidth, WindowHeight), "Baba is You 2", Style::Close | Style::Resize | Style::Titlebar);

	Motor GameMotor;

	GameMotor.LoadLevel("Assets/Levels/Level0.csv231");
	GameMotor.Play(window);
	
	return EXIT_SUCCESS;
}