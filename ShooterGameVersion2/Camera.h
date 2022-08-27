#pragma once
#include "SFML/Graphics.hpp"
//Camera class:
class Camera
{
private:
	sf::Vector2f position;
public:
	Camera(sf::Vector2f position) {
		this->position = position;
	}
	sf::Vector2f GetPos();
	//sets the position of the camera.
	void SetPos(sf::Vector2f pos);


};

