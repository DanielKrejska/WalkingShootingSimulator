#pragma warning(disable : 4244)
#include "Engine.h"
#include <sstream>

void Engine::update(Time deltaTime)
{
	// hlavní funkènost main loopy
	switch (currentState)
	{
	case GameState::PLAYING:
		break;

	case GameState::EXIT:
		window.close();
		break;
	}

	hudPositionUpdate();

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
