#include "LevelManager.h"
#include <filesystem>
using std::filesystem::directory_iterator;

LevelManager::LevelManager()
{
	mapsNum = 0;
	string path = "maps/";
	for (const auto& file : directory_iterator(path))
	{
		auto filePath = file.path();
		string stringFilePath = filePath.string();
		mapNames.push_back(stringFilePath);
		menuString += to_string(++mapsNum) + ") " + stringFilePath + '\n';
	}
}

const string& LevelManager::getMenuString()
{
	return menuString;
}
