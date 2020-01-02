#include "Motor.h"

int main()
{
	Ressources ressources;

	RenderWindow window(VideoMode(Ressources::WindowSize.width, Ressources::WindowSize.height), "Brain Adventure", Style::Close | Style::Resize | Style::Titlebar);
	Motor GameMotor = Motor(window);
	Floor* tempo = new Floor;
	
	NavigationChoice NavChoice = NavigationChoice::MainMenu;
	GameMotor.LoadGame("Assets/Levels/level0.csv","Assets/Levels/level1.csv");

	GameMotor.Play();
	/*while (true)
	{
		switch (NavChoice)
		{
		case NavigationChoice::MainMenu :
			NavChoice = GameMotor.MainMenu();
			break;
		case NavigationChoice::LevelSelect :
			NavChoice = GameMotor.LevelSelector();
			break;
		case NavigationChoice::Options :
			NavChoice = GameMotor.Options();
			break;
		case NavigationChoice::Credits :
			NavChoice = GameMotor.Credits();
			break;
		case NavigationChoice::Quit :
			return EXIT_SUCCESS;
		}
	}*/

	return EXIT_SUCCESS;
}