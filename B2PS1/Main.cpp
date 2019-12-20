#include "Motor.h"

int main()
{
	Ressources ressources;

	RenderWindow window(VideoMode(Ressources::WindowSize.width, Ressources::WindowSize.height), "Brain Adventure", Style::Close | Style::Resize | Style::Titlebar);
	Motor GameMotor = Motor(window);

	NavigationChoice NavChoice = NavigationChoice::MainMenu;

	while (true)
	{
		switch (NavChoice)
		{
		case NavigationChoice::MainMenu :
			NavChoice = GameMotor.MainMenu();
			break;
		case NavigationChoice::LevelSelect:
			NavChoice = GameMotor.LevelSelector();
			break;
		case NavigationChoice::Options:
			NavChoice = GameMotor.Options();
			break;
		case NavigationChoice::Credits:
			NavChoice = GameMotor.Credits();
			break;
		case NavigationChoice::Quit:
			return EXIT_SUCCESS;
		}
	}

	
	/*
	Pour faire fonctionner le code une fois, le jeu lancé il faut appuyer sur "f"
	et écrire "player is you" dans la console et appuyer sur Entrer pour pouvoir controler ensuite le joueur avec les touches "Z,Q,S,D"
	*/

	return EXIT_SUCCESS;
}