#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include "GameLogic.h"
#include <iostream>
#include <cstring>

#define FRAME_RATE 60
#define X_POSITION 0
#define Y_POSITION 0
#define RECT_SIZE 100.f
#define RECT_MOVING_FACTOR_X 60
#define RECT_MOVING_FACTOR_Y -65
#define CHANGE_DIRECTION -1
#define WINDOW_SIZE 800
using namespace std;


const char* SPEED_CHANGE_ENABLED = "speed_change_en"

int runGraphics(const char* speed,
				const char* direction,
				const char* size,
				const char* fullScreen,
				const char* name)
{
	int speedFactor = 1;
	//std::cout << "Enter your name: ";
	std::string name = new std::string(name);
	sf::Clock clock;
	
	bool changeSpeed;
	(strcmp(speed, SPEED_CHANGE_ENABLED) == 0) ? changeSpeed = true
	                                           : changeSpeed = false;

	//if (!std::getline(std::cin, name)) { /* I/O error! */ return -1; }

	/*if (!name.empty()) {
		std::cout << "thanks." << std::endl;
	}*/
	GameLogic* game = new GameLogic();

	game->startClocks(clockType::dir);
	game->startClocks(clockType::size);
	game->startClocks(clockType::speed);
	

	srand(time(NULL));
	bool gameInStartScreen = true;
	bool firstIteration = true;
	while (game->isOpen())
	{
		
		//move the rectangle
		sf::Event event;
		const sf::String userName = (const sf::String)name;
		game->setTitle(userName);
		if (firstIteration) {
			game->displyHelloMessage(name);
			firstIteration = false;
			game->getWindow()->display();
			clock.restart();
		}

		/*while (gameInStartScreen)
		{

			while (game->getWindow()->pollEvent(event))
			{
				switch (event.type)
				{
				case(sf::Event::Closed):
					game->getWindow()->close();
					break;
				case(sf::Event::EventType::KeyPressed ):
					if (event.key.code == sf::Keyboard::Space) {
						gameInStartScreen = false;
					}
					break;

				default:
					break;
				}
			}
		}*/
		game->checkClocks();

		sf::Time elapsed = clock.restart();
		//std::cout << elapsed.asMilliseconds() << '\n';


		float movingFactorX = elapsed.asSeconds()*RECT_MOVING_FACTOR_X*speedFactor;
		float movingFactorY = elapsed.asSeconds()*RECT_MOVING_FACTOR_Y * speedFactor;
		const sf::Vector2f & pos = game->getRect()->getPosition();
		/*checking for clocks events*/
		if (game->changeSpeed) {
            speedFactor = (rand() % (int)(7)) + 1;
		}

		if (game->changeSize) {
			float size = (rand() % (int)(70)) + 30;
			game->changeRectSize(size);
		}
		if (game->changeDirection) {
			game->rectInWindow();
		}

		if (!game->rectInWindow())
		{
			if (game->xIsOut) {
				float randNum = rand();
				float angleFactorX = static_cast <float> (randNum > 0 ? randNum: -randNum) / static_cast <float> (RAND_MAX);
				movingFactorX *= (angleFactorX)*10 ;
				game->changeXDirection *= CHANGE_DIRECTION;
				game->xIsOut = false;
			}
			if (game->yIsout) {
				float randNum = rand();
				float angleFactorY = static_cast <float> (randNum) / static_cast <float> (RAND_MAX);
				game->changeYDirection *= CHANGE_DIRECTION;
				movingFactorY *= (angleFactorY)*10 ;
				game->yIsout = false;
			}
		}

		const float & xPos = (pos.x - movingFactorX*game->changeXDirection);
		const float & yPos = (pos.y - movingFactorY*game->changeYDirection);
		game->RectSetPosition(xPos , yPos );
		

		while (game->getWindow()->pollEvent(event))
		{
			switch (event.type)
			{
			case(sf::Event::Closed):
				game->getWindow()->close();
				break;
			case(sf::Event::EventType::MouseMoved)://to change to insuming semple.
				game->getCircle()->setPosition(event.mouseMove.x, event.mouseMove.y);
			default:
				break;
			}
		}
		if (game->isCollision()) {
			game->getWindow()->clear(sf::Color());
		}
		else {
			game->getWindow()->clear(sf::Color(250, 150, 100));
		}
		game->getWindow()->draw((*game->getRect()));
		game->getWindow()->draw((*game->getCircle()));
		game->getWindow()->display();
	}



	return 0;
}
