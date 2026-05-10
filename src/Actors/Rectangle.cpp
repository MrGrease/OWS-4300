#include "Actors/Rectangle.h"
#include <SFML/Graphics.hpp>

Simulation::Rectangle::Rectangle(float width, float height,float x,float y,float sx, float sy,uint8_t r, uint8_t g, uint8_t b,std::string& text,sf::Font& font,unsigned int fontSize)
{
	this->actorShape = new sf::RectangleShape(sf::Vector2f(width,height));

	this->width = width;
	this->height = height;

	this->posX = x;
	this->posY = y;

	this->speedX = sx;
	this->speedY = sy;

	this->draw = true;
	this->drawText = true;

	this->fillColor = new sf::Color(r,g,b);
	this->actorText = new sf::Text(font,text, fontSize);
}

void Simulation::Rectangle::Tick()
{
	this->actorShape->setPosition({ this->posX + this->speedX, this->posY + this->speedY });

	this->posX = this->actorShape->getPosition().x;
	this->posY = this->actorShape->getPosition().y;
	
	sf::FloatRect bounds = this->actorText->getLocalBounds();

	actorText->setPosition({
		this->posX + (this->width / 2.0f) - (bounds.position.x + bounds.size.x / 2.0f),
		this->posY + (this->height / 2.0f) - (bounds.position.y + bounds.size.y / 2.0f)
		});

	this->actorShape->setFillColor(*this->fillColor);

	this->CheckCollision();
}

void Simulation::Rectangle::Draw(sf::RenderWindow& window)
{
	window.draw(*this->actorShape);

	window.draw(*this->actorText);

	lastScreenWidth = window.getSize().x;
	lastScreenHeight = window.getSize().y;
}

void Simulation::Rectangle::CheckCollision()
{
	if (this->posX + this->width >= lastScreenWidth || this->posX <= 0)
	{
		this->speedX *= -1;
	}
	if (this->posY + this->height >= lastScreenHeight || this->posY <= 0)
	{
		this->speedY *= -1;
	}
}
