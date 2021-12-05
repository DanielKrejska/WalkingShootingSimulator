#pragma warning(disable : 4244)
#pragma warning(disable : 26812)
#include "Engine.h"

typedef Keyboard::Key key;

inline bool pressed(key pressedKey)
{
	return Keyboard::isKeyPressed(pressedKey);
}

void Engine::input()
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			currentState = GameState::EXIT;
		}
		else if (event.type == Event::Resized)
		{
			view.setSize(window.getSize().x, window.getSize().y);
			repositionHUD();
		}
	}

	static bool key0onHold = false, key1onHold = false, key3onHold = false;

	// èudly
	switch (currentState)
	{
	case GameState::MENU:
		if (pressed(key::Num1) || pressed(key::Numpad1))
		{
			if (!key1onHold) { currentState = GameState::LEVEL_PICK; }
			key1onHold = true;
		}
		else key1onHold = false;

		if (pressed(key::Num0) || pressed(key::Numpad0))
		{
			if (!key0onHold) currentState = GameState::EXIT;
		}
		else key0onHold = false;

		break;

	case GameState::LEVEL_PICK:
		if (pressed(key::Num0) || pressed(key::Numpad0))
		{
			currentState = GameState::MENU;
			key0onHold = true;
		}
		else key0onHold = false;
		break;
	}
}
