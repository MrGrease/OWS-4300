#pragma once

#include "ShapeActor.h"
namespace Simulation {
	class Circle : public ShapeActor
	{
	public:
		Circle(int segments, float radius, float x, float y, float sx, float sy, uint8_t r, uint8_t g, uint8_t b, std::string& text, sf::Font& font, unsigned int fontSize);
		~Circle() = default;

		void Tick() override;
		void Draw(sf::RenderWindow& window) override;
		void CheckCollision() override;
	private:
		float segments, radius;
	};
}