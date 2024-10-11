#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
	struct Obstacle
	{
		Position2D position;
		sf::Sprite sprite;
	};

	void InitObstacle(Obstacle& obstacle, const sf::Texture& texture);
}

