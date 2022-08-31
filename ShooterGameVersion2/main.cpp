
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
// Code cleaning --- Remove level editor.
// Code cleaning --- Remove 2nd player.
// Code cleaning --- Clean main area into the 3 functions. (Doing)
// Add jumping function.
// Add jumping animation
// Code cleaning --- remove unnecessary comments.
// 
// Dunno after that. Gun mechanics, scoring, enemies. Try to keep code clean when adding these.
// 
// If i want to change how i do things, make a gameworld object that you do GameObject.Add(GameObject(properties))
// 
// Fix level editor problems.
// Level editor problems: Creates multiple game objects sometimes. (i think)
// 
// ADD SPRITES
// ADD ANIMATION CLASS
// DO GAME


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
/// Jumping function for the player. Will be called by PlayerMovement()
/// </summary>
void PlayerJump(GameObject& player) {

}
/// <summary>
/// Handles player movement as well as player animations.
/// </summary>
void PlayerMovement(GameObject& player,Controls controls) {
    controls.Refresh();

    if (controls.left) {
        if (player.physics.velocity.x > 0 && player.animation.flipped != false) {
            player.animation.Reset();
        }
        player.physics.velocity.x -= 1;
        player.animation.flipped = false;
    }
    if (controls.right) {
        if (player.physics.velocity.x < 0 && player.animation.flipped != true) {
            player.animation.Reset();
        }
        player.physics.velocity.x += 1;

        player.animation.flipped = true;
    }
    if (controls.down) {

        player.physics.velocity.y += 1;
    }
    if (controls.up) {
        player.physics.velocity.y -= 1;
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
    //You cant sort gameObject storage so I cannot delete new objects unless a new vector is used for objects that will be deleted.
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
