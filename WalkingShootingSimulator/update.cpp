#pragma warning(disable : 4244)
#include "Engine.h"
#include <sstream>

void Engine::update(Time deltaTime)
{
	// hlavní funkènost main loopy
	switch (currentState)
	{
	case GameState::PLAYING:
		{
		Vector2f nextPosition(player.calculateNextPosition(deltaTime));
		this->wallCollisions(nextPosition);
		player.executeMovement(nextPosition);
		Vector2i mousePosition = Mouse::getPosition(window);
		Vector2f mouseWorldPos = window.mapPixelToCoords(mousePosition);
		this->rotatePlayer(mouseWorldPos);
		player.animationUpdate(deltaTime);
		player.stateUpdate(deltaTime);
		for (Bullet& b : bullets)
			b.update(deltaTime);
		break;
		}

	case GameState::EXIT:
		window.close();
		break;
	}

	viewSet();
	// aby se nám HUD neaktualizoval každej frame
	// postaèí to jednou za sekundu
	sinceHUDUpdate += deltaTime;
	if (sinceHUDUpdate > seconds(1))
	{
		std::stringstream ssfps;
		ssfps << int (1 / deltaTime.asSeconds());
		fpsText.setString(ssfps.str());
		sinceHUDUpdate = Time::Zero;
	}
}
