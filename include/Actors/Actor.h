#pragma once
#include <SFML/Graphics/RenderWindow.hpp>


namespace Simulation {
	class Actor
	{
	public:
		Actor() = default;
		~Actor() = default;

		virtual void Tick() = 0;
		virtual void Draw(sf::RenderWindow& window) = 0;
	};
}