#pragma once
#include <SFML/Audio.hpp>
using namespace sf;

class SoundManager
{
private:
	// buffers
	SoundBuffer walkSB;
	SoundBuffer shootSB;
	SoundBuffer wallHitSB;
	SoundBuffer targetHitSB;
	SoundBuffer reloadSB;

	// sounds
	Sound walkS;
	Sound shootS;
	Sound wallHitS;
	Sound targetHitS;
	Sound reloadS;

public:
	void playWalk(bool resume);
	void playShoot();
	void playWallHit();
	void playTargetHit();
	void playReload();

	SoundManager();
	~SoundManager();
};
