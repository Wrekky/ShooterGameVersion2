#include "Utils.h"
#include "Collision.h"
bool Utils::OnGround(GameObject obj, std::vector<GameObject*> objects) {
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

sf::Vector2f Utils::FireDirection(sf::Vector2f dir1, sf::Vector2f dir2) {
    sf::Vector2f direction = dir1 - dir2;
    //divide by distance of both objects to normalize to 1
    float absSum = abs(direction.x) + std::abs(direction.y);
    if (absSum != 0) {
        return sf::Vector2f(direction.x / absSum, direction.y / absSum);
    }
    else {
        return sf::Vector2f(1, 0);
    }
}