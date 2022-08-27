#include <vector>
#include "GameObject.h"
#include <algorithm>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Camera.h"
#pragma once

static class Draw
{

public:
	//Layer sorting function, use when updating the gameObjects vector.
	static std::vector<GameObject*> SortByLayer(std::vector<GameObject*> gameObjects);
	
	//Draws every game object, call every frame..
	static void DrawObjects(sf::RenderWindow & window, std::vector<GameObject*> gameObjects,Camera cam);
	
private:
	
};

