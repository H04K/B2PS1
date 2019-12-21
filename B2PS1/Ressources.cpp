#include "Motor.h"

Ressources::windowSize Ressources::WindowSize = Ressources::windowSize(1600, 900);
// w -> 1300 mini


Font Ressources::Font_Arial = Font();
Font Ressources::Font_BlackGround = Font();
Font Ressources::Font_LemonJuice = Font();
Font Ressources::Font_Ouders = Font();
Font Ressources::Font_TheAbsolute = Font();
Font Ressources::Font_TheAbsoluteBrush = Font();
Font Ressources::Font_MedievalScroll = Font();

Ressources::Ressources()
{
	Ressources::Font_Arial.loadFromFile("Assets/Fonts/arial_narrow_7.ttf");
	Ressources::Font_BlackGround.loadFromFile("Assets/Fonts/Black Ground.ttf");
	Ressources::Font_LemonJuice.loadFromFile("Assets/Fonts/Lemon Juice.otf");
	Ressources::Font_Ouders.loadFromFile("Assets/Fonts/Ouders.ttf");
	Ressources::Font_TheAbsolute.loadFromFile("Assets/Fonts/TheAbsolute.otf");
	Ressources::Font_TheAbsoluteBrush.loadFromFile("Assets/Fonts/TheAbsoluteBrush.otf");
	Ressources::Font_MedievalScroll.loadFromFile("Assets/Fonts/Medieval Scroll of Wisdom.ttf");
}

Vector2f Ressources::realTextSize(Text& text)
{
	return Vector2f(text.getLocalBounds().width + text.getLetterSpacing() * 2, text.getLocalBounds().height + text.getLocalBounds().height / 1.5);
}