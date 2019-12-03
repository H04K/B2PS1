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

enum class LogicType { Instruction, Element, Operateur, None };
enum class OperateurType { Is, And, None };
enum class ElementType { Player, Wall, None };
enum class InstructionType { Stop, You, None };

struct Logic
{
	LogicType logicType = LogicType::None;

	OperateurType operateurType = OperateurType::None;
	ElementType elementType = ElementType::None;
	InstructionType instructionType = InstructionType::None;

	Logic() = default;
	Logic(OperateurType opType) : logicType(LogicType::Operateur), operateurType(opType) {}
	Logic(ElementType elemType) : logicType(LogicType::Element), elementType(elemType) {}
	Logic(InstructionType instrType) : logicType(LogicType::Instruction), instructionType(instrType) {}
};

// Pour que le type Motor soit accessible depuis la declaration des de GameElement
class Motor;

class GameElement {
protected:
	void Stop();
	void You();
public:
	static list<InstructionType>* instructions;
	void ApplyLogicalEvents();

	string name = "UnamedGameElement";

	Motor* motor = nullptr;

	/*Les textures et sprites sont vou� a changer pour un system animable*/

	Sprite sprite;
	Texture texture;
	
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
Le nom Player est vou� a changer pour un nom comme BABA ou autre chose
*/
class Player : public GameElement {
public:
	static list<InstructionType>* instructions;
	string name = "UnamedPlayer";

	void LoadSprites();

	void Start();
	void Update();
	void Draw();
};






class Lim : public GameElement
{
public:

	Vector2i mpos = Mouse::getPosition();
	RectangleShape Limite = RectangleShape(Vector2f(1024.f, 10.f));
	Vector2f Lpos = Vector2f(0.f, 700.f);
	void Start();
	void Update();
	void Draw();
};

class Instructions : public GameElement
{
public:
	
	RectangleShape Inst = RectangleShape(Vector2f(70.f, 70.f));
	Vector2f InstPos = Vector2f(500.f, 500.f);
	
	void Start();
	void Update();
	void Draw();
 };