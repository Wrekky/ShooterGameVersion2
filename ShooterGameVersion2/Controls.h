#include "SFML/Graphics.hpp"
#pragma once
class Controls
{
public:
	sf::Keyboard::Key leftKey = sf::Keyboard::A;
	sf::Keyboard::Key rightKey = sf::Keyboard::D;
	sf::Keyboard::Key upKey = sf::Keyboard::W;
	sf::Keyboard::Key downKey= sf::Keyboard::S;
	sf::Keyboard::Key jumpKey = sf::Keyboard::Space;
	//constructors:
	Controls() {
	}
	Controls(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, sf::Keyboard::Key jumpKey) {
		this->leftKey = leftKey;
		this->rightKey = rightKey;
		this->upKey = upKey;
		this->downKey = downKey;
		this->jumpKey = jumpKey;
	}
	bool left;
	bool right;
	bool up;
	bool down;
	bool jump;


	//refresh controls function, call this once per frame.
	void Refresh();
};

