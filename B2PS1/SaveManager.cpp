#include "Motor.h"

SaveManager::SaveManager(Motor& motor) : motor(&motor) 
{
	// construit la liste de map pour pouvoir sauvgarder dedans

	ifstream mapsConfigFile("Assets/Levels/mapsConfig.json", ifstream::binary);
	Json::Value mapsConfig;
	mapsConfigFile >> mapsConfig;

	for (Json::Value& mapConfig : mapsConfig)
	{
		vector<SaveLevel> levels = vector<SaveLevel>();

		for (Json::Value level : mapConfig["levels"])
			if(!level["map"])
				levels.push_back(SaveLevel(false, -1));

		Maps.push_back(levels);
	}
}

void SaveManager::BuildNewSave()
{
	Json::Value slotValue;
	Json::Reader reader;

	string json = "{\"name\" : \"Roger\",";
	json += "\"maps\" : [";

	for (int i = 0; i < Maps.size(); i++)
	{
		json += "[";

		for (int j = 0; j < Maps[i].size(); j++)
		{
			json += "{";

			if(i == 0 && j == 0)
				json += "\"unlocked\" : true,";
			else
				json += "\"unlocked\" : false,";
			
			json += "\"bestTime\" : -1";

			if (j + 1 != Maps[i].size())
				json += "},";
			else
				json += "}";
		}

		if(i + 1 != Maps.size())
			json += "],";
		else
			json += "]";
	}

	json += "]}";

	reader.parse(json, slotValue);

	ofstream slotFile("Assets/Saves/Slot" + to_string(SaveSlot) + ".json", ofstream::binary);
	slotFile << slotValue;
	slotFile.close();
}

void SaveManager::LoadGame()
{
	
}

void SaveManager::SaveGame()
{

	Json::Value slotValue;
	Json::Reader reader;


	// sauvegarde

	/*
	string outputJson = "{}";
	reader.parse(outputJson, outputJsonValue);
	*/


	ofstream slotFile("Assets/Saves/Slot" + to_string(SaveSlot) + ".json", ofstream::binary);
	slotFile << slotValue;
	slotFile.close();
}
