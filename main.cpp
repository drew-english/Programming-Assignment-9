#include <SFML/Graphics.hpp>

#define LINEAR_SPEED 1.0
#define ROTATE_SPEED .5

/**UPDATED TO BE SMOOTHER**/

int main(void) // car movement
{

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!"); // opens the window
	sf::RectangleShape shape(sf::Vector2f(120, 50)); // change this to your car drawing!
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(400, 550);
	shape.setOrigin((shape.getSize().x * 0.5), (shape.getSize().y * 0.5));

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


		if (keys[0]) // turn left
		{
			shape.rotate(-ROTATE_SPEED);
		}

		if (keys[1]) // turn right
		{
			shape.rotate(ROTATE_SPEED);
		}

		if (keys[2]) //- movement obtained from: https://en.sfml-dev.org/forums/index.php?topic=4951.0
		{
			shape.move(sf::Vector2f(LINEAR_SPEED * cos(3.14159265 * (shape.getRotation() - 180) / 180),
				 LINEAR_SPEED * sin(3.14159265 * (shape.getRotation() - 180) / 180)));
		}

		if (keys[3]) // this movement speed is divided by 2 to move slower when moving backwards
		{
			shape.move(sf::Vector2f((-LINEAR_SPEED / 2) * cos(3.14159265 * (shape.getRotation() - 180) / 180),
				(-LINEAR_SPEED / 2) * sin(3.14159265 * (shape.getRotation() - 180) / 180)));
		}


		window.clear(); // mandatory to do before drawing stuff, so that shape doesn't actually get covered
		window.draw(shape); // this goes to a hidden buffer - display will copy this to the main buffer
		window.display(); // copies the hidden buffer to the main buffer (window) - this is double-buffering

	}

	return 0;
}
