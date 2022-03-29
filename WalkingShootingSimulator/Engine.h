#pragma once
#include <string>
#include <vector>
#include "Bullet.h"
#include "LevelManager.h"
#include "Soldier.h"
#include "SoundManager.h"
#define HUD_UPDATE_TIME seconds(1.f)
#define PI 3.14159265


// NA TESTOVÁNÍ
#include <iostream>
using namespace std;

class Engine
{

private:
	// okno programu
	RenderWindow window;
	View view;

	// stádia hry, pro øízení programu
	enum class GameState {
		MENU, // spustí se po zapnutí a mùžeme odsud to ostatních
		LEVEL_PICK, // spustit hru -> výbìr levelu
		PLAYING, // bìží hra
		PAUSE, // pozastavená hra -> menu nebo pokraèování hry
		EXIT, // ukonèení programu
		INFO
	};
	
	GameState currentState;
	Font font;
	Text fpsText;
	Time sinceHUDUpdate;
	Text levelPickText;
	Text menuText;
	Text ammoText;
	Text infoText;
	RectangleShape infoBG;

	Sprite cursorSprite;
	Sprite bgSprite;
	// uložení textur
	Texture bgTexture;
	Texture floorTexture;

	// správa
	Vector2f mouseWorldPosition;
	Vector2f scaleToFullHD;
	LevelManager levelManager;
	SoundManager soundManager;
	Time levelTime;
	bool levelFinished;

	void rotatePlayer();
	// herní objekty
	Soldier player;
	vector<Bullet> bullets;
	vector<Target> targets;

	/*
	* Funkce pro Vnitøní použití
	*/
	void input();
	void update(Time deltaTime);
	void draw();

	// kolize objektù
	void wallCollisions(Vector2f& playerLastPosition);

	void viewSet();
	void hudResizeUpdate();
	void hudPositionUpdate();

	// tøída Engine má pouze jednu instanci
	Engine();

public:

	void run();

	static Engine& getEngine();
	~Engine();
};
