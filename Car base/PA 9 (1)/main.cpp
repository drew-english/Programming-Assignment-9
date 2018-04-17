#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

int main(void) // car base - expand on this please!
{
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!"); // opens the window
	//glEnable(GL_TEXTURE_2D);
	sf::RectangleShape shape(sf::Vector2f(120, 50));
	shape.setFillColor(sf::Color::Blue);
	shape.setPosition(400, 550);

	while (window.isOpen()) // keep the program running as long as the window is not closed by the user
	{
		sf::Event event;
		while (window.pollEvent(event)) // iterate through when user interface is detected (closing, key press, etc.)
		{
			if (event.type == sf::Event::Closed) // if user closes window, "officially" close the window
			{
				window.close();
			}
		}

		window.clear(); // mandatory to do before drawing stuff, so that shape doesn't actually get covered
		window.draw(shape); // this goes to a hidden buffer - display will copy this to the main buffer
		window.display(); // copies the hidden buffer to the main buffer (window) - this is double-buffering
	}

	return 0;
}