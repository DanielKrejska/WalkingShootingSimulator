#pragma warning(disable : 4244)
#include "Engine.h"
#include "TextureHolder.h"

#define crosshaire_scale Vector2f(0.04f, 0.04f)

Engine::Engine()
{
	window.create(VideoMode(1280, 720), "Walking Shooting Simulator");
	view.setSize(window.getSize().x, window.getSize().y);
	window.setFramerateLimit(160);
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
	ammoText.setFont(font);
	ammoText.setCharacterSize(18);
	ammoText.setFillColor(Color::Yellow);
	//ammoText.setStyle(Text::Bold);
	floorTexture = TextureHolder::getTexture("graphics/background_sheet.png");
	bgTexture = TextureHolder::getTexture("graphics/bg.jpg");
	bgSprite.setTexture(bgTexture);
	window.setMouseCursorVisible(false);
	cursorSprite.setTexture(TextureHolder::getTexture("graphics/crosshair.png"));
	cursorSprite.setScale(crosshaire_scale);
	// aù objekty skoËÌ na svoje mÌsto
	viewSet();
	hudResizeUpdate();
	Vector2i mousePosition = Mouse::getPosition(window);
	mouseWorldPosition = window.mapPixelToCoords(mousePosition);
}

Engine::~Engine()
{
}

Engine& Engine::getEngine()
{
	static Engine only_engine; // jedin· instance t¯Ìdy Engine
	return only_engine;
}

void Engine::run()
{
	Clock frameClock;
	Time deltaTime;

	while (window.isOpen())
	{
		deltaTime = frameClock.restart();
		Vector2i mousePosition = Mouse::getPosition(window);
		mouseWorldPosition = window.mapPixelToCoords(mousePosition);

		input();
		update(deltaTime);
		draw();

	}
}

void Engine::hudResizeUpdate()
{
	view.setSize(window.getSize().x, window.getSize().y);
	// pozadÌ je ve fullhd a j· to cel˝ programuju na 1080p monitoru
	scaleToFullHD.x = view.getSize().x / 1920.f;
	scaleToFullHD.y = view.getSize().y / 1080.f;
	bgSprite.setScale(scaleToFullHD);

	menuText.setPosition(window.getSize().x / 2 - menuText.getGlobalBounds().width / 2,
		window.getSize().y / 2 - menuText.getGlobalBounds().height / 2);

	levelPickText.setPosition(window.getSize().x / 2 - levelPickText.getGlobalBounds().width / 2,
		window.getSize().y / 2- levelPickText.getGlobalBounds().height / 2);

}

// objekty, co se musÌ drûet View
void Engine::hudPositionUpdate()
{
	FloatRect viewRect = FloatRect((float)view.getCenter().x - (view.getSize().x / 2),
		(float)view.getCenter().y - (view.getSize().y / 2),
		(float)view.getSize().x, (float)view.getSize().y);

	fpsText.setPosition(viewRect.left + 2, viewRect.top + 2);
	ammoText.setPosition(
		mouseWorldPosition.x - (ammoText.getGlobalBounds().width / 2),
		mouseWorldPosition.y + (cursorSprite.getGlobalBounds().height / 2) + 2);
}


void Engine::viewSet()
{
	if (currentState == GameState::PLAYING)
		// tady se fl·kne pozice postavy
		view.setCenter(player.getCenter());
	else
		view.setCenter(window.getSize().x / 2, window.getSize().y / 2);

	hudPositionUpdate();
}

void Engine::rotatePlayer()
{
	float dtX = mouseWorldPosition.x - player.getCenter().x;
	float dtY = mouseWorldPosition.y - player.getCenter().y;
	float rotation = atan2(dtY, dtX);
	rotation = rotation * (180.f / PI);
	player.rotate(rotation);
}
