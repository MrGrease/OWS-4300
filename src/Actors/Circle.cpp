#include "Actors/Circle.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Simulation::Circle::Circle(int segments, float radius, float x, float y, float sx, float sy, uint8_t r, uint8_t g, uint8_t b, std::string& text, sf::Font& font, unsigned int fontSize)
{
	this->actorShape = new sf::CircleShape(radius,segments);

	this->segments= segments;
	this->radius = radius;

	this->posX = x;
	this->posY = y;

	this->speedX = sx;
	this->speedY = sy;

	this->draw = true;
	this->drawText = true;

	this->fillColor = new sf::Color(r, g, b);
	this->actorText = new sf::Text(font, text, fontSize);
}

void Simulation::Circle::Tick()
{
	this->actorShape->setScale(sf::Vector2(this->scale, this->scale));

	this->actorShape->setPosition({ this->posX + this->speedX, this->posY + this->speedY });

	this->posX = this->actorShape->getPosition().x;
	this->posY = this->actorShape->getPosition().y;

	sf::FloatRect bounds = actorText->getLocalBounds();

	actorText->setPosition({
	(this->posX + this->radius* this->scale) - (bounds.position.x + bounds.size.x / 2.0f),
	(this->posY + this->radius* this->scale) - (bounds.position.y + bounds.size.y / 2.0f)
		});

	this->actorShape->setFillColor(*this->fillColor);	

	this->CheckCollision();
}

void Simulation::Circle::Draw(sf::RenderWindow& window)
{
	if (!draw)
		return;
	window.draw(*this->actorShape);

	window.draw(*this->actorText);

	lastScreenWidth = window.getSize().x;
	lastScreenHeight = window.getSize().y;
}

void Simulation::Circle::CheckCollision()
{
	if (this->posX + (this->radius*2* this->scale) >= lastScreenWidth || this->posX <= 0)
	{
		this->speedX *= -1;
	}
	if (this->posY + (this->radius * 2* this->scale) >= lastScreenHeight || this->posY <= 0)
	{
		this->speedY *= -1;
	}
}
