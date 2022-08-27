#include "Camera.h"
sf::Vector2f Camera::GetPos() {
	return this->position;
}
//sets the position of the camera.
void Camera::SetPos(sf::Vector2f pos) {
	this->position = pos;
}