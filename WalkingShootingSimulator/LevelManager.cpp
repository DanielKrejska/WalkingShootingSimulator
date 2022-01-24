#pragma warning(disable : 26495)
#pragma warning(disable : 4267)
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
		int strlen = stringFilePath.size() - 9;
		menuString += to_string(++mapsNum) + ") " +
			stringFilePath.substr(5, strlen) + '\n';
		if (mapsNum == MAX_MAP_NUM) break;
	}
	for (int i = mapsNum + 1; i < MAX_MAP_NUM + 1; i++)
		menuString += to_string(i) + ") [SLOT EMPTY]\n";
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
		arrayMap = nullptr;
		wallPositions.clear();
		mapSize.x = mapSize.y = 0;
	}
}

bool LevelManager::loadMap(int mapIndex, Soldier& player)
{
	if (mapIndex >= mapsNum) return false;
	this->deleteCurrentMap();
	technicalInit(mapIndex);
	graphicalInit(player);
	return true;
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

const vector<Vector2f>& LevelManager::getWalls()
{
	return wallPositions;
}
