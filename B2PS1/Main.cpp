#include "Motor.h"

enum class Type { Instruction, Element, Operateur, None };
enum class OperateurType { Is, And, None };
enum class ElementType { Baba, Wall, None };
enum class InstructionType { Stop, You, None };

struct Logic
{
	Type logicType = Type::None;

	OperateurType operateurType = OperateurType::None;
	ElementType elementType = ElementType::None;
	InstructionType instructionType = InstructionType::None;

	Logic() = default;
	Logic(Type logicalType, OperateurType type2) : logicType(logicalType), operateurType(type2) {}
	Logic(Type logicalType, ElementType type2) : logicType(logicalType), elementType(type2) {}
	Logic(Type logicalType, InstructionType type2) : logicType(logicalType), instructionType(type2) {}
};

bool LogicSequenceIsValid(Logic sequence[], unsigned int size)
{
	int validConditions = 0;

	for (int i = 0; i < size; i++)
	{
		cout << "------Index " << i << endl;
 		cout << "Type " << (int)sequence[i].logicType << endl;

		if (i == 0 && sequence[i].logicType == Type::Element)
		{
			cout << "l'index " << i << " est un Element" << endl;
			validConditions++;
		}

		else if (i != 0 && i % 1 == 0 && sequence[i].logicType == Type::Operateur)
		{
			cout << "l'index " << i << " est un Operateur (" << i % 2 << ")" << endl;
			validConditions++;
		}

		else if (i % 2 == 0 && sequence[i].logicType == Type::Element || sequence[i].logicType == Type::Instruction)
		{
			cout << "l'index " << i << " est un Element ou une instruction (" << i % 1 << ")" << endl;
			validConditions++;
		}

		
		if (i == size && sequence[i].logicType == Type::Operateur) 
		{
			cout << "le dernier index ( " << i << " n'est pas valide" << endl;
			validConditions--;
		}
	}

	cout << "ValidConditions " << validConditions << endl;

	if (validConditions == size)
		return true;
	return false;
}

int main()
{
	Logic sequence[5];

	sequence[0] = Logic(Type::Element, ElementType::Wall);
	sequence[1] = Logic(Type::Operateur, OperateurType::Is);
	sequence[2] = Logic(Type::Instruction, InstructionType::Stop);
	sequence[3] = Logic(Type::Operateur, OperateurType::And);
	sequence[4] = Logic(Type::Operateur, OperateurType::Is);

	if (LogicSequenceIsValid(sequence, 5))
		cout << "YES" << endl;
	else
		cout << "paouf" << endl;

	cin.get();

	/*
	RenderWindow window(VideoMode(800, 600), "Baba is You 2", Style::Close | Style::Resize | Style::Titlebar);

	Motor GameMotor;

	GameMotor.SetLevel(0);
	GameMotor.Play(window);
	*/
	return EXIT_SUCCESS;
}