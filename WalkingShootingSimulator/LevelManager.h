#pragma once
#pragma warning(disable : 4244)
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Soldier.h"
#include "Target.h"
using namespace std;
using namespace sf;

class LevelManager
{
private:
	vector<string> mapNames;
	string menuString;

	int mapsNum;

	// size of current level in tiles
	Vector2i mapSize;

	VertexArray* pVertexMap;
	char** arrayMap = nullptr;
	vector<Vector2f> wallPositions;

	void deleteCurrentMap();
	void technicalInit(int mapIndex);
	void graphicalInit(Soldier& player, vector<Target>& targets);

public:
	LevelManager();

	static const int TILE_SIZE = 50;
	static const int MAX_MAP_NUM = 9;

	bool loadMap(int mapIndex, Soldier& player, vector<Target>& targets);

	const VertexArray* getVertexMap();
	const string& getMenuString();
	int getMapsNum();
	const vector<Vector2f>& getWalls();

	~LevelManager();
};
