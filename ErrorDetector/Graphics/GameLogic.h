#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#ifndef GAMELOGIC_H
#define GAMELOGIC_H 
using namespace std;

enum clockType
{
	size, dir, speed
};


class GameLogic
{
public:
    GameLogic(bool fullScreen = true);
	~GameLogic();
	bool isCollision();
	bool rectInWindow();
	sf::RenderWindow* getWindow();
	sf::RectangleShape* getRect();
	sf::RectangleShape* getSmallRect();
	sf::CircleShape* getCircle();
	bool setTitle(const sf::String name);
	bool xIsOut = false;
	bool yIsout = false;
	bool isOpen();
	float changeXDirection;
	float changeYDirection;
	void displyHelloMessage(string userName);
	void RectSetPosition(const float & xPos, const float & yPos);
	sf::Text text;
	bool takeName();
	string userName;
	void startClocks(clockType type);
	void checkClocks();
	bool changeDirection = false;
	bool changeSpeed = false;
	bool changeSize = false;
	void changeRectSize(float size = 100.f);
	int screenHeight;
private:
	bool nameEntered = false;
	sf::Clock size_clock;
	sf::Clock direction_clock;
	sf::Clock speed_clock;

	bool speed_change = false;
	bool size_change = false;
	bool direction_change = false;
	bool split_rects = false;

	int sizeChangeTime = 3;
	int directionChangeTime = 5;
	int speedChangeTime = 7;

	int rectSize = 100;

	const std::vector< sf::VideoMode>& vid = sf::VideoMode::getFullscreenModes();
	sf::RenderWindow* window;
	sf::CircleShape* shapeCircle;
	sf::RectangleShape* shapeRect;
	sf::RectangleShape* shapeRect_small;
	
	
};
#endif // !GAMELOGIC_H

