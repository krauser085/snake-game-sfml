#include <SFML\Graphics.hpp>
#include <iostream>

enum direction { stop, left, right, up, down };
direction d;

sf::Event event;
// window size const
const sf::Vector2f WINDOW_SIZE(1024, 768);

// for position of the charactor
sf::Vector2f position;

sf::Vector2f speed;

// speed limit of the charactor
const float F_LIMIT = 0.07;
const float B_LIMIT = -0.07;

sf::Texture imgHead;
sf::Sprite imagePlayer;
sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Green Snake!");

// set initial setting
int initialSetting() {
	// load image file from project folder into the texture
	if (!imgHead.loadFromFile("snake.png", sf::IntRect(256, 0, 64, 64))) {
		// if file loading failed show msg
		std::cout << "there's no file!" << std::endl;
	}

	imagePlayer.setTexture(imgHead);
	// initial direction
	d = stop;

	// initial position
	position.x = 320;
	position.y = 240;

	// initial speed;
	speed.x = 0;
	speed.y = 0;

	// set initial position of the charactor
	imagePlayer.setPosition(position.x, position.y);

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
		if (speed.x > 0) speed.x = 0;
		if (speed.x > B_LIMIT) speed.x -= 0.0001;

		if (speed.y > 0) speed.y -= 0.00005;
		else if (speed.y < 0) speed.y += 0.00005;
		break;
	case right:
		if (speed.x < 0) speed.x = 0;
		if (speed.x < F_LIMIT) speed.x += 0.0001;

		if (speed.y > 0) speed.y -= 0.00005;
		else if (speed.y < 0) speed.y += 0.00005;
		break;
	case up:
		if (speed.y > 0) speed.y = 0;
		if (speed.y > B_LIMIT) speed.y -= 0.0001;

		if (speed.x > 0) speed.x -= 0.00005;
		else if (speed.x < 0) speed.x += 0.00005;
		break;
	case down:
		if (speed.y < 0) speed.y = 0;
		if (speed.y < F_LIMIT) speed.y += 0.0001;

		if (speed.x > 0) speed.x -= 0.00005;
		else if (speed.x < 0) speed.x += 0.00005;
		break;
	}

	position.x += speed.x;
	position.y += speed.y;

	return 0;
}
// draw items
int draw() {
	// set position on each frame
	imagePlayer.setPosition(position.x, position.y);
	// clear on every frame
	window.clear(sf::Color::White);
	// draw the circle on every frame
	//window.draw(circle);
	window.draw(imagePlayer);
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