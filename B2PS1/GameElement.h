#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Audio.hpp>
#include <SFML/GpuPreference.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <thread>
#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <list>

using namespace sf;
using namespace std;

enum class Type { Instruction, Element, Operateur, None };
enum class OperateurType { Is, And, None };
enum class ElementType { Baba, Wall, None };
enum class InstructionType { Stop, You, None };

struct Logic
{
	Type type = Type::None;

	OperateurType operateurType = OperateurType::None;
	ElementType elementType = ElementType::None;
	InstructionType instructionType = InstructionType::None;

	Logic() = default;
	Logic(Type type, OperateurType type2) : type(type), operateurType(type2) {}
	Logic(Type type, ElementType type2) : type(type), elementType(type2) {}
	Logic(Type type, InstructionType type2) : type(type), instructionType(type2) {}
};

// Pour que le type Motor soit accessible depuis la declaration des de GameElement
class Motor;

class GameElement {
protected:
	void Stop();
	void You();
public:
	list<InstructionType> instructions = list<InstructionType>();
	void ApplyLogicalEvents();

	string name = "UnamedGameElement";

	Motor* motor = nullptr;

	/*Les textures et sprites sont voué a changer pour un system animable*/
	static Texture* texture;
	Sprite sprite;
	virtual void LoadSprites();
	
	/**/
	Vector2f* position = new Vector2f();

	GameElement();
	bool GetEvent(Event& _event, Event::EventType eventType);

	virtual void Start();
	virtual void Update();
	virtual void Draw();
};

/*
Le nom Player est voué a changer pour un nom comme BABA ou autre chose
*/
class Player : public GameElement {
public:
	string name = "UnamedPlayer";

	void LoadSprites();

	void Start();
	void Update();
	void Draw();
};