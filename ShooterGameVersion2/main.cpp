#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include "Controls.h"
#include "Collision.h"
#include "GameObject.h"
#include "Bullet.h"
#include <iostream>
#include "Draw.h"
#include "PhysicsWorld.h"
#include "Camera.h"
#include "Player.h"
#include "Utils.h"
#include <cmath>
//TODO LIST UPDATED:
// 
// Major refactoring. Split everything into classes properly.
// Add a crosshair 
// Add a UI bar.
// Create player HP.
// Add an enemy
// Add a score system for eveyr enemy killed.
// Create player class.
// Code cleaning --- remove unnecessary comments.
// 
// Dunno after that. Gun mechanics, scoring, enemies. Try to keep code clean when adding these.
// 

/// <summary>
/// Creates a wall at a given location. Must be called by the IntializeWorld() function.
/// </summary>
/// <returns></returns>
GameObject CreateWall(sf::Vector2f position, sf::Vector2f size) {
    GameObject wall(Box2D(position, size), "Floor", 1, Physics2D(sf::Vector2f(0, 0), false));
    return wall;
}
/// <summary>
/// Initializes default locations of all gameobjects except for the players.
/// Intialize the world, then add the players to it.
/// </summary>
/// <returns>The current level.</returns>
std::vector<GameObject> InitializeWorld() {
    std::vector<GameObject> world;
    world.reserve(1000);
    world.push_back(CreateWall(sf::Vector2f(0, 720), sf::Vector2f(720, 50)));
    world.push_back(CreateWall(sf::Vector2f(0, 0), sf::Vector2f(720, 50)));
    world.push_back(CreateWall(sf::Vector2f(100, 300), sf::Vector2f(200, 200)));
    return world;
}

/// <summary>
/// returns the degree to have one object look at another.
/// </summary>
/// <param name="looking"></param>
/// <param name="lookingAt"></param>
/// <param name="offset"></param>
/// <returns></returns>
float LookAt(sf::Vector2f looking, sf::Vector2f lookingAt, float offset) {
    //sets rotation towards another object.
    sf::Vector2f a = looking;
    sf::Vector2f b = lookingAt;

    float xDiff = b.x - a.x;
    float yDiff = b.y - a.y;

    //caluclate angle in radians.
    float radianAngle = atan2f(yDiff, xDiff);

    float angleDegrees = radianAngle * 180 / M_PI;

    angleDegrees + offset;

    return angleDegrees;
}



int main()
{
    Player player = Player(sf::Vector2f(50,50));
    bool close = false;
    std::string crosshair = "images/crosshair.png";
    std::string ak47 = "images/weapons/ak47.png";

    std::string bullet = "images/bullets/bullet-basic.png";
    sf::Texture bulletText;
    
    sf::Texture crosshairText;
    sf::Texture ak47Text;
    sf::Mouse mouse;

    if (crosshairText.loadFromFile(crosshair)) {
        std::cout << "Crosshair loaded successfully." << std::endl;
    }
    else {
        std::cout << "Crosshair not loaded!!" << std::endl;
    }
    if (ak47Text.loadFromFile(ak47)) {
        std::cout << "Weapon loaded successfully." << std::endl;
    }
    else {
        std::cout << "Weapon not loaded!!" << std::endl;
    }

    
    crosshairText.setSmooth(true);
    ak47Text.setSmooth(true);

    //all gameobjects get pushed into gameObjectStorage, where they are stored.
    //Gameobjects are then sent out as references to the gameobjects vector which is used by every function.
    // Can't sort gameObjectStorage.  Can't delete new objects unless a new vector is used for temp objects.
    std::vector<GameObject> gameObjectStorage;
    gameObjectStorage = InitializeWorld();
    std::vector<GameObject> entityObjectStorage;
    std::vector<GameObject*> gameObjects;
    for (int x = 0; x < gameObjectStorage.size(); x++) {
        gameObjects.push_back(&gameObjectStorage[x]);
    }
    GameObject crosshairObj(Box2D(sf::Vector2f(100, 100), sf::Vector2f(50, 50)), "crosshair", 3);
    crosshairObj.animation = Animation(crosshairText,1);
    crosshairObj.physics.enabled = false;
    crosshairObj.physics.collisionsEnabled = false;
    crosshairObj.debugDraw = false;
    crosshairObj.type = "ui";
    GameObject weaponObj(Box2D(sf::Vector2f(200, 100), sf::Vector2f(100, 50)), "ak47", 3);
    weaponObj.animation = Animation(ak47Text, 1);
    weaponObj.physics.enabled = false;
    weaponObj.physics.collisionsEnabled = false;
    weaponObj.debugDraw = false;

    gameObjects.push_back(&player);
    gameObjects.push_back(&crosshairObj);
    gameObjects.push_back(&weaponObj);
    //Sorting all objects. 
    int gameObjectsSize = gameObjects.size();
    gameObjects = Draw::SortByLayer(gameObjects);

    //Other game settings
    PhysicsWorld world;
   

    //Controls
    Controls p1Controls;

    //Window and framerate settings
    sf::RenderWindow window(sf::VideoMode(1200,800), "");
    Camera cam(player.box2d.position);
    crosshairObj.box2d.position = player.box2d.position;
    window.requestFocus();
    window.setMouseCursorVisible(false);
    bool focus = window.hasFocus();
    float framerate = 60;//60 fps.
    float convertedFramerate = (1 / framerate) * 1000;
	sf::Clock clock;
	while (!close) {
		while (window.isOpen())
		{
            while (focus) {
                sf::Vector2f mousePos = (sf::Vector2f)mouse.getPosition(window);
                //Any camera movement needs to apply to the crosshair position.
                crosshairObj.box2d.position = mousePos;
                focus = window.hasFocus();
                //set ak47 to look at crosshair.
                weaponObj.box2d.position = player.box2d.position;
                weaponObj.box2d.rotation = LookAt(weaponObj.box2d.position, crosshairObj.box2d.position + cam.GetPos(), 0); // since crosshair is a ui object, add camera position to convert to worldspace
                //if a new gameobject is added, all layers will be resorted.
                //remove entities from gameObjects.
                //Add entities to gameObjects.

				if (clock.getElapsedTime().asMilliseconds() > convertedFramerate) {
                    if (mouse.isButtonPressed(sf::Mouse::Button::Left)) {
                        std::vector<GameObject*> currentRef;
                        for (int i = 0; i < entityObjectStorage.size(); i++) {
                            currentRef.push_back(&entityObjectStorage[i]);
                        }
                        
                        entityObjectStorage.push_back(player.Fire(weaponObj, crosshairObj.box2d.position + cam.GetPos()));
                        //remove all previous references for entities from gameObjects list.
                        for (int i = 0; i < currentRef.size(); i++) {
                            for (int x = 0; x < gameObjects.size(); x++) {
                                if (currentRef[i] == gameObjects[x]) {
                                    gameObjects.erase(gameObjects.begin() + x);
                                }
                            }
                        }
                        for (int i = 0; i < entityObjectStorage.size(); i++) {
                            gameObjects.push_back(&entityObjectStorage[i]);
                        }
                        //gameObjects.push_back(&entityObjectStorage.back());
                    }
                    //remove all objects found in entityObjectStorage from gameObjects DUE TO the vector changing position in memory when adding a new object.
                    player.onGround = Utils::OnGround(player, gameObjects);
                    p1Controls.Refresh();
                    player.PlayerMovement(p1Controls);
					gameObjects = world.Update(gameObjects);
					//sets camera position to center of the window.

					cam.SetPos(player.box2d.position - sf::Vector2f((window.getSize().x) / 2 - player.box2d.size.x / 2, (window.getSize().y) / 2 - player.box2d.size.y / 2));
                    gameObjects = Draw::SortByLayer(gameObjects);
					Draw::DrawObjects(window, gameObjects, cam);


                    clock.restart();
				}
            }
            focus = window.hasFocus();
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    close = true;
                    window.close();
                }
            }
		}

    }

    return 0;

}
