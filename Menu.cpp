#include "Menu.h"

Menu::Button::Button(sf::Text text, sf::Vector2f size)
{
	font.loadFromFile("Roboto-Regular.ttf");
	//font.loadFromFile("Xenotron.ttf");
	this->text = text;
	this->text.setFont(font);

	shape.setSize(size);

	this->setPosition(sf::Vector2f(30.0f, 30.0f));



	shape.setFillColor(sf::Color::White);
	this->text.setFillColor(sf::Color::Red);
	this->text.setOutlineColor(sf::Color::Black);
	this->text.setOutlineThickness(.33);
	shown = true;
}

void Menu::Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(shape, states);
	target.draw(text, states);
}

void Menu::Button::setPosition(sf::Vector2f pos)
{
	shape.setPosition(pos);
	float height, width;
	height = (shape.getPosition().y) + (shape.getLocalBounds().height / 2) - text.getLocalBounds().height *.65;
	width = (shape.getPosition().x) + shape.getLocalBounds().width / 2 - (text.getLocalBounds().width) *.5;
	text.setPosition(sf::Vector2f(width, height));
}

sf::RectangleShape & Menu::Button::getShape()
{
	return shape;
}


void Menu::Button::darken()
{
	shape.setFillColor(sf::Color::Yellow);
}

void Menu::Button::lighten()
{
	shape.setFillColor(sf::Color::White);
}

void Menu::Button::setBool(bool newValue)
{
	mouseOnButton = newValue;
}

bool Menu::Button::getBool()
{
	return mouseOnButton;
}

bool Menu::Button::getIfShown()
{
	return shown;
}

void Menu::Button::setShown(bool newValue)
{
	shown = newValue;
}


bool Menu::runMenu()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Andy 500");

	sf::Text texts[25];

	sf::Mouse mouse;
	sf::Event event, event2;
	sf::Text text;
	text.setString("Play Game");
	Menu::Button playButton(text, sf::Vector2f(500.0f, 50.0f));
	text.setString("View Readme");
	Menu::Button readmeButton(text, sf::Vector2f(500.0f, 50.0f));
	text.setString("Exit");
	Menu::Button exitButton(text, sf::Vector2f(500.0f, 50.0f));
	sf::Vector2f temp;
	temp.x = window.getSize().x / 2 - playButton.getShape().getLocalBounds().width / 2;
	temp.y = window.getSize().y / 3 + 25;
	playButton.setPosition(temp);
	temp.y += 75;
	readmeButton.setPosition(temp);
	temp.y += 75;
	exitButton.setPosition(temp);

	sf::Text title;
	sf::Font font;
	font.loadFromFile("RobotoCondensed-BoldItalic.ttf");
	//font.loadFromFile("Xenotron.ttf");
	title.setFont(font);
	title.setString("Tank Fight III: Return of O'Fallon");
	title.setCharacterSize(50);
	title.setColor(sf::Color::Magenta);
	title.setOutlineColor(sf::Color::White);
	title.setOutlineThickness(2);
	title.setPosition(sf::Vector2f(window.getSize().x / 2 - title.getLocalBounds().width / 2, window.getSize().y / 5));
	sf::Text credit;
	credit.setFont(font);
	credit.setColor(sf::Color::White);
	credit.setString("Developed By: Karl Estes, Connor Pitt, Darren Guzman, and Ryan Bailey");
	credit.setCharacterSize(20);
	credit.setPosition(sf::Vector2f(window.getSize().x / 2 - credit.getLocalBounds().width / 2, window.getSize().y - credit.getLocalBounds().height - 10));



	sf::RectangleShape shape = playButton.getShape();
	playButton.setBool(false);

	bool gameMenu = false;

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}




		///Figure out why this function is running slowly
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))) // is there a mouse click AND is the mouse over the button?
		{
			if (Menu::checkMouseBounds(mouse, playButton.getShape(), &window)) ///BUTTON HAS TO BE PRESSED AND HELD
			{
				window.close();
				return true; //run the game loop
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (Menu::checkMouseBounds(mouse, readmeButton.getShape(), &window))
				system("C:\\Users\\Aweso\\Desktop\\\"Cpts 122 Projects\"\\\"CPTS 122 Final Project\"\\\"CPTS 122 Final Project\"\\readme.txt"); //needs to be changed for each computer
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (checkMouseBounds(mouse, exitButton.getShape(), &window))
				window.close();
			return false;
		}

		if (checkMouseBounds(event, shape))
			playButton.setBool(true);
		else
			playButton.setBool(false);

		if (checkMouseBounds(event, readmeButton.getShape()))
			readmeButton.setBool(true);
		else
			readmeButton.setBool(false);

		if (checkMouseBounds(event, exitButton.getShape()))
			exitButton.setBool(true);
		else
			exitButton.setBool(false);


		if (playButton.getBool()) //changes the color of the button in relation to the mouse hovering over it
			playButton.darken();
		else
			playButton.lighten();

		if (readmeButton.getBool())
			readmeButton.darken();
		else
			readmeButton.lighten();

		if (exitButton.getBool())
			exitButton.darken();
		else
			exitButton.lighten();

		window.clear();

		if (playButton.getIfShown()) // enables the buttons to be hidden if need be
			window.draw(playButton);
		if (readmeButton.getIfShown())
			window.draw(readmeButton);
		if (exitButton.getIfShown())
			window.draw(exitButton);

		window.draw(title);
		window.draw(credit);



		//	window.draw(text);

		//	std::cout << "Mouse X: " << event.mouseMove.x << " Mouse Y: " << event.mouseMove.y << std::endl;
		//	std::cout << "Shape X: " << shape.getPosition().x << " Shape Y: " << shape.getPosition().y << std::endl;
		//	std::cout << checkMouseBounds(event, shape) << std::endl;


		//countDownText(window, texts);  //my attempt at a countdown timer

		//for (int i = 10; i > 0; i--)
		//{
		//	window.draw(texts[i]);
		//	_sleep(1000);
		//}


		window.display();

	}
}

bool Menu::checkMouseBounds(sf::Event & event, sf::RectangleShape shape)
{
	int mXPos = event.mouseMove.x;
	int mYPos = event.mouseMove.y;


	//checks if the mouse's x AND y position is within the bounds of the box
	if ((mXPos >= shape.getPosition().x && mXPos < (shape.getPosition().x + shape.getSize().x)) && mYPos >= shape.getPosition().y && mYPos < (shape.getPosition().y + shape.getSize().y))
		return true;
	else
		return false;
}

bool Menu::checkMouseBounds(sf::Mouse & mouse, sf::RectangleShape & shape, sf::RenderWindow *gameWindow)
{
	int mXPos = mouse.getPosition(*gameWindow).x;
	int mYPos = mouse.getPosition(*gameWindow).y;

	//std::cout << "XPos Mouse: " << mXPos << std::endl;
	//std::cout << "YPos Mouse: " << mYPos << std::endl;
	//std::cout << "XPos Button: " << shape.getGlobalBounds().left << std::endl;
	//std::cout << "YPos Button: " << shape.getGlobalBounds().top << std::endl;

	//checks if the mouse's x AND y position is within the bounds of the box
	if ((mXPos >= shape.getPosition().x && mXPos < (shape.getPosition().x + shape.getSize().x)) && mYPos >= shape.getPosition().y && mYPos < (shape.getPosition().y + shape.getSize().y))
		return true;
	else
		return false;

}

