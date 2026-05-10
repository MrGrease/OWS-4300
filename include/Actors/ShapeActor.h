#pragma once

#include "Actor.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace Simulation {

	class ShapeActor : public Actor
	{
	public:
		ShapeActor();
		~ShapeActor();

		virtual void Tick() = 0;
		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual void CheckCollision() = 0;

	protected:
		sf::Shape* actorShape;

		float posX, posY;
		float speedX, speedY;
		bool draw, drawText;
		sf::Color* fillColor;
		sf::Text* actorText;
		int lastScreenWidth, lastScreenHeight;
	};
}