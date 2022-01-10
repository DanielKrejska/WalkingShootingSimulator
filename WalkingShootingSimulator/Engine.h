#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "LevelManager.h"
#include "Soldier.h"

using namespace sf;

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

	Sprite bgSprite;
	// ulo�en� textur
	Texture bgTexture;
	Texture floorTexture;

	// spr�va
	Vector2f scaleToFullHD;
	LevelManager levelManager;

	/*
	* Funkce pro Vnit�n� pou�it�
	*/
	void input();
	void update(Time deltaTime);
	void draw();

	void viewSet();
	void hudResizeUpdate();
	void hudPositionUpdate();

	// t��da Engine m� pouze jednu instanci
	Engine();

	Soldier player;

public:

	void run();

	static Engine& getEngine();
	~Engine();
};
