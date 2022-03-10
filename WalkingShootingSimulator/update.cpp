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
		soundManager.playWalk(player.isWalking());	
		player.executeMovement(nextPosition);
		this->rotatePlayer();
		player.animationUpdate(deltaTime);
		player.stateUpdate(deltaTime);
		for (Bullet& b : bullets)
			b.update(deltaTime);
		auto tit = targets.begin();
		while (tit != targets.end())
		{
			if (tit->isDestroyed())
				tit = targets.erase(tit);
			else
				tit++;
		}
		break;
	}

	case GameState::EXIT:
		window.close();
		break;
	}

	cursorSprite.setPosition(
		mouseWorldPosition.x - (cursorSprite.getGlobalBounds().width / 2),
		mouseWorldPosition.y - (cursorSprite.getGlobalBounds().height / 2));

	viewSet();
	// aby se n�m HUD neaktualizoval ka�dej frame
	// posta�� to jednou za sekundu
	sinceHUDUpdate += deltaTime;
	if (sinceHUDUpdate >= HUD_UPDATE_TIME)
	{
		std::stringstream ssfps;
		ssfps << int(1 / deltaTime.asSeconds());
		fpsText.setString(ssfps.str());
		sinceHUDUpdate = Time::Zero;
	}
	// s ukazetelem munice je to jin� p�sni�ka, ten mus� b�t p�esn�
	static int lastAmmo = 0;
	if (lastAmmo != player.checkMag())
	{
		stringstream ssAmmo;
		ssAmmo << player.checkMag();
		ammoText.setString(ssAmmo.str());
	}
	lastAmmo = player.checkMag();
}
