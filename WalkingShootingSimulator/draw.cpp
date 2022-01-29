#include "Engine.h"

void Engine::draw()
{
	window.clear();
	// always draw
	window.setView(view);

	switch (currentState)
	{
	case GameState::MENU:
		window.draw(bgSprite);
		window.draw(menuText);
		break;
	case GameState::LEVEL_PICK:
		window.draw(bgSprite);
		window.draw(levelPickText);
		break;
	case GameState::PLAYING:
		window.draw(*levelManager.getVertexMap(), &floorTexture);
		window.draw(player);
		for (Bullet b : bullets)
		{
			window.draw(b.getShape());
		}
		break;
	case GameState::PAUSE:
		window.draw(*levelManager.getVertexMap(), &floorTexture);
		window.draw(menuText);
		break;
	}

	window.draw(fpsText);
	window.display();
}
