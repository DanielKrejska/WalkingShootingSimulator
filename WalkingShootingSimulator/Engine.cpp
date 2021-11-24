#include "Engine.h"
#include <cassert>

Engine::Engine()
{
	window.create(VideoMode(1280, 720), "Walking Shooting Simulator");
	view.setSize(window.getSize().x, window.getSize().y);
	currentState = GameState::MENU;
	assert(font.loadFromFile("fonts/Roboto.ttf"));
	fpsText.setFont(font);
	fpsText.setCharacterSize(15);
	fpsText.setFillColor(Color::Green);
	sinceHUDUpdate = Time::Zero;
	menuText.setFont(font);
	menuText.setCharacterSize(50);
	menuText.setFillColor(Color(244, 152, 22));
	menuText.setString("1) play\n2) fullscreen\n3) exit");
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

void Engine::repositionHUD()
{
	view.setCenter(window.getSize().x / 2, window.getSize().y / 2);

	FloatRect viewRect = FloatRect((float)view.getCenter().x - (view.getSize().x / 2),
		(float)view.getCenter().y - (view.getSize().y / 2),
		(float)view.getSize().x, (float)view.getSize().x);

	fpsText.setPosition(viewRect.left + 2, viewRect.top + 2);

	menuText.setPosition(view.getCenter() - Vector2f(menuText.getGlobalBounds().width/2,
		menuText.getGlobalBounds().height / 2));
}
