#pragma once

#include <SFML/Graphics.hpp>
#include "Point.h"

class Car : public sf::RectangleShape
{
public:
	enum position
	{
		topLeft = 0,
		topRight = 1,
		botRight = 2,
		botLeft = 3
	};

	double velocity;
	Point coords[4]; //collision checking
	Car(sf::Vector2f &pos, const sf::Color &c, sf::Vector2f &size) //, sf::Texture &newTexture) Dont have Texture for car to make sprite yet.
	{
		this->setFillColor(c);
		this->setSize(size);
		this->setPosition(pos);
		coords[topLeft].coordinate = pos;
		coords[topRight].coordinate.x = pos.x + size.x;
		coords[topRight].coordinate.y = pos.y;
		coords[botRight].coordinate.x = pos.x + size.x;
		coords[botRight].coordinate.y = pos.y + size.y;
		coords[botLeft].coordinate.x = pos.x;
		coords[botLeft].coordinate.y = pos.y + size.y;
		velocity = 0.0;
	}

private:


};