#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

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
		EXIT // ukonèení programu
	};
	
	GameState currentState;
	Font font;
	Text fpsText;
	Time sinceHUDUpdate;

	Text menuText;

	/*
	* Funkce pro Vnitøní použití
	*/
	void input();
	void update(Time deltaTime);
	void draw();

	void repositionHUD();

	// tøída Engine má pouze jednu instanci
	Engine();

public:

	void run();

	static Engine& getEngine();
};
