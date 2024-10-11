#include "Obstacle.h"
#include "Game.h"

namespace ApplesGame
{
	void InitObstacle(Obstacle& obstacle, const sf::Texture& texture)
	{
		obstacle.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		obstacle.sprite.setTexture(texture);
		SetSpriteSize(obstacle.sprite, OBSTACLE_SIZE, OBSTACLE_SIZE);
		SetSpriteRelativeOrigin(obstacle.sprite, 0.5f, 0.5f);
		obstacle.sprite.setPosition(obstacle.position.x, obstacle.position.y);
	}
}

