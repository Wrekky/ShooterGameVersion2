
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
// Add friction/a speed limit on x movement.
// Add jumping animation
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
        if (Collision::AABB(box,objects[i]->box2d)) {
            return true;
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
    //Texture setup. Think about breaking this up into methods.
    std::string playerJump = "animations/playerWalk/playerJumpSheet.png";
    std::string playerWalk = "animations/playerWalk/playerWalkSheet.png";
    sf::Texture playerWalkImage;
   
    if (playerWalkImage.loadFromFile(playerWalk)) {
        std::cout << "player walk image loaded" << std::endl;
    }
    else {
        std::cout << "player walk image not loaded" << std::endl;
    }
    if (playerWalkImage.loadFromFile(playerJump)) {
        std::cout << "player jump image loaded" << std::endl;
    }
    else {
        std::cout << "player jump image not loaded" << std::endl;
    }
    playerWalkImage.setSmooth(true);



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

    //////Player Objects
    GameObject player(Box2D(sf::Vector2f(100, 100), sf::Vector2f(50, 100)), "Player", 2, Physics2D(sf::Vector2f(50 + 5, 100 + 5)));
    player.animation = Animation(playerWalkImage, 4);
    player.animation.framerate = 60;
    player.debugDraw = false;
    gameObjects.push_back(&player);
    
    //Sorting all objects. 
    int gameObjectsSize = gameObjects.size();
    gameObjects = Draw::SortByLayer(gameObjects);

    //Other game settings
    PhysicsWorld world;
    Camera cam(sf::Vector2f(0, 0));

    //Controls
    Controls p1Controls;

    //Window and framerate settings
    sf::RenderWindow window(sf::VideoMode(800, 400), "");
    float framerate = 60;//60 fps.
    float convertedFramerate = (1 / framerate) * 1000;//bad but fine...
    sf::Clock clock;
    while (window.isOpen())
    {
        //if a new gameobject is added, all layers should be resorted... (Pretty big perf cost if a lot of objects are being added at once. Maybe change)
        if (gameObjectsSize > gameObjects.size()) {
            gameObjectsSize = gameObjects.size();
            gameObjects = Draw::SortByLayer(gameObjects);
        }
        else {
            //
            if (clock.getElapsedTime().asMilliseconds() > convertedFramerate) {
                player.onGround = OnGround(player, gameObjects);
                clock.restart();
                PlayerMovement(player, p1Controls);
                gameObjects = world.Update(gameObjects);
                cam.SetPos(player.box2d.position + sf::Vector2f(-350, -200));
                Draw::DrawObjects(window, gameObjects, cam);
            }
        }
    }

    return 0;

}
