#pragma once
#include "SFML/Graphics.hpp"
class Animation
{
public:
	bool flipped = false;
	int framerate = 0;
	float currentFrame = 0;
	int count = 0;
	int currentImageCount=0;
	sf::Vector2u spriteSize;
	sf::Texture currentImage;
	sf::Vector2i textureSize = sf::Vector2i(50,50);
	sf::Vector2i texturePos = sf::Vector2i(0, 0);
	Animation(sf::Texture currentImage,int count) {
		this->currentImage = currentImage;
		this->count = count-1;
		spriteSize = sf::Vector2u(currentImage.getSize().x/count, currentImage.getSize().y);
	}
	Animation() {

	}
	void Animate() {
		if (currentImageCount < count) {
			currentImageCount++;
		}
		else {
			currentImageCount = 0;
		}
	}
	void Reset() {
		currentImageCount = 0;
	}
};

