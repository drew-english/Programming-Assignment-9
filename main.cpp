#include <SFML/Graphics.hpp>
#include "Car.h"

#define LINEAR_SPEED 1.75
#define ROTATE_SPEED .8
#define PENALTY .25

/**UPDATED TO BE SMOOTHER**/

int main(void) // car movement
{
		
	double linSpeed = LINEAR_SPEED;
	double rotSpeed = ROTATE_SPEED;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Andy 500"); // opens the window
	
	sf::Texture redCar;
	sf::Texture trackTxtr;
	redCar.loadFromFile("redCar.png");
	trackTxtr.loadFromFile("Track.png");

	sf::Image trackImg;
	trackImg.loadFromFile("Track.png");
	sf::Sprite track(trackTxtr); // sets the backround to the Track.png

	Car car1(sf::Vector2f(1100, 125), &redCar);

	bool keys[4] = { false };

	while (window.isOpen()) // keep the program running as long as the window is not closed by the user
	{
		sf::Event event;
		while (window.pollEvent(event)) // iterate through when user interface is detected (closing, key press, etc.)
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A))) // turn left
		{
			keys[0] = true;
			keys[1] = false; // allows both keys to be pressed at once, moving in the direction of the last key pressed until it is released
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D))) // turn right
		{
			keys[1] = true;
			keys[0] = false; // allows both keys to be pressed at once, moving in the direction of the last key pressed until it is released
		}
		else
		{
			keys[0] = false;
			keys[1] = false;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
		{// move forwards 
			keys[2] = true;
			keys[3] = false; // allows both keys to be pressed at once, moving in the direction of the last key pressed until it is released
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S))) // move backwards
		{
			keys[3] = true;
			keys[2] = false; // allows both keys to be pressed at once, moving in the direction of the last key pressed until it is released
		}
		else
		{
			keys[2] = false;
			keys[3] = false;
		}


		int collision = car1.detectCollision(); // detects collision of car, see car.h for return values
		if (keys[0]) // turn left
		{
			
			if(collision == 1)
			{
				linSpeed *= PENALTY;
				rotSpeed *= PENALTY;
			}

			car1.rotate(-rotSpeed);
			linSpeed = LINEAR_SPEED;
			rotSpeed = ROTATE_SPEED;
		}

		if (keys[1]) // turn right
		{
			if (collision == 1)
			{
				linSpeed *= PENALTY;
				rotSpeed *= PENALTY;
			}

			car1.rotate(rotSpeed);
			linSpeed = LINEAR_SPEED;
			rotSpeed = ROTATE_SPEED;
		}

		if (keys[2]) //- movement obtained from: https://en.sfml-dev.org/forums/index.php?topic=4951.0
		{
			if (collision == 1)
			{
				linSpeed *= PENALTY;
				rotSpeed *= PENALTY;
			}

			car1.move(sf::Vector2f(-linSpeed * cos(3.14159265 * (car1.getRotation() - 180) / 180),
				-linSpeed * sin(3.14159265 * (car1.getRotation() - 180) / 180)));
			linSpeed = LINEAR_SPEED;
			rotSpeed = ROTATE_SPEED;
		}

		if (keys[3]) // this movement speed is divided by 2 to move slower when moving backwards
		{
			if (collision == 1)
			{
				linSpeed *= PENALTY;
				rotSpeed *= PENALTY;
			}

			car1.move(sf::Vector2f((linSpeed / 2) * cos(3.14159265 * (car1.getRotation() - 180) / 180),
				(linSpeed / 2) * sin(3.14159265 * (car1.getRotation() - 180) / 180)));
			linSpeed = LINEAR_SPEED;
			rotSpeed = ROTATE_SPEED;
		}


		window.clear(); // mandatory to do before drawing stuff, so that shape doesn't actually get covered
		window.draw(track);
		window.draw(car1); // this goes to a hidden buffer - display will copy this to the main buffer
		window.display(); // copies the hidden buffer to the main buffer (window) - this is double-buffering
	}

	return 0;

}