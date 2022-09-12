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
	bool singleFrame = false;
	/// <summary>
	/// 
	/// </summary>
	/// <param name="spriteSheet">Spritesheet must be one line.</param>
	/// <param name="count">Total count of the images in the sprite sheet.</param>
	Animation(sf::Texture spriteSheet,int count) {
		this->currentImage = spriteSheet;
		this->count = count-1;
		spriteSize = sf::Vector2u(spriteSheet.getSize().x/count, spriteSheet.getSize().y);
	}
	Animation() {

	}
	/// <summary>
	/// Iterates the animation forward 1 frame.
	/// </summary>
	void Animate();
	/// <summary>
	/// Resets the animation.
	/// </summary>
	void Reset();

};

