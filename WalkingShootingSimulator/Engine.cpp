#pragma warning(disable : 4244)
#include "Engine.h"
#include <cassert>

Engine::Engine()
{
	window.create(VideoMode(1280, 720), "Walking Shooting Simulator");
	view.setSize(window.getSize().x, window.getSize().y);
	window.setFramerateLimit(90);
	currentState = GameState::MENU;
	font.loadFromFile("fonts/Roboto.ttf");
	fpsText.setFont(font);
	fpsText.setCharacterSize(15);
	fpsText.setFillColor(Color::Green);
	sinceHUDUpdate = Time::Zero;
	levelPickText.setFont(font);
	levelPickText.setCharacterSize(35);
	levelPickText.setFillColor(Color::Yellow);
	levelPickText.setString(levelManager.getMenuString());
	menuText.setFont(font);
	menuText.setCharacterSize(75);
	menuText.setFillColor(Color::Green);
	menuText.setString("1) play\n0) exit");
	floorTexture.loadFromFile("graphics/background_sheet.png");
	bgTexture.loadFromFile("graphics/bg.jpg");
	bgSprite.setTexture(bgTexture);
	// a� objekty sko�� na svoje m�sto
	hudResizeUpdate();
}

Engine& Engine::getEngine()
{
	static Engine only_engine; // jedin� instance t��dy Engine
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

void Engine::hudResizeUpdate()
{
	viewSet();

	view.setSize(window.getSize().x, window.getSize().y);
	// pozad� je ve fullhd a j� to cel� programuju na 1080p monitoru
	scaleToFullHD.x = view.getSize().x / 1920;
	scaleToFullHD.y = view.getSize().y / 1080;
	bgSprite.setScale(scaleToFullHD);

	menuText.setPosition(view.getCenter() - Vector2f(
		menuText.getGlobalBounds().width / 2,
		menuText.getGlobalBounds().height / 2));

	levelPickText.setPosition(view.getCenter() - Vector2f(
		levelPickText.getGlobalBounds().width / 2,
		levelPickText.getGlobalBounds().height / 2));
}

void Engine::hudPositionUpdate()
{
	viewSet();

	FloatRect viewRect = FloatRect((float)view.getCenter().x - (view.getSize().x / 2),
		(float)view.getCenter().y - (view.getSize().y / 2),
		(float)view.getSize().x, (float)view.getSize().x);

	fpsText.setPosition(viewRect.left + 2, viewRect.top + 2);
}

void Engine::viewSet()
{
	if (currentState == GameState::PLAYING)
		// tady se fl�kne pozice postavy
		view.setCenter(0, 0);
	else
		view.setCenter(window.getSize().x / 2, window.getSize().y / 2);
}