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

	// èudly
	switch (currentState)
	{
	case GameState::MENU:
		if (pressed(key::Num1) || pressed(key::Numpad1))
		{
			currentState = GameState::LEVEL_PICK;
		}
		if (pressed(key::Num3) || pressed(key::Numpad3))
		{
			currentState = GameState::EXIT;
		}
	}
}
