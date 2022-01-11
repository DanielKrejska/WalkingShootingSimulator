#pragma warning(disable : 4244)
#pragma warning(disable : 26812)
#include "Engine.h"
#include <cassert>

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
			hudResizeUpdate();
		}
	}

	static bool keyOnHold[10] = { false };
	static bool escOnHold = false;

	// èudly
	switch (currentState)
	{
	case GameState::PLAYING:
		if (pressed(key::Escape) && !escOnHold)
		{
			currentState = GameState::PAUSE;
			escOnHold = true;
		}
		else
		{
			escOnHold = false;
		}
		break;
	case GameState::PAUSE:
		if (pressed(key::Num1) || pressed(key::Numpad1))
		{
			if (!keyOnHold[1]) { currentState = GameState::PLAYING; }
			keyOnHold[1] = true;
		}
		else keyOnHold[1] = false;

		if (pressed(key::Num0) || pressed(key::Numpad0))
		{
			if (!keyOnHold[0]) currentState = GameState::MENU;
			keyOnHold[0] = true;
		}
		else keyOnHold[0] = false;
		break;
	case GameState::MENU:
		if (pressed(key::Num1) || pressed(key::Numpad1))
		{
			if (!keyOnHold[1]) { currentState = GameState::LEVEL_PICK; }
			keyOnHold[1] = true;
		}
		else keyOnHold[1] = false;

		if (pressed(key::Num0) || pressed(key::Numpad0))
		{
			if (!keyOnHold[0]) currentState = GameState::EXIT;
		}
		else keyOnHold[0] = false;

		break;

	case GameState::LEVEL_PICK:
		if (pressed(key::Num0) || pressed(key::Numpad0))
		{
			currentState = GameState::MENU;
			keyOnHold[0] = true;
		}
		else keyOnHold[0] = false;

		int holdIndex = 1;
		for (int i = key::Num1; i <= key::Num9; i++)
		{
			if (pressed(key(i)) || pressed(key(i + 49)))
			{
				if (!keyOnHold[holdIndex])
				{
					if (levelManager.loadMap(holdIndex - 1, player))
						currentState = GameState::PLAYING;
				}
			}
			else
			{
				keyOnHold[holdIndex] = false;
			}
			holdIndex++;
		}
		break;
	}
}
