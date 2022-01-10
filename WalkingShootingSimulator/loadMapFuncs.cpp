#pragma warning(disable : 6386)
#pragma warning(disable : 4267)
#pragma warning(disable : 26451)
#include "LevelManager.h"
#include <fstream>
using std::ifstream;
using std::string;

void LevelManager::technicalInit(int mapIndex)
{
	ifstream inputFile(mapNames[mapIndex]);
	string rowString;

	// získání velikosti mapy
	while (getline(inputFile, rowString))
	{
		++mapSize.y;
	}
	mapSize.x = rowString.length();

	// FileInputStream zpìt na zaèátek
	inputFile.clear();
	inputFile.seekg(0, ios::beg);

	deleteCurrentMap();
	// vytvoøení 2d pole
	arrayMap = new int* [mapSize.y];
	for (int i = 0; i < mapSize.y; i++)
	{
		arrayMap[i] = new int[mapSize.x];
	}

	rowString.clear();

	// zapisování hodnot do 2d pole
	int y = 0;
	while (inputFile >> rowString)
	{
		for (int x = 0; x < rowString.length(); x++)
		{
			const char val = rowString[x];
			arrayMap[y][x] = atoi(&val);
		}
		y++;
	}
	inputFile.close();
}


void LevelManager::graphicalInit()
{
	pVertexMap = new VertexArray();
	pVertexMap->setPrimitiveType(Quads);
	pVertexMap->resize(mapSize.x * mapSize.y * 4);
	VertexArray& va = *pVertexMap;

	static const int FLOOR_TYPES = 3;
	int currentVertex = 0;
	
	for (int w = 0; w < mapSize.x; w++)
	{
		for (int h = 0; h < mapSize.y; h++)
		{
			// pøiøazení pozice bodù v mapì
			va[currentVertex + 0].position = Vector2f(w * TILE_SIZE,
				h * TILE_SIZE);
			va[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, 
				h * TILE_SIZE);
			va[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE,
				(h * TILE_SIZE) + TILE_SIZE);
			va[currentVertex + 3].position = Vector2f((w * TILE_SIZE),
				(h * TILE_SIZE) + TILE_SIZE);

			// ètvercùm v mapì pøiøadíme ètverec v textuøe
			if (arrayMap[h][w] == 1)
			{
				va[currentVertex + 0].texCoords = Vector2f(0,
					0 + FLOOR_TYPES * TILE_SIZE);
				va[currentVertex + 1].texCoords = Vector2f(TILE_SIZE,
					0 + FLOOR_TYPES * TILE_SIZE);
				va[currentVertex + 2].texCoords = Vector2f(TILE_SIZE,
					TILE_SIZE + FLOOR_TYPES * TILE_SIZE);
				va[currentVertex + 3].texCoords = Vector2f(0,
					TILE_SIZE + FLOOR_TYPES * TILE_SIZE);
			}
			else
			{
				// použije se jedna náhodnì vybraná textura ze tøí textur podlahy
				srand((int)time(0) + h * w - h);
				int choosen = (rand() % FLOOR_TYPES);
				int verticalOffset = choosen * TILE_SIZE;

				va[currentVertex + 0].texCoords = Vector2f(0,
					0 + verticalOffset);
				va[currentVertex + 1].texCoords = Vector2f(TILE_SIZE,
					0 + verticalOffset);
				va[currentVertex + 2].texCoords = Vector2f(TILE_SIZE,
					TILE_SIZE + verticalOffset);
				va[currentVertex + 3].texCoords = Vector2f(0,
					TILE_SIZE + verticalOffset);
			}
			currentVertex += 4;
		}
	}
}
