#include "GameLogic.h"

#define FRAME_RATE 60
#define X_POSITION 0
#define Y_POSITION 0
#define RECT_MOVING_FACTOR 60
#define CHANGE_DIRECTION -1
int g_WINDOW_SIZE  = 600;
#define RECT_FRAME_SIZE 100
#define DISTANCE_FROM_ORIGIN 1
#define FONT_FILE_LOCATION "font/vtks-giz/font.ttf"
#define HELLO_MSG ",\nin this game you should\nkeep the green dot\ninside the red rectengle\nat all time.\nTo Start Please Press\nthe space Button.\n\n               enjoy."
using namespace std;


GameLogic::GameLogic(bool fullScreen , int numOfEdges)
{

	const std::vector< sf::VideoMode>& vid = sf::VideoMode::getFullscreenModes();
    if(fullScreen)
    {
			g_WINDOW_SIZE = vid[0].height;

        GameLogic::window = new sf::RenderWindow(sf::VideoMode(g_WINDOW_SIZE, g_WINDOW_SIZE), "Error Detector", sf::Style::Default);
		GameLogic::window->setPosition(sf::Vector2i(-vid[0].width/2,0));

    }
    else{
			g_WINDOW_SIZE = vid[0].height;

		GameLogic::window = new sf::RenderWindow(sf::VideoMode(g_WINDOW_SIZE, g_WINDOW_SIZE), "Error Detector", sf::Style::Default);

        //GameLogic::window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Error Detector", sf::Style::Default);
        GameLogic::window->setPosition(sf::Vector2i(-vid[0].width/2,0));

    }
    _pattern.init(numOfEdges);//setting the current pattern
    framesPatternCounter = _pattern.getNextCounter();
    screenHeight = g_WINDOW_SIZE;
	GameLogic::shapeCircle = new sf::CircleShape(10.f);
    GameLogic::shapeRect = new sf::RectangleShape(sf::Vector2f(rectSize, rectSize));
    GameLogic::shapeRect_small = new sf::RectangleShape(sf::Vector2f(rectSize-40, rectSize-40));
	changeRectSize();


	GameLogic::shapeCircle->setFillColor(sf::Color::Green);
	GameLogic::shapeCircle->setOrigin(X_POSITION, Y_POSITION);
    GameLogic::shapeRect->setOrigin(0, 0);
    GameLogic::shapeRect->setPosition((g_WINDOW_SIZE/2)-50,(g_WINDOW_SIZE/2)-50);
    GameLogic::shapeRect_small->setOrigin(0, 0);
	//GameLogic::shapeRect_small->setPosition(g_WINDOW_SIZE/2,g_WINDOW_SIZE/2);
	GameLogic::window->setFramerateLimit(FRAME_RATE);
	GameLogic::changeXDirection = 0.5;
	GameLogic::changeYDirection = 0.5;
}
/*Destructor*/
GameLogic::~GameLogic()
{
	delete GameLogic::window;
	delete GameLogic::shapeCircle;
	delete GameLogic::shapeRect;
}

/*This function is to check if there is cillision between the rect and the pointer. */
bool GameLogic::isCollision() {
	float circleX = this->shapeCircle->getPosition().x;
	float circleY = this->shapeCircle->getPosition().y;
	float rectX = this->shapeRect->getPosition().x;
	float rectY = this->shapeRect->getPosition().y;
	if (circleX - rectX > rectSize || circleY - rectY > rectSize
		|| circleX - rectX < DISTANCE_FROM_ORIGIN || circleY - rectY < DISTANCE_FROM_ORIGIN)
		return false;
	else
		return true;

}

/*Function to check if the rect is getting to the windows border*/
bool GameLogic::rectInWindow() {
	if (changeDirection) {
		xIsOut = true;
		yIsout = true;
		return false;
	}
	sf::Vector2f temp = this->shapeRect->getPosition();
	int x = temp.x + DISTANCE_FROM_ORIGIN;
	int y = temp.y + DISTANCE_FROM_ORIGIN;
	
	if (x > this->window->getSize().y - rectSize || x < DISTANCE_FROM_ORIGIN) {
		xIsOut = true;
	}
	if (y > this->window->getSize().y - rectSize || y < DISTANCE_FROM_ORIGIN) {
		yIsout = true;
	}
	if (xIsOut || yIsout) {
		
		return false;
	}
	return true;

}

int GameLogic::getFrameNum(){
	return framesPatternCounter;
}

void GameLogic::updatePattern(){
	if(_pattern.update()){
		GameLogic::shapeRect->setPosition((g_WINDOW_SIZE/2)-50,(g_WINDOW_SIZE/2)-50);
		GameLogic::changeXDirection = 0.5;
		GameLogic::changeYDirection = 0.5;
		if(rand() % 2 == 1)
			this->split_rects = true;
	}
	framesPatternCounter = _pattern.getNextCounter();
}

sf::RenderWindow* GameLogic::getWindow() {
	return GameLogic::window;
}

sf::RectangleShape* GameLogic::getRect() {
	return this->shapeRect;
}

sf::RectangleShape* GameLogic::getSmallRect() {
	return this->shapeRect_small;
}

sf::CircleShape* GameLogic::getCircle() {
	return this->shapeCircle;
}

bool GameLogic::isOpen() {
	return this->window;
}

bool GameLogic::setTitle(const sf::String name) {
	GameLogic::window->setTitle(name);
	return true;
}
int g_splitRectsCounter = 0;

void GameLogic::RectSetPosition(const float & xPos, const float & yPos) {
	this->shapeRect->setPosition(xPos, yPos);
		if(!this->split_rects){
		this->shapeRect_small->setPosition(xPos+20, yPos+20);
	}
	else{
		g_splitRectsCounter++;
		if(g_splitRectsCounter == 80){
			this->split_rects = false;
			g_splitRectsCounter = 0;
		}	
	}
}

bool GameLogic::takeName()
{
	std::cout << "Enter your name: ";
	std::string name;

	if (!std::getline(std::cin, name)) { /* I/O error! */ return false; }

	if (!name.empty()) {
		std::cout << "thanks." << std::endl;
	}
	return true;
}

void GameLogic::startClocks(clockType type)
{
	switch (type)
	{
	case clockType::size:
		size_clock.restart();
		break;
	case dir:
		direction_clock.restart();
		break;
	case speed:
		speed_clock.restart();
		break;
	default:
		break;
	}

}

void GameLogic::checkClocks()
{
	if (changeDirection) {
		if (direction_clock.getElapsedTime().asSeconds() > directionChangeTime)
		{
			changeDirection = true;
			startClocks(clockType::dir);
		}
		else{
			changeDirection = false;
		}
	}
	if (changeSpeed) {
		if (speed_clock.getElapsedTime().asSeconds() > speedChangeTime) {
			changeSpeed = true;
			startClocks(clockType::speed);
		}
		else {
			changeSpeed = false;
		}

	}
	if (changeSize) {
		if (size_clock.getElapsedTime().asSeconds() > sizeChangeTime) {
			changeSize = true;
			startClocks(clockType::size);
		}
		else {
			changeSize = false;
		}

	}
}
void GameLogic::changeRectSize(float size)
{

	GameLogic::shapeRect->setSize(sf::Vector2f(size, size));
	GameLogic::shapeRect->setFillColor(sf::Color::Black);
	GameLogic::shapeRect->setOutlineThickness(5);
	GameLogic::shapeRect->setOutlineColor(sf::Color(250, 0, 0));
	
	GameLogic::shapeRect_small->setSize(sf::Vector2f(size-40, size-40));
	GameLogic::shapeRect_small->setFillColor(sf::Color::Black);
	GameLogic::shapeRect_small->setOutlineThickness(5);
	GameLogic::shapeRect_small->setOutlineColor(sf::Color(250, 250, 0));
	rectSize = size;

}

void GameLogic::displyHelloMessage(string userName) {
	// select the font
	sf::Font myFont;
	//const string fileLocation = FONT_FILE_LOCATION;
	//bool a = myFont.loadFromFile(fileLocation);
	text.setFont(myFont); // font is a sf::Font

	text.setString("Hello " + userName + HELLO_MSG);

	// set the character size
	text.setCharacterSize(24); // in pixels, not points!

	//text.setFillColor(sf::Color::Blue);

	text.setPosition(50, 50);

	// set the text style
	text.setStyle(sf::Text::Bold );

	GameLogic::window->clear(sf::Color::White);

	GameLogic::window->draw(text);
}


