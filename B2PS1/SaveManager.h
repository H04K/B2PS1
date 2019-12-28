#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include "json//json.h"

// pour pouvoir acceder au type motor
class Motor;

class SaveManager
{
	int levelsCount = 0;
	int levelsDone = 0;
public:

	struct SaveLevel
	{
		bool isUnlocked;
		float timeDone;
		SaveLevel(bool isUnlocked, float timeDone) : isUnlocked(isUnlocked), timeDone(timeDone){}
	};

	Motor* motor = nullptr;
	SaveManager(Motor& motor);

	int SaveSlot = -1;
	string name = "Roger";

	int getLevelsDone();
	int getLevelsCount();

	vector<vector<SaveLevel>> Maps = vector<vector<SaveLevel>>();

	void LoadGame();
	void SaveGame();
	void EmptySlot(int index);
};