#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>


namespace ApplesGame
{
	//generate position
	Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight)
	{
		Position2D result;
		result.x = rand() / (float)RAND_MAX * screenWidth;
		result.y = rand() / (float)RAND_MAX * screenHeight;
		return result;
	}

	//collision w/ objects
	bool IsCirclesCollide(Position2D position1, float size1, Position2D position2, float size2) {
		float squareDistance = (position1.x - position2.x) * (position1.x - position2.x) +
			(position1.y - position2.y) * (position1.y - position2.y);
		float squareRadiusSum = (size1 + size2) * (size1 + size2) / 4;

		return squareDistance < squareRadiusSum;
	}
	
	//set for sprites
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
	}

}
