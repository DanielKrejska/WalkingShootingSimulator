#pragma once
#include <string>
#include <vector>
#include "Bullet.h"
#include "LevelManager.h"
#include "Soldier.h"
#define PI 3.14159265
#define HUD_UPDATE_TIME seconds(1.f)


// NA TESTOV�N�
#include <iostream>
using namespace std;

class Engine
{

private:
	// okno programu
	RenderWindow window;
	View view;

	// st�dia hry, pro ��zen� programu
	enum class GameState {
		MENU, // spust� se po zapnut� a m��eme odsud to ostatn�ch
		LEVEL_PICK, // spustit hru -> v�b�r levelu
		PLAYING, // b�� hra
		PAUSE, // pozastaven� hra -> menu nebo pokra�ov�n� hry
		EXIT // ukon�en� programu
	};
	
	GameState currentState;
	Font font;
	Text fpsText;
	Time sinceHUDUpdate;
	Text levelPickText;
	Text menuText;
	Text ammoText;

	Sprite cursorSprite;
	Sprite bgSprite;
	// ulo�en� textur
	Texture bgTexture;
	Texture floorTexture;

	// spr�va
	Vector2f mouseWorldPosition;
	Vector2f scaleToFullHD;
	LevelManager levelManager;

	void rotatePlayer();
	// hern� objekty
	Soldier player;
	vector<Bullet> bullets;
	vector<Target> targets;

	/*
	* Funkce pro Vnit�n� pou�it�
	*/
	void input();
	void update(Time deltaTime);
	void draw();

	// kolize objekt�
	void wallCollisions(Vector2f& playerLastPosition);

	void viewSet();
	void hudResizeUpdate();
	void hudPositionUpdate();

	// t��da Engine m� pouze jednu instanci
	Engine();

public:

	void run();

	static Engine& getEngine();
	~Engine();
};
