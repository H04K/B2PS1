#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include "json//json.h"

// pour pouvoir acceder au type motor
class Motor;

class SaveManager
{
public:

	struct SaveLevel
	{
		bool isWon;
		float timeDone;
		SaveLevel(bool isWon, float timeDone) : isWon(isWon), timeDone(timeDone){}
	};

	Motor* motor = nullptr;
	SaveManager(Motor& motor);

	int SaveSlot = -1;
	vector<vector<SaveLevel>> Maps = vector<vector<SaveLevel>>();

	void BuildNewSave();
	void LoadGame();
	void SaveGame();
};