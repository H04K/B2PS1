#include "Motor.h"

int main()
{
	Ressources ressources;

	RenderWindow window(VideoMode(Ressources::WindowSize.width, Ressources::WindowSize.height), "Brain Adventure", Style::Close | Style::Resize | Style::Titlebar);



	Motor GameMotor = Motor(window);
	GameMotor.MainMenu();
	GameMotor.LoadGame("Assets/Levels/level0.csv", "Assets/Levels/level1.csv");
	/*GameMotor.LoadMap("Assets/Levels/level0.csv");
	GameMotor.LoadLevel("Assets/Levels/level1.csv");*/
	GameMotor.Play();
	/*
	
	Pour faire fonctionner le code une fois, le jeu lancé il faut appuyer sur "f"
	et écrire "player is you" dans la console et appuyer sur Entrer pour pourvoir controler ensuite le joueur avec les touches "Z,Q,S,D"
	
	*/


	return EXIT_SUCCESS;
}