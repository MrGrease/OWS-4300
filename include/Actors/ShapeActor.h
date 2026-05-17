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


    public:
        // =========================
        // Speed
        // =========================
        float GetSpeedX() const { return speedX; }
        float GetSpeedY() const { return speedY; }

        void SetSpeedX(float value) { speedX = value; }
        void SetSpeedY(float value) { speedY = value; }

        void SetSpeed(float x, float y)
        {
            speedX = x;
            speedY = y;
        }

        // =========================
        // Scale
        // =========================
        float GetScale() const { return scale; }
        void SetScale(float value) { scale = value; }

        // =========================
        // Draw flag
        // =========================
        bool GetDraw() const { return draw; }
        void SetDraw(bool value) { draw = value; }

        // =========================
        // Fill Color
        // =========================
        sf::Color* GetFillColor() const { return fillColor; }
        void SetFillColor(float& r, float& g, float& b) 
        { 
            fillColor->r = r*255;
            fillColor->g = g*255;
            fillColor->b = b*255;
        }

        // =========================
        // Actor Text
        // =========================
        sf::Text* GetActorText() const { return actorText; }
        void SetActorText(const char* text) { actorText->setString(sf::String(text)); }
	protected:
		sf::Shape* actorShape;

		float posX, posY;
		float speedX, speedY;
		float scale = 1.0f;
		bool draw, drawText;
		sf::Color* fillColor;
		sf::Text* actorText;
		int lastScreenWidth, lastScreenHeight;
	};
}