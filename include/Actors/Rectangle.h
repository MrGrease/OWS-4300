#pragma once

#include "ShapeActor.h"
namespace Simulation {
	class Rectangle : public ShapeActor
	{
	public:
		Rectangle(float width, float height, float x, float y, float sx, float sy, uint8_t r, uint8_t g, uint8_t b, std::string& text, sf::Font& font, unsigned int fontSize);
		~Rectangle() = default;

		void Tick() override;
		void Draw(sf::RenderWindow& window) override;
		void CheckCollision() override;
	private:
		float width, height;
	};
}