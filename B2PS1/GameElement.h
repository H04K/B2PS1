#pragma once
#include "Components.h";

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

// Pour que le type Motor soit accessible depuis la declaration de GameElement
class Motor;

class GameElement {
protected:
	void Stop();
	void You();

	void Move(float x, float y);
public:
	list<InstructionType>* logicInstructions = nullptr;
	void ApplyLogicInstructions();

	string name = "Unamed";
	Vector2f position = Vector2f();
	Motor* motor = nullptr;

	/*Texture* texture;
	Sprite sprite;*/

	AnimatedSprite animatedSprite = AnimatedSprite(*this);
	virtual void LoadSprites();

	GameElement();
	~GameElement();

	virtual void Start();
	virtual void Update();
	virtual void Draw();
};

/*
Le nom Player est voué a changer pour un nom comme BABA ou autre chose
*/
class Player : public GameElement {
public:

	ElementType type = ElementType::Player;

	static list<InstructionType> LogicInstructions;

	//static Texture* texture;
	static list<Texture*>* textures;

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