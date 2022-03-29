#pragma warning(disable : 4244)
#include "Engine.h"
#include <sstream>
#include <filesystem>

void Engine::update(Time deltaTime)
{
	// hlavní funkènost main loopy
	switch (currentState)
	{
	case GameState::PLAYING:
	{
		levelTime += deltaTime;
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
		// kontrola konce hry
		if (targets.size() <= 0)
		{
			levelFinished = true;
			stringstream s;
			s << "ALL TARGETS DESTROYED\n" << fixed << setprecision(2) 
				<< levelTime.asSeconds() << " seconds\n\n0) menu";
			menuText.setString(s.str());
			currentState = GameState::PAUSE;
			hudResizeUpdate();
			soundManager.playWalk(false);
			window.setMouseCursorVisible(true);
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
	// aby se nám HUD neaktualizoval každej frame
	// postaèí to jednou za sekundu
	sinceHUDUpdate += deltaTime;
	if (sinceHUDUpdate >= HUD_UPDATE_TIME)
	{
		std::stringstream ssfps;
		ssfps << int(1 / deltaTime.asSeconds());
		fpsText.setString(ssfps.str());
		sinceHUDUpdate = Time::Zero;
	}
	// s ukazetelem munice je to jiná písnièka, ten musí být pøesný
	static int lastAmmo = 0;
	if (lastAmmo != player.checkMag())
	{
		stringstream ssAmmo;
		ssAmmo << player.checkMag();
		ammoText.setString(ssAmmo.str());
	}
	lastAmmo = player.checkMag();
}
