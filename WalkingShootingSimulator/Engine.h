#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

// NA TESTOV�N�
#include <iostream>

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

	/*
	* Funkce pro Vnit�n� pou�it�
	*/
	void input();
	void update(Time deltaTime);
	void draw();

	// t��da Engine m� pouze jednu instanci
	Engine();

public:

	void run();

	static Engine& getEngine();
};
