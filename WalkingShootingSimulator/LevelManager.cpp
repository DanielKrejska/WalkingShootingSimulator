#pragma warning(disable : 26495)
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
	menuString += "0) exit";
}

LevelManager::~LevelManager()
{
	deleteCurrentMap();
}

void LevelManager::deleteCurrentMap()
{
	if (arrayMap != nullptr)
	{
		for (int i = 0; i < mapSize.y; i++)
		{
			delete[] arrayMap[i];
		}
		delete[] arrayMap;
		delete pVertexMap;
	}
}

void LevelManager::loadMap(int mapIndex)
{
	technicalInit(mapIndex);
	graphicalInit();
}

const VertexArray* LevelManager::getVertexMap()
{
	return pVertexMap;
}

const string& LevelManager::getMenuString()
{
	return menuString;
}

int LevelManager::getMapsNum()
{
	return mapsNum;
}
