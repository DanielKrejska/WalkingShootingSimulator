#pragma warning(disable : 4244)
#include "Engine.h"
#include <sstream>

void Engine::update(Time deltaTime)
{
	// hlavn� funk�nost main loopy
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
	// aby se n�m HUD neaktualizoval ka�dej frame
	// posta�� to jednou za sekundu
	sinceHUDUpdate += deltaTime;
	if (sinceHUDUpdate > seconds(1))
	{
		std::stringstream ssfps;
		ssfps << int (1 / deltaTime.asSeconds());
		fpsText.setString(ssfps.str());
		sinceHUDUpdate = Time::Zero;
	}
}
