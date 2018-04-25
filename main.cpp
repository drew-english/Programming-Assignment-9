#include <SFML/Graphics.hpp>
#include <iostream>

int main(void) // car movement + goal
{
	float moveX = 20.0;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!"); // opens the window
	sf::RectangleShape shape(sf::Vector2f(120, 50)), goal(sf::Vector2f(20, 150)); // set goal position to wherever you want
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(400, 550);
	shape.setOrigin((shape.getSize().x * 0.5), (shape.getSize().y * 0.5));
	goal.setFillColor(sf::Color::White);
	goal.setPosition(500, 550);
	goal.setOrigin((goal.getSize().x * 0.5), (goal.getSize().y * 0.5));

	while (window.isOpen()) // keep the program running as long as the window is not closed by the user
	{
		sf::Event event;
		while (window.pollEvent(event)) // iterate through when user interface is detected (closing, key press, etc.)
		{
			switch (event.type)
			{
			case (sf::Event::Closed):
			{
				window.close();
			}
			case (sf::Event::KeyPressed):
			{
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A))) // turn left
				{
					shape.rotate(-10);
				}
				else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D))) // turn right
				{
					shape.rotate(10);
				}
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W))) // move forwards - movement obtained from: https://en.sfml-dev.org/forums/index.php?topic=4951.0
				{
					shape.move(sf::Vector2f(moveX * cos(3.14159265 * (shape.getRotation() - 180) / 180), moveX * sin(3.14159265 * (shape.getRotation() - 180) / 180)));
				}
				else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S))) // move backwards
				{
					shape.move(sf::Vector2f((-moveX / 2) * cos(3.14159265 * (shape.getRotation() - 180) / 180), (-moveX / 2) * sin(3.14159265 * (shape.getRotation() - 180) / 180)));
				}
			}
			}


		}
		if ((shape.getGlobalBounds().intersects(goal.getGlobalBounds())) && (((moveX / 2) * cos(3.14159265 * (shape.getRotation() - 180) / 180)) < 0))
		{
			std::cout << "GOAL!!!" << std::endl;
		}

		window.clear(); // mandatory to do before drawing stuff, so that shape doesn't actually get covered
		window.draw(shape); // this goes to a hidden buffer - display will copy this to the main buffer
		window.draw(goal);
		window.display(); // copies the hidden buffer to the main buffer (window) - this is double-buffering
	}

	return 0;
}