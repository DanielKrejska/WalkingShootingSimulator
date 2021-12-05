#pragma once
#pragma warning(disable : 4244)
#include <vector>
#include <string>
using namespace std;

class LevelManager
{
private:
	vector<string> mapNames;
	string menuString;

	int mapsNum;

public:
	LevelManager();

	const string& getMenuString();
};
