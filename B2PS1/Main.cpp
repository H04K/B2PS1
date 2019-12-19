#include "Motor.h"

int main()
{
	Ressources ressources;

	RenderWindow window(VideoMode(Ressources::WindowSize.width, Ressources::WindowSize.height), "Brain Adventure", Style::Close | Style::Resize | Style::Titlebar);



	Motor GameMotor = Motor(window);
	GameMotor.MainMenu();

	return EXIT_SUCCESS;
}