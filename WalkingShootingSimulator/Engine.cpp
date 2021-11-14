#include "Engine.h"
#include <cassert>

Engine::Engine()
{
	window.create(VideoMode(1280, 720), "Walking Shooting Simulator");
	currentState = GameState::MENU;
	assert(font.loadFromFile("fonts/Collegiate.ttf"));
	fpsText.setFont(font);
	fpsText.setCharacterSize(20);
	fpsText.setFillColor(Color::Green);
	fpsText.setPosition(0.f, 0.f);
	sinceHUDUpdate = Time::Zero;
}

Engine& Engine::getEngine()
{
	static Engine only_engine; // jediná instance tøídy Engine
	return only_engine;
}

void Engine::run()
{
	Clock frameClock;
	Time deltaTime;

	while (window.isOpen())
	{
		deltaTime = frameClock.restart();
		
		input();
		update(deltaTime);
		draw();

	}
}
