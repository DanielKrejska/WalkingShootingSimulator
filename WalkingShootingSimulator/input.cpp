#include "Engine.h"

void Engine::input()
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			currentState = GameState::EXIT;
		}
	}
}
