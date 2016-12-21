#include <SFML\Graphics.hpp>
#include <iostream>
#include <list>

enum direction { stop, left, right, up, down };
direction d;

sf::Event event;
// window size const
const sf::Vector2f WINDOW_SIZE(1024, 768);

// for position of the charactor
sf::Vector2f position;
std::list<float> positionListX;
std::list<float> positionListY;
sf::Vector2i positionFruit;

sf::Vector2f speed;

// speed limit of the charactor
const float F_LIMIT = 0.4;
const float B_LIMIT = -0.4;

int bodyLength = 1;
int delayFrame = 0;
// temp circle shape for test
sf::CircleShape circle;
sf::CircleShape circleBody;

sf::Texture imgHead;
sf::Texture imgFruit;
sf::Sprite imagePlayer;
sf::Sprite imagePlayer2;
sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Green Snake!");

// set initial setting
int initialSetting() {
	// load image file from project folder into the texture
	if (!imgHead.loadFromFile("snake.png")) {
		// if file loading failed show msg
		std::cout << "there's no file!" << std::endl;
	}
	
	//temp implements
	circle.setRadius(30);
	circle.setFillColor(sf::Color::Blue);
	circleBody.setRadius(30);
	circleBody.setFillColor(sf::Color::Green);

	imgFruit.loadFromFile("snake.png", sf::IntRect(0,192,64,64));

	imagePlayer.setTexture(imgHead);
	imagePlayer2.setTexture(imgFruit);
	imagePlayer.setTextureRect(sf::IntRect(256, 0, 64, 64));
	// initial direction
	d = stop;

	// initial position
	position.x = 320;
	position.y = 240;
	srand(time(NULL));
	positionFruit.x = std::rand() % (int)WINDOW_SIZE.x;
	positionFruit.y = std::rand() % (int)WINDOW_SIZE.y;

	// initial speed;
	speed.x = 0;
	speed.y = 0;

	// set initial position of the charactor
	imagePlayer.setPosition(position.x, position.y);
	
	// temp implement
	circle.setPosition(position.x, position.y);

	imagePlayer2.setPosition(positionFruit.x, positionFruit.y);
	return 0;
}

// get input from Keyboard
int getInput() {
	while (window.pollEvent(event)) {

		switch (event.type) {
			// close window when click the exit button
			window.close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::Left:
				d = left;
				break;
			case sf::Keyboard::Right:
				d = right;
				break;
			case sf::Keyboard::Up:
				d = up;
				break;
			case sf::Keyboard::Down:
				d = down;
				break;
			}
			break;
		}
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
	return 0;
}
int logic() {
	// move circle
	switch (d) {
	case left:
		// set head direction
		imagePlayer.setTextureRect(sf::IntRect(192, 64, 64, 64));
		// set speed
		if (speed.x > 0) speed.x = 0;
		if (speed.x > B_LIMIT) speed.x -= 0.0001;

		if (speed.y > 0) speed.y -= 0.00005;
		else if (speed.y < 0) speed.y += 0.00005;
		break;
	case right:
		// set head direction
		imagePlayer.setTextureRect(sf::IntRect(256, 0, 64, 64));
		// set speed
		if (speed.x < 0) speed.x = 0;
		if (speed.x < F_LIMIT) speed.x += 0.0001;

		if (speed.y > 0) speed.y -= 0.00005;
		else if (speed.y < 0) speed.y += 0.00005;
		break;
	case up:
		// set head direction
		imagePlayer.setTextureRect(sf::IntRect(192, 0, 64, 64));
		
		// set speed
		if (speed.y > 0) speed.y = 0;
		if (speed.y > B_LIMIT) speed.y -= 0.0001;

		if (speed.x > 0) speed.x -= 0.00005;
		else if (speed.x < 0) speed.x += 0.00005;
		break;
	case down:
		// set head direction
		imagePlayer.setTextureRect(sf::IntRect(256, 64, 64, 64));
		
		// set speed
		if (speed.y < 0) speed.y = 0;
		if (speed.y < F_LIMIT) speed.y += 0.0001;

		if (speed.x > 0) speed.x -= 0.00005;
		else if (speed.x < 0) speed.x += 0.00005;
		break;
	}

	position.x += speed.x;
	position.y += speed.y;

	// set position of fruit again
	if (position.x + 32 > positionFruit.x && position.x - 32 < positionFruit.x &&
		position.y + 32 > positionFruit.y && position.y - 32 < positionFruit.y) {
		std::cout << "snake ate fruit" << std::endl;
		positionFruit.x = std::rand() % (int)WINDOW_SIZE.x;
		positionFruit.y = std::rand() % (int)WINDOW_SIZE.y;
		
		bodyLength++;
	}
	if (delayFrame == 100) {
		positionListX.push_front(position.x);
		positionListY.push_front(position.y);
		delayFrame = 0;
	}
	while (bodyLength < positionListX.size()) {
		positionListX.pop_back();
		positionListY.pop_back();
	}
	delayFrame++;
	return 0;
}
// draw items
int draw() {

	// set position on each frame
	imagePlayer.setPosition(position.x, position.y);
	// temp implement
	circle.setPosition(position.x, position.y);

	imagePlayer2.setPosition(positionFruit.x, positionFruit.y);

	// clear on every frame
	window.clear(sf::Color::White);
	// draw the circle on every frame
	window.draw(imagePlayer2);
	//window.draw(imagePlayer);
	//temp implement
	std::list<float>::iterator i;
	std::list<float>::iterator y;
	for (i = positionListX.begin(); i != positionListX.end() ; ++i) {
		y = positionListY.begin();
		//std::cout << *i << std::endl;
		
		circleBody.setPosition(*i, *y);
		window.draw(circleBody);
		y++;
	}
	window.draw(circle);

	// display what window has done on every frame
	window.display();
	return 0;
}

int main() {

	initialSetting();

	while (window.isOpen()) {
		// get input direction from keyboard
		getInput();
		logic();
		// move the charactor with the result of input
		draw();
	}
	return 0;
}