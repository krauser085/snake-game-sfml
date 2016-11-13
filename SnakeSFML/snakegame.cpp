#include <SFML\Graphics.hpp>
#include <iostream>

enum direction { stop, left, right, up, down };
direction d;

sf::Event event;

// window size const
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

// for position of the charactor
float hPostion; // horizontal position
float vPostion; // vertical position
				// for current speed of the charactor
float hSpeed;
float vSpeed;
// speed limit of the charactor
const float F_LIMIT = 0.07;
const float B_LIMIT = -0.07;

sf::Texture image;
sf::Sprite imagePlayer;
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Green Snake!");

// set initial setting
int initialSetting() {
	// load image file from project folder into the texture
	if (!image.loadFromFile("snake.png", sf::IntRect(256, 0, 64, 64))) {
		// if file loading failed show msg
		std::cout << "there's no file!" << std::endl;
	}

	imagePlayer.setTexture(image);
	// initial direction
	d = stop;

	// initial position
	hPostion = 320;
	vPostion = 240;

	// initial speed;
	hSpeed = 0;
	vSpeed = 0;

	// set initial position of the charactor
	imagePlayer.setPosition(hPostion, vPostion);

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

// draw items
int draw() {
	// move circle
	switch (d) {
	case left:
		if (hSpeed > 0) hSpeed = 0;
		if (hSpeed > B_LIMIT) hSpeed -= 0.0001;

		if (vSpeed > 0) vSpeed -= 0.00005;
		else if (vSpeed < 0) vSpeed += 0.00005;
		break;
	case right:
		if (hSpeed < 0) hSpeed = 0;
		if (hSpeed < F_LIMIT) hSpeed += 0.0001;

		if (vSpeed > 0) vSpeed -= 0.00005;
		else if (vSpeed < 0) vSpeed += 0.00005;
		break;
	case up:
		if (vSpeed > 0) vSpeed = 0;
		if (vSpeed > B_LIMIT) vSpeed -= 0.0001;

		if (hSpeed > 0) hSpeed -= 0.00005;
		else if (hSpeed < 0) hSpeed += 0.00005;
		break;
	case down:
		if (vSpeed < 0) vSpeed = 0;
		if (vSpeed < F_LIMIT) vSpeed += 0.0001;

		if (hSpeed > 0) hSpeed -= 0.00005;
		else if (hSpeed < 0) hSpeed += 0.00005;
		break;
	}

	hPostion += hSpeed;
	vPostion += vSpeed;
	// set position on each frame
	imagePlayer.setPosition(hPostion, vPostion);
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
		// move the charactor with the result of input
		draw();
	}
	return 0;
}