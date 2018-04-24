#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Car.h"
int main()
{
	//Menu::runMenu();

	enum keys
	{
		W=0,
		A=1,
		S=2,
		D=3

	};
	sf::RenderWindow window(sf::VideoMode(1500, 1000), "SFML works!");
	Car p1(*(new sf::Vector2f(0, 0)),
		sf::Color::Yellow,
		*(new sf::Vector2f(window.getSize().x*0.25, window.getSize().y*.33)));
	
	bool kp = false;
	float pos = 0.0;
	bool arr[4];

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				kp = true;
				pos += 0.5;
				if (event.key.code == sf::Keyboard::S)
				{
					p1.move(0, 4);
				}
				if (event.key.code == sf::Keyboard::D)
				{
					p1.move(4, 0);
				}
				if (event.key.code == sf::Keyboard::W)
				{
					p1.move(0, -4);
				}
				if (event.key.code == sf::Keyboard::A)
				{
					p1.move(-4, 0);
				}
				if (event.type == sf::Event::KeyReleased)
				{
					kp = false;
					p1.move(0, pos);
				}

			}
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(p1);
		window.display();
	}

	
	return 0;
}