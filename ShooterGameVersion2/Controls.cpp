#include "Controls.h"
void Controls::Refresh() {
	left = false;
	right = false;
	up = false;
	down = false;
	jump = false;

	if (sf::Keyboard::isKeyPressed(leftKey)) {
		left = true;
	}
	if (sf::Keyboard::isKeyPressed(rightKey)) {
		right = true;
	}
	if (sf::Keyboard::isKeyPressed(upKey)) {
		up = true;
	}
	if (sf::Keyboard::isKeyPressed(downKey)) {
		down = true;
	}
	if (sf::Keyboard::isKeyPressed(jumpKey) && jump == false) {
		jump = true;
	}
}