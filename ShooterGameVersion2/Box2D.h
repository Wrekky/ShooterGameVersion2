#pragma once
#include <SFML/System/Vector2.hpp>
class Box2D
{
public:
	sf::Vector2f position;
	sf::Vector2f size;
	bool isColliding = false;
	Box2D() {
		position = sf::Vector2f(0,0);
		size = sf::Vector2f(0, 0);
	}
	Box2D(sf::Vector2f position, sf::Vector2f size) {
		this->position = position;
		this->size= size;
	}

};

