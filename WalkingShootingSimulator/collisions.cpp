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
	}
}
