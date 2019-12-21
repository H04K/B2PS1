#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

using namespace std;

enum class LogicType { Instruction, Element, Operateur, None };
enum class OperateurType { Is, And, None };
enum class ElementType { Brain, Wall, None };
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

// pour pouvoir acceder au type Motor
class Motor;

class LogicSequenceManager
{
private:
	Motor* motor = nullptr;
public:
	LogicSequenceManager(Motor& motor) : motor(&motor) {}

	void sendSequence(string code);
	bool isSequenceValid(list<Logic>& logicSequence);
	void applySequence(list<Logic>& logicSequence);

	void morphGameElement(ElementType oldType, ElementType newType);
};