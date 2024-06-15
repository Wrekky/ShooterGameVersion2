#include "GameObject.h"
#pragma once
class Utils
{
public:
    static bool OnGround(GameObject obj, std::vector<GameObject*> objects);
    static sf::Vector2f FireDirection(sf::Vector2f dir1, sf::Vector2f dir2);
};

