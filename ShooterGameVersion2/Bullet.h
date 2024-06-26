#include "GameObject.h";
#pragma once
class Bullet: public GameObject
{
public:
	float damage = 1;
	float speed = 1;
	float timeAlive = 0;
	Bullet(const GameObject gameObject): GameObject(gameObject)
	{
		this->damage = 1;
		this->speed = 1;
		bulletText.loadFromFile(bulletTextString);
		bulletText.setSmooth(true);
	}

	Bullet(std::string bulletTextureString);
	sf::Vector2f FireDirection(sf::Vector2f dir1, sf::Vector2f dir2);
private:
	std::string bulletTextString = "images/bullets/bullet-basic.png";
	sf::Texture bulletText;
};

