#pragma once

#include <SFML/Graphics.hpp>

class Car : public sf::RectangleShape
{
public:
	enum position //allows to keep track of what position each coordinate corresponds to on the car
	{
		topLeft = 0,
		topRight = 1,
		botRight = 2,
		botLeft = 3
	};

	double velocity;
	sf::Vector2f coords[4]; //collision checking
	Car(sf::Vector2f &pos, const sf::Color &c, sf::Vector2f &size) //, sf::Texture &newTexture) Dont have Texture for car to make sprite yet.
	{
		this->setFillColor(c);
		this->setSize(size);
		this->setPosition(pos);
		coords[topLeft] = pos;
		coords[topRight].x = pos.x + size.x;
		coords[topRight].y = pos.y;
		coords[botRight].x = pos.x + size.x;
		coords[botRight].y = pos.y + size.y;
		coords[botLeft].x = pos.x;
		coords[botLeft].y = pos.y + size.y;
		velocity = 0.0;
	}

private:


};
