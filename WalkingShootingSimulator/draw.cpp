#include "Engine.h"

void Engine::draw()
{
	window.clear();
	// always draw
	window.setView(view);
	window.draw(fpsText);

	switch (currentState)
	{
	case GameState::MENU:
		window.draw(menuText);
		break;
	}

	window.display();
}
