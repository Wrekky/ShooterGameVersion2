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
	bool left = false;
	bool right = false;
	bool up = false;
	bool down = false;
	bool jump = false;
	//constructors:
	Controls() {
		this->leftKey = sf::Keyboard::Key::A;
		this->rightKey = sf::Keyboard::Key::D;
		this->upKey = sf::Keyboard::Key::W;
		this->downKey = sf::Keyboard::Key::S;
		this->jumpKey = sf::Keyboard::Key::Space;
	}
	Controls(sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, sf::Keyboard::Key jumpKey) {
		this->leftKey = leftKey;
		this->rightKey = rightKey;
		this->upKey = upKey;
		this->downKey = downKey;
		this->jumpKey = jumpKey;
	}


	/// <summary>
	/// Refreshes controls, call this once per frame.
	/// </summary>
	void Refresh();
};

