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
			hudResizeUpdate();
		}
	}

	static bool keyOnHold[9] = { false };

	// èudly
	switch (currentState)
	{
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
		for (int i = key::Num1; i < key::Num9 + 1; i++)
		{
			if (pressed(key(i)) || pressed(key(i + 49)))
			{
				if (!keyOnHold[holdIndex++])
				{
					currentState = GameState::PLAYING;
				}
			}
		}
		
		break;
	}
}
