#include "Collision.h"
bool Collision::AABB(Box2D& a, Box2D& b) {
	if (((a.position.x <= b.position.x + b.size.x) && a.position.x >= b.position.x) || (a.position.x + a.size.x >= b.position.x && a.position.x <= b.position.x)) {
		//x axis is colliding
		if (((a.position.y <= b.position.y + b.size.y) && a.position.y >= b.position.y) || (a.position.y + a.size.y >= b.position.y && a.position.y <= b.position.y)) {
			//y axis is colliding
			//collision on both axis should mean collision is happening
			return true;
		}
	}
	return false;
}