#include "Motor.h"

int main()
{
	Ressources ressources;

	RenderWindow window(VideoMode(Ressources::WindowSize.width, Ressources::WindowSize.height), "Brain Adventure", Style::Close | Style::Titlebar);
	Motor GameMotor = Motor(window);

	while (window.isOpen())
	{
		static NavigationChoice NavChoice = NavigationChoice::MainMenu;

		switch (NavChoice)
		{
		case NavigationChoice::MainMenu :
			NavChoice = GameMotor.MainMenu();
			break;
		case NavigationChoice::SelectSaveSlot:
			NavChoice = GameMotor.SelectSaveSlot();
			break;
		case NavigationChoice::LevelSelect :
			NavChoice = GameMotor.LevelSelect();
			break;
		case NavigationChoice::Options :
			NavChoice = GameMotor.Options();
			break;
		case NavigationChoice::Credits :
			NavChoice = GameMotor.Credits();
			break;
		case NavigationChoice::Play:
			NavChoice = GameMotor.Play();
			break;
		case NavigationChoice::Quit :
			return EXIT_SUCCESS;
		}
	}

	return EXIT_SUCCESS;
}