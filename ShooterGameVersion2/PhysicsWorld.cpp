#include "PhysicsWorld.h"
std::vector<GameObject*> PhysicsWorld::Update(std::vector<GameObject*> allObjects) {
	for (int x = 0; x < allObjects.size(); x++) {

		Physics2D p2d = allObjects[x]->physics;
		if (p2d.enabled) {
			allObjects[x]->physics.velocity.y += gravity * allObjects[x]->physics.gravityRatio;
			//add gravity to velocity.
			//for every bit of velocity in either direction, add 1 to the objects current position and center.
			//If a collision occurs, stop that bit of velocity. Just make it zero for now.
			sf::Vector2f velocityRatio = sf::Vector2f(p2d.velocity.x / 10, p2d.velocity.y / 10);
			int z = 0;
			while (z != 10) {
				z++;
				//if x collision is less than y collision do x collision first.
				//get velocity ratio - how many x should i move for every y... no just add both.
				//add to current position, check for collisions. If no collision, add velocity. If collision, check both directions for collision and make the position fo the object the closest point between objects.
				//adding x velocity.
				allObjects[x]->box2d.position = sf::Vector2f(allObjects[x]->box2d.position.x + velocityRatio.x, allObjects[x]->box2d.position.y);
				//checking for collision
				//this should never be getting hit. Collision should never happen. Only adding xs... wait a collision is always happening?
				bool collision = false;
				for (int i = 0; i < allObjects.size(); i++) {
					if (i != x) {
						if (Collision::AABB(allObjects[x]->box2d, allObjects[i]->box2d)) {
							allObjects[x]->box2d.isColliding = true;
							//if collision is to the left.
							if (velocityRatio.x < 0) {
								allObjects[x]->box2d.position = sf::Vector2f(allObjects[i]->box2d.position.x + allObjects[i]->box2d.size.x + 0.1f, allObjects[x]->box2d.position.y);
							}
							//if collision is to the right.
							if (velocityRatio.x > 0) {
								allObjects[x]->box2d.position = sf::Vector2f(allObjects[i]->box2d.position.x - allObjects[x]->box2d.size.x - 0.1f, allObjects[x]->box2d.position.y);
							}
							allObjects[x]->physics.velocity.x = 0;
							collision = true;
						}
					}
				}

				//adding y velocity.
				allObjects[x]->box2d.position = sf::Vector2f(allObjects[x]->box2d.position.x, allObjects[x]->box2d.position.y + velocityRatio.y);
				//checking for collision
				for (int i = 0; i < allObjects.size(); i++) {
					if (i != x) {
						if (Collision::AABB(allObjects[x]->box2d, allObjects[i]->box2d)) {
							allObjects[x]->box2d.isColliding = true;
							//if collision is to the up.
							if (velocityRatio.y < 0) {
								allObjects[x]->box2d.position = sf::Vector2f(allObjects[x]->box2d.position.x, allObjects[i]->box2d.position.y + allObjects[i]->box2d.size.y + 0.1f);
							}
							//if collision is to the down.
							if (velocityRatio.y > 0) {

								allObjects[x]->box2d.position = sf::Vector2f(allObjects[x]->box2d.position.x, allObjects[i]->box2d.position.y - allObjects[x]->box2d.size.y - 0.1f);

							}
							allObjects[x]->physics.velocity.y = 0;
							collision = true;
						}
					}
				}
				if (collision) {
					allObjects[x]->box2d.isColliding = true;
				}
				else {
					allObjects[x]->box2d.isColliding = false;
				}
			}

		}
	}
	return allObjects;
}
