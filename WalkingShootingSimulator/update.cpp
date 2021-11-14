#include "Engine.h"
#include <sstream>

void Engine::update(Time deltaTime)
{
	// hlavn� funk�nost main loopy
	switch (currentState)
	{
	case GameState::MENU:
		break;

	case GameState::EXIT:
		window.close();
		break;
	}

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
