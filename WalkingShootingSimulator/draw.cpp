#include "Engine.h"

void Engine::draw()
{
	window.clear();
	window.setView(view);
	window.draw(fpsText);
	window.display();
}
