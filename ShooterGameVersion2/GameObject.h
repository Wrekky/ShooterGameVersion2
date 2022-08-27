#include "Box2D.h"
#include "Animation.h"
#include <string>
#include <vector>
#include "Physics2D.h"

#pragma once
class GameObject
{
public:
	Box2D box2d;
	Animation animation;
	Physics2D physics;
	std::string type = "";
	int layer = 0;
	bool debugDraw = true;

	//constructors
	GameObject(Box2D box2d,Animation animation,std::string type,Physics2D physics) {
		this->box2d = box2d;
		this->animation = animation;
		this->type = type;
		this->physics = physics;
	}
	GameObject(Box2D box2d, std::string type,Physics2D physics) {
		this->box2d = box2d;
		this->type = type;
		this->physics = physics;
	}
	GameObject(Box2D box2d, std::string type, int layer, Physics2D physics) {
		this->box2d = box2d;
		this->type = type;
		this->layer = layer;
		this->physics = physics;
	}
	GameObject() {
		physics = Physics2D(sf::Vector2f(0,0));
		type = "NULL";
	}
private:
	
};

