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
	/// <summary>
	/// Gets position of the camera
	/// </summary>
	/// <returns></returns>
	sf::Vector2f GetPos();
	/// <summary>
	/// Sets the position of the camera
	/// </summary>
	/// <param name="pos">position</param>
	void SetPos(sf::Vector2f pos);


};

