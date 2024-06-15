#include "GameObject.h"
#include "Controls.h"
#include "Bullet.h"
#pragma once
class Player: public GameObject
{
public:
	Player(sf::Vector2f position);
	void PlayerJump();
	void PlayerMovement(Controls controls);
	Bullet Fire(GameObject weapon, sf::Vector2f fireDirection);
private:
	float speedCap = 6.0f;
	float speed = 1.0f;
	float friction = 0.5f;
};

