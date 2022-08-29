#pragma once
#include <vector>
#include "GameObject.h"
#include "Collision.h"
#include <iostream>
class PhysicsWorld
{
public:
	//Gravity multiplier, higher multiplier = heavier objects.
	float gravity = 0.2f;
	//Applies object velocity and adjusts collisions accordingly.
	std::vector<GameObject*> Update(std::vector<GameObject*> allObjects);
};

