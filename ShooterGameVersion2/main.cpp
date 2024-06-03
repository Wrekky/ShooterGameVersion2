
#include <SFML/Graphics.hpp>
#include "Controls.h"
#include "Collision.h"
#include "GameObject.h"
#include <iostream>
#include "Draw.h"
#include "PhysicsWorld.h"
#include "Camera.h"
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
/// Checks if an object is on the ground or not.
/// </summary>
/// <param name="obj">The object to be checked.</param>
/// <param name="objects">All gameobjects.</param>
/// <returns>True if on ground.</returns>
bool OnGround(GameObject obj, std::vector<GameObject*> objects) {
    Box2D box;
    box = obj.box2d;
    box.position = sf::Vector2f(box.position.x + 1, box.position.y + box.size.y + 1);
    box.size = sf::Vector2f(box.size.x-2,2);
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->physics.collisionsEnabled) {
            if (Collision::AABB(box, objects[i]->box2d)) {
                return true;
            }
        }
    }
    return false;
}
/// <summary>
/// Jumping function for the player. Will be called by PlayerMovement()
/// </summary>
void PlayerJump(GameObject& player) {
    player.physics.velocity.y = -10;
}
/// <summary>
/// Handles player movement as well as player animations.
/// </summary>
void PlayerMovement(GameObject& player,Controls controls) {
    float xSpeedCap = 6.0f;
    float speed = 1.0f;
    float friction = 0.5f;
    if (!player.onGround) {
        friction = 0.1f;
        speed = 0.5f;
    }
    controls.Refresh();
    if (controls.left && player.physics.velocity.x > -xSpeedCap) {
        if (player.physics.velocity.x > 0 && player.animation.flipped != false) {
            player.animation.Reset();
        }
        player.physics.velocity.x -= speed;
        player.animation.flipped = false;
    }
    if (controls.right && player.physics.velocity.x < xSpeedCap) {
        if (player.physics.velocity.x < 0 && player.animation.flipped != true) {
            player.animation.Reset();
        }
        player.physics.velocity.x += speed;

        player.animation.flipped = true;

    }

    //psuedo friction for the player.
    if (!controls.right && !controls.left) {
        if(std::abs(player.physics.velocity.x) < 0.55f) {
            player.physics.velocity.x = 0;
        }
        else if (player.physics.velocity.x > 0) {
            player.physics.velocity.x -= friction;
        }
        else if (player.physics.velocity.x < 0) {
            player.physics.velocity.x += friction;
        }
    }
    if (controls.jump && player.onGround) {
        PlayerJump(player);
    }
    //If you hold space while jumping you should have a longer arc.
    if (controls.jump && player.physics.velocity.y < 0) {
        player.physics.gravityRatio = 0.3f;
    }
    else {
        player.physics.gravityRatio = 1.0f;
    }
    player.animation.framerate = std::abs((player.physics.velocity.x)) * 2;
}


int main()
{
    bool close = false;
    std::string crosshair = "images/crosshair.png";
    std::string ak47 = "images/weapons/ak47.png";
    std::string playerWalk = "animations/playerWalk/playerWalkSheet.png";
    sf::Texture playerWalkImage;
    sf::Texture crosshairText;
    sf::Texture ak47Text;
    sf::Mouse mouse;
    if (playerWalkImage.loadFromFile(playerWalk)) {
        std::cout << "player walk image loaded" << std::endl;
    }
    else {
        std::cout << "player walk image not loaded" << std::endl;
    }
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
    playerWalkImage.setSmooth(true);
    crosshairText.setSmooth(true);
    ak47Text.setSmooth(true);

    //all gameobjects get pushed into gameObjectStorage, where they are stored.
    //Gameobjects are then sent out as references to the gameobjects vector which is used by every function.
    // Can't sort gameObjectStorage.  Can't delete new objects unless a new vector is used for temp objects.
    std::vector<GameObject> gameObjectStorage;
    gameObjectStorage = InitializeWorld();
    std::vector<GameObject> tempObjectStorage;
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
    GameObject player(Box2D(sf::Vector2f(100, 100), sf::Vector2f(50, 100)), "Player", 2, Physics2D(sf::Vector2f(50 + 5, 100 + 5)));
    player.animation = Animation(playerWalkImage, 4);
    player.animation.framerate = 60;
    player.debugDraw = false;
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
                //if a new gameobject is added, all layers will be resorted.
                if (gameObjectsSize > gameObjects.size()) {
                    gameObjectsSize = gameObjects.size();
                    gameObjects = Draw::SortByLayer(gameObjects);
                }
                else {
                    if (clock.getElapsedTime().asMilliseconds() > convertedFramerate) {
                        sf::Vector2f prevPos = player.box2d.position;
                        player.onGround = OnGround(player, gameObjects);
                        clock.restart();
                        PlayerMovement(player, p1Controls);
                        gameObjects = world.Update(gameObjects);
                        //sets camera position to center of the window.
                        //get movement from camera and add it to the crosshair.
                        
                        cam.SetPos(player.box2d.position - sf::Vector2f((window.getSize().x) / 2 - player.box2d.size.x / 2, (window.getSize().y) / 2 - player.box2d.size.y / 2));

                        Draw::DrawObjects(window, gameObjects, cam);
                    }
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
