#pragma once
#include <SFML/System/Vector2.hpp>
class Physics2D
{
	//Should be an instance. -- every game object will have a physics 2d property, with a bool that enables or disables it. 
	//Needs to include objects mass, bounciness, velocity.
public:
	bool enabled = true;
	bool collisionsEnabled = true;
	sf::Vector2f velocity;
	sf::Vector2f center;
	float mass = 0;
	float bounciness = 0;
	float gravityRatio = 1.0f;
	Physics2D(sf::Vector2f velocity, sf::Vector2f center, float mass, float bounciness) {
		this->mass = mass;
		this->bounciness = bounciness;
		this->velocity = velocity;
		this->center = center;
	}
	Physics2D(sf::Vector2f velocity, sf::Vector2f center) {
		this->mass = 100;
		this->bounciness = 0;
		this->velocity = velocity;
		this->center = center;
	}
	Physics2D(sf::Vector2f center) {
		this->mass = 100;
		this->bounciness = 0;
		this->velocity = sf::Vector2f(0, 0);
		this->center = center;
	}
	Physics2D(sf::Vector2f center,bool enabled) {
		this->mass = 100;
		this->bounciness = 0;
		this->velocity = sf::Vector2f(0, 0);
		this->center = center;
		this->enabled = enabled;
	}
	Physics2D() {
		//dont use me
	}
};

