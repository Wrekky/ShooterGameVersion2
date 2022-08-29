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

	/// <summary>
	/// Layer sorting fucntion. Used to update the gameObjects vector to change the order of objects drawn. Highber layer values should lead to the object being infront of lower layer value objects. (DOUBLE CHECK THIS)
	/// </summary>
	/// <param name="gameObjects">gameObjects vector.</param>
	/// <returns>Sorted gameObjects vector</returns>
	static std::vector<GameObject*> SortByLayer(std::vector<GameObject*> gameObjects);
	
	//Draws every game object, call every frame..

	/// <summary>
	/// Draws all objects to the screen 
	/// </summary>
	/// <param name="window">Window to draw to.</param>
	/// <param name="gameObjects">All gameobjects.</param>
	/// <param name="cam">Current camera being used.</param>
	static void DrawObjects(sf::RenderWindow & window, std::vector<GameObject*> gameObjects,Camera cam);
	
private:
	
};

