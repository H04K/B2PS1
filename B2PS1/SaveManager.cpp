#include "Motor.h"

SaveManager::SaveManager(Motor& motor) : motor(&motor) 
{
	// construit la liste de map pour pouvoir sauvgarder dedans

	ifstream mapsConfigFile("Assets/Levels/mapsConfig.json", ifstream::binary);
	Json::Value mapsConfig;
	mapsConfigFile >> mapsConfig;

	bool isFirstLevel = true;
	for (Json::Value& mapConfig : mapsConfig)
	{
		vector<SaveLevel> levels = vector<SaveLevel>();

		for (Json::Value level : mapConfig["levels"])
			if (!level["map"])
				if (isFirstLevel)
				{
					levels.push_back(SaveLevel(true, 0));
					isFirstLevel = false;
				}
				else
					levels.push_back(SaveLevel(false, -1));

		Maps.push_back(levels);
	}
}

int SaveManager::getLevelsDone()
{
	int levelsDone = 0;

	for (vector<SaveLevel>& levels : Maps)
		for (SaveLevel& level : levels)
			if (level.isUnlocked)
				levelsDone++;

	this->levelsDone = levelsDone;
	return levelsDone;
}

int SaveManager::getLevelsCount()
{
	int levelsCount = 0;

	for (vector<SaveLevel>& levels : Maps)
		for (SaveLevel& level : levels)
			levelsCount++;

	this->levelsCount = levelsCount;
	return levelsCount;
}

void SaveManager::LoadGame()
{
	ifstream slotFile("Assets/Saves/Slot" + to_string(SaveSlot) + ".json", ifstream::binary);
	Json::Value slotValue;
	slotFile >> slotValue;

	name = slotValue["name"].asString();
	levelsDone = slotValue["levelsDone"].asInt(); // pas très utilise mais c'est la

	for (int i = 0; i < slotValue["maps"].size(); i++)
		for (int j = 0; j < slotValue["maps"][i].size(); j++)
		{
			Maps[i][j].timeDone = slotValue["maps"][i][j]["bestTime"].asFloat();
			Maps[i][j].isUnlocked = slotValue["maps"][i][j]["unlocked"].asBool();
		}
}

void SaveManager::SaveGame()
{
	levelsCount = getLevelsCount();
	levelsDone = getLevelsDone();

	Json::Value slotValue;
	Json::Reader reader;

	string json = "{\"name\" : \"Roger\",";
	json += "\"levelsDone\" : " + to_string(levelsDone) + ",";
	json += "\"maps\" : [";

	for (int i = 0; i < Maps.size(); i++)
	{
		json += "[";

		for (int j = 0; j < Maps[i].size(); j++)
		{
			json += "{";

			if (Maps[i][j].isUnlocked)
				json += "\"unlocked\" : true,";
			else
				json += "\"unlocked\" : false,";

			json += "\"bestTime\" : " + to_string(Maps[i][j].timeDone);

			if (j + 1 != Maps[i].size())
				json += "},";
			else
				json += "}";
		}

		if (i + 1 != Maps.size())
			json += "],";
		else
			json += "]";
	}

	json += "]}";

	reader.parse(json, slotValue);

	ofstream slotFile("Assets/Saves/Slot" + to_string(SaveSlot) + ".json", ofstream::binary);
	slotFile << slotValue;
	slotFile.close();

	cout << "succesful save Slot " << SaveSlot << endl;
}

void SaveManager::EmptySlot(int index)
{
	Json::Value slotValue;
	Json::Reader reader;

	reader.parse("{\"isEmpty\" : true}", slotValue);

	ofstream slotFile("Assets/Saves/Slot" + to_string(index) + ".json", ofstream::binary);
	slotFile << slotValue;
	slotFile.close();
}