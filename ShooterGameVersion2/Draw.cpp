#include "Draw.h"

std::vector<GameObject*> Draw::SortByLayer(std::vector<GameObject*> gameObjects) {
	std::vector<GameObject*> test = gameObjects;
	for (int x = 0; x < test.size(); x++) {
		int layer = test[x]->layer;
	}
	std::sort(test.begin(), test.end(),
		[](GameObject* struct1, GameObject* struct2)
		{
			return (struct1->layer < struct2->layer);
		}
	);
	return test;
}

void Draw::DrawObjects(sf::RenderWindow& window, std::vector<GameObject*> gameObjects,Camera cam) {
	window.clear();
	for (int x = 0; x < gameObjects.size(); x++) {
		if (gameObjects[x]->debugDraw) {
			//generating draw shape.
			sf::RectangleShape shape = sf::RectangleShape(gameObjects[x]->box2d.size);
			shape.setPosition(gameObjects[x]->box2d.position);
			if (gameObjects[x]->box2d.isColliding) {
				shape.setFillColor(sf::Color::Green);
			}
			shape.setPosition(shape.getPosition() - cam.GetPos());
			window.draw(shape);
		}
		else {
			int globalFrame = 60;
			int framerate = gameObjects[x]->animation.framerate;
			int current = gameObjects[x]->animation.currentFrame;
			///MESS maybe fix later...
			if (framerate != 0) {
				framerate = globalFrame / framerate;
			}
			
			
			//will change this so its set instead of having to be calculated.
			current += 1;
			gameObjects[x]->animation.currentFrame = current;
			//generating draw shape.
			sf::RectangleShape shape = sf::RectangleShape(gameObjects[x]->box2d.size);
			shape.setPosition(gameObjects[x]->box2d.position);
			shape.setTexture(&gameObjects[x]->animation.currentImage);
			if (gameObjects[x]->animation.flipped) {
				shape.setScale(-1.0, 1.0);
				shape.setPosition(shape.getPosition().x+shape.getSize().x,shape.getPosition().y);
			}
			else {
				shape.setScale(1.0, 1.0);
			}
			
			if (current > framerate) {
				gameObjects[x]->animation.Animate();
				if (framerate == 0) {
					gameObjects[x]->animation.Reset();
				}
				//change the objects texture.
				int textWidth, textHeight;
				sf::Vector2i textureSize = sf::Vector2i(gameObjects[x]->animation.spriteSize);
				int currentPos = gameObjects[x]->animation.currentImageCount * textureSize.x;
				sf::Vector2i texturePos = sf::Vector2i(currentPos, 0);
				gameObjects[x]->animation.texturePos=texturePos;
				gameObjects[x]->animation.textureSize=textureSize;
				
				shape.setTextureRect(sf::IntRect(texturePos, textureSize));
				
				gameObjects[x]->animation.currentFrame = 0;
			}
			else {

				shape.setTextureRect(sf::IntRect(gameObjects[x]->animation.texturePos, gameObjects[x]->animation.textureSize));
				gameObjects[x]->animation.currentFrame = current;
			}
			shape.setPosition(shape.getPosition() - cam.GetPos());
			window.draw(shape);
			//if animations are added i guess...
		}
	}
	window.display();
}