#include "Engine.h"

void Engine::wallCollisions(Vector2f& playerNextPosition)
{
	const vector<Vector2f>& wallPositions = levelManager.getWalls();
	FloatRect twr; // temp wall rect
	FloatRect pr = player.getRect().getGlobalBounds();
	pr.left = playerNextPosition.x;
	pr.top = playerNextPosition.y;
	for (Vector2f position : wallPositions)
	{
		twr.left = position.x;
		twr.top = position.y;
		twr.height = twr.width = LevelManager::TILE_SIZE;

		// pokud by hráèùv následující krok vedl do zdi, tak to ho zruš
		if (pr.intersects(twr))
		{
			FloatRect withNewX(pr.left, player.getPosition().y, pr.width, pr.height);
			FloatRect withNewY(player.getPosition().x, pr.top, pr.width, pr.height);
			if (withNewX.intersects(twr))
			{
				playerNextPosition.x = player.getOldPosition().x;
			}
			if (withNewY.intersects(twr))
			{
				playerNextPosition.y = player.getOldPosition().y;
			}
		}
		
		// náboje
		auto it = bullets.begin();
		while (it != bullets.end())
		{
			// zeï
			if (it->getRect().intersects(twr))
			{
				it = bullets.erase(it);
				soundManager.playWallHit();
			}
			else
			{
				++it;
				break;
			}
		}
	}

	//cout << targets.size() << "\t" << bullets.size() << endl;
	bool didCollide = false;
	auto bit = bullets.begin();
	while (bit != bullets.end())
	{
		for (auto tit = targets.begin(); tit != targets.end(); tit++)
		{
			if (bit->getRect().intersects(tit->getColliderRect()))
			{
				tit->takeDamage(1);
				didCollide = true;
				soundManager.playTargetHit();
				break;
			}
		}
		if (didCollide)
		{
			bit = bullets.erase(bit);
			didCollide = false;
		}
		else
		{
			bit++;
		}
	}
}
