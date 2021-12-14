#pragma once
#pragma warning(disable : 4244)
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
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
	int** arrayMap = nullptr;

	void deleteCurrentMap();
	void technicalInit(int mapIndex);
	void graphicalInit();

public:
	LevelManager();

	static const int TILE_SIZE = 50;

	void loadMap(int levelIndex);

	const VertexArray* getVertexMap();
	const string& getMenuString();
	int getMapsNum();

	~LevelManager();
};
