#include "Box2D.h"
#pragma once
class Collision
{
public:
	/// <summary>
	/// AABB box collision. Returns true if the provided boxes are colliding. 
	/// </summary>
	/// <param name="a">Box A to compare. </param>
	/// <param name="b">Box B to compare. </param>
	/// <returns>Returns True if either box is colliding with each other.</returns>
	static bool AABB(Box2D& a, Box2D& b);

private:
};

