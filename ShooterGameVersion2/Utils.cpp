#include "Utils.h"
#include "Collision.h"
static bool OnGround(GameObject obj, std::vector<GameObject*> objects) {
    Box2D box;
    box = obj.box2d;
    box.position = sf::Vector2f(box.position.x + 1, box.position.y + box.size.y + 1);
    box.size = sf::Vector2f(box.size.x - 2, 2);
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->physics.collisionsEnabled) {
            if (Collision::AABB(box, objects[i]->box2d)) {
                return true;
            }
        }
    }
    return false;
}