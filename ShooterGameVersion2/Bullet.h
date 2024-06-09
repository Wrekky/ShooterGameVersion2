#include "GameObject.h";
#pragma once
class Bullet: public GameObject
{
public:
	float damage = 1;
	float speed = 1;
	Bullet(std::string bulletTextureString);
	Bullet();
	GameObject Fire(GameObject weapon, sf::Vector2f fireDirection);
	sf::Vector2f FireDirection(sf::Vector2f dir1, sf::Vector2f dir2);
private:
	std::string bulletTextString = "images/bullets/bullet-basic.png";
	sf::Texture bulletText;
};

