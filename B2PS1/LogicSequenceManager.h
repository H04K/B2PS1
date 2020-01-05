#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

using namespace std;
using namespace sf;

// logic
enum class LogicType { Instruction, Element, Operateur, None };
enum class OperateurType { Is, And, None };
enum class ElementType { Brain, Wall, None };
enum class InstructionType { Stop, You, None };

// logic Bloc
enum class HitDirection { Up, Down, Left, Right };
enum class SequencePosition { Begin, Intermediate, End, None };

// pour pouvoir acceder au type Motor & au type Collider
class Motor;
class Collider;

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

class LogicBloc
{
public:
	LogicBloc(Color color, Vector2f size, Vector2f position, Logic logicType);
	~LogicBloc() { delete collider; }

	Motor* motor = nullptr;

	RectangleShape body;
	Vector2f position;
	Collider* collider = nullptr;

	void Move(float offsetx, float offsety) { position += Vector2f(offsetx, offsety); }

	Logic logicType;
	SequencePosition sequencePosition = SequencePosition::None;
	map<HitDirection, LogicBloc*> collidedMap = map<HitDirection, LogicBloc*>();

	void CheckCollision(list<LogicBloc*>& logicBlocs);

	void Draw();
};

class LogicSequenceManager
{
	Motor* motor = nullptr;
public:
	LogicSequenceManager(Motor& motor) : motor(&motor) {}

	void sendSequence(string code);

	void buildSequence(list<LogicBloc*>& logicBlocs);
	bool isSequenceValid(list<Logic>& logicSequence);
	void applySequence(list<Logic>& logicSequence);

	void morphGameElement(ElementType oldType, ElementType newType);
};