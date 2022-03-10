#pragma warning(disable : 26812)
#include "SoundManager.h"

SoundManager::SoundManager()
{
	walkSB.loadFromFile("sounds/walk.wav");
	walkS.setBuffer(walkSB);
	shootSB.loadFromFile("sounds/shoot.wav");
	shootS.setBuffer(shootSB);
	shootS.setVolume(32.5f);
	wallHitSB.loadFromFile("sounds/wall_hit.wav");
	wallHitS.setBuffer(wallHitSB);
	targetHitSB.loadFromFile("sounds/target_hit.wav");
	targetHitS.setBuffer(targetHitSB);
	reloadSB.loadFromFile("sounds/reload.wav");
	reloadS.setBuffer(reloadSB);
}

SoundManager::~SoundManager()
{
}

void SoundManager::playWalk(bool resume)
{
	if (resume)
	{
		if (walkS.getStatus() != Sound::Status::Playing)
		{
			walkS.play();
		}
	}
	else
	{
		if (walkS.getStatus() == Sound::Status::Playing)
		{
			walkS.stop();
		}
	}
}

void SoundManager::playShoot()
{
	shootS.play();
}

void SoundManager::playWallHit()
{
	wallHitS.play();
}

void SoundManager::playTargetHit()
{
	targetHitS.play();
}

void SoundManager::playReload()
{
	reloadS.play();
}
