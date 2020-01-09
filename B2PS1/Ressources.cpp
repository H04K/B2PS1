#include "Motor.h"

Ressources::windowSize Ressources::WindowSize = Ressources::windowSize(1500, 900);
// w -> 1300 mini

float Ressources::MoveVelocity = 1.0f;

Texture Ressources::Texture_LogicBrain = Texture();
Texture Ressources::Texture_LogicWall = Texture();
Texture Ressources::Texture_LogicNeurone = Texture();
Texture Ressources::Texture_LogicDoor = Texture();
Texture Ressources::Texture_LogicKey = Texture();
Texture Ressources::Texture_LogicPillar = Texture();
Texture Ressources::Texture_LogicSpike = Texture();

Texture Ressources::Texture_LogicIs = Texture();
Texture Ressources::Texture_LogicAnd = Texture();

Texture Ressources::Texture_LogicYou = Texture();
Texture Ressources::Texture_LogicStop = Texture();
Texture Ressources::Texture_LogicPush = Texture();
Texture Ressources::Texture_LogicWin = Texture();
Texture Ressources::Texture_LogicDefeat = Texture();

Font Ressources::Font_Arial = Font();
Font Ressources::Font_BlackGround = Font();
Font Ressources::Font_LemonJuice = Font();
Font Ressources::Font_Ouders = Font();
Font Ressources::Font_TheAbsolute = Font();
Font Ressources::Font_TheAbsoluteBrush = Font();
Font Ressources::Font_MedievalScroll = Font();

Ressources::Ressources()
{
	Texture_LogicBrain.loadFromFile("Assets/Sprites/LogicBlocs/brain.png");
	Texture_LogicWall.loadFromFile("Assets/Sprites/LogicBlocs/text_wall_0_1.png");
	Texture_LogicNeurone.loadFromFile("Assets/Sprites/LogicBlocs/");
	Texture_LogicDoor.loadFromFile("Assets/Sprites/LogicBlocs/");
	Texture_LogicKey.loadFromFile("Assets/Sprites/LogicBlocs/");
	Texture_LogicPillar.loadFromFile("Assets/Sprites/LogicBlocs/");
	Texture_LogicSpike.loadFromFile("Assets/Sprites/LogicBlocs/");


	Texture_LogicIs.loadFromFile("Assets/Sprites/LogicBlocs/text_is_0_1.png");
	Texture_LogicAnd.loadFromFile("Assets/Sprites/LogicBlocs/text_and_0_1.png");
	Texture_LogicWin.loadFromFile("Assets/Sprites/LogicBlocs/text_win_0_1.png");

	Texture_LogicYou.loadFromFile("Assets/Sprites/LogicBlocs/text_you_0_1.png");
	Texture_LogicStop.loadFromFile("Assets/Sprites/LogicBlocs/text_stop_0_1.png");
	Texture_LogicPush.loadFromFile("Assets/Sprites/LogicBlocs/text_push_0_1.png");
	Texture_LogicWin.loadFromFile("Assets/Sprites/LogicBlocs/text_win_0_1.png");
	Texture_LogicWin.loadFromFile("Assets/Sprites/LogicBlocs/text_win_0_1.png");
	Texture_LogicDefeat.loadFromFile("Assets/Sprites/LogicBlocs/text_defeat_0_1.png");

	Font_Arial.loadFromFile("Assets/Fonts/arial_narrow_7.ttf");
	Font_BlackGround.loadFromFile("Assets/Fonts/Black Ground.ttf");
	Font_LemonJuice.loadFromFile("Assets/Fonts/Lemon Juice.otf");
	Font_Ouders.loadFromFile("Assets/Fonts/Ouders.ttf");
	Font_TheAbsolute.loadFromFile("Assets/Fonts/TheAbsolute.otf");
	Font_TheAbsoluteBrush.loadFromFile("Assets/Fonts/TheAbsoluteBrush.otf");
	Font_MedievalScroll.loadFromFile("Assets/Fonts/Medieval Scroll of Wisdom.ttf");
}

Vector2f Ressources::realTextSize(Text& text)
{
	return Vector2f(text.getLocalBounds().width + text.getLetterSpacing() * 2, text.getLocalBounds().height + text.getLocalBounds().height / 1.5);
}