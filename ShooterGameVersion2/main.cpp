
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
/// Handles player movement as well as flipping of animations.
/// </summary>
void PlayerMovement(GameObject& player) {

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
    std::vector<GameObject*> gameObjects;
    for (int x = 0; x < gameObjectStorage.size(); x++) {
        gameObjects.push_back(&gameObjectStorage[x]);
    }

    //////Player Objects
    GameObject player(Box2D(sf::Vector2f(100, 100), sf::Vector2f(50, 100)), "Player", 2, Physics2D(sf::Vector2f(50 + 5, 100 + 5)));
    player.animation = Animation(playerWalkImage, 4);
    player.animation.framerate = 12;
    player.debugDraw = false;
    gameObjects.push_back(&player);
    GameObject player2(Box2D(sf::Vector2f(500, 500), sf::Vector2f(10, 10)), "Player2", 2, Physics2D(sf::Vector2f(50 + 5, 100 + 5)));
    gameObjects.push_back(&player2);
    
    //Sorting all objects. 
    int gameObjectsSize = gameObjects.size();
    gameObjects = Draw::SortByLayer(gameObjects);

    //Other game settings
    PhysicsWorld world;
    Camera cam(sf::Vector2f(0, 0));

    //Controls
    Controls p1Controls;
    Controls p2Controls(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Space);

    //Window and framerate settings
    sf::RenderWindow window(sf::VideoMode(800, 400), "");
    float framerate = 60;//60 fps.
    float convertedFramerate = (1 / framerate) * 1000;//bad but fine...
    sf::Clock clock;
    
    //Old edit mode stuff. Remove this.
    sf::Vector2f topLeft = sf::Vector2f(-300,-300);
    sf::Vector2f bottomRight = sf::Vector2f(-300, -300);
    bool editMode = false;
    
    while (window.isOpen())
    {
        if (gameObjectsSize > gameObjects.size()) {
            gameObjectsSize = gameObjects.size();
            //Re-sort objects if any change in layers occurs.
            gameObjects = Draw::SortByLayer(gameObjects);
        }
        if (editMode) {///////////////////////////////////////////////// LEVEL EDITOR MODE: needed to run: mouse position, gameobjects... yeah just gonna leave it here
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
                editMode = false;
                topLeft = sf::Vector2f(-300, -300);
                bottomRight = sf::Vector2f(-300, -300);
            }
            //get mouse position.
            sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
            //When mouse clicks once set to boxes top left corner.
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && (topLeft == sf::Vector2f(-300, -300))) {
                topLeft = mousePos;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)&& (bottomRight == sf::Vector2f(-300, -300))) {
                bottomRight = mousePos;
            }
            if ((topLeft != sf::Vector2f(-300, -300) && bottomRight != sf::Vector2f(-300, -300))) {
                //Check which is top left vs bottom right.
                float height;
                if (topLeft.y > bottomRight.y) {
                    height = topLeft.y - bottomRight.y;
                }
                else {
                    height = bottomRight.y - topLeft.y;
                }

                float width;
                if (topLeft.x > bottomRight.x) {
                    width = topLeft.x - bottomRight.x;
                }
                else {
                    width = bottomRight.x - topLeft.x;
                }
                sf::Vector2f pos;
                if (topLeft.x < bottomRight.x) {
                    if (topLeft.y < bottomRight.y) {
                        pos = topLeft;
                    }
                    else {
                        pos = sf::Vector2f(topLeft.x, bottomRight.y);
                    }
                }
                else {
                    if (topLeft.y < bottomRight.y) {
                        pos = sf::Vector2f(bottomRight.x, topLeft.y);
                    }
                    else {
                        pos = bottomRight;
                    }
                }
                //have width, height and pos.
                Box2D box(pos, sf::Vector2f(width, height));
                GameObject platform(box, "platform", 1, Physics2D(sf::Vector2f(0 + window.getSize().x / 2, (window.getSize().y - 50) + 25), false));
                gameObjectStorage.push_back(platform);
                gameObjects.push_back(&gameObjectStorage.back());
                topLeft = sf::Vector2f(-300, -300);
                bottomRight = sf::Vector2f(-300, -300);
            }
        }
        else {
            if (clock.getElapsedTime().asMilliseconds() > convertedFramerate) {
                clock.restart();
                p1Controls.Refresh();
                
                if (p1Controls.left) {
                    if (player.physics.velocity.x > 0 && player.animation.flipped != false) {
                        player.animation.Reset();
                    }
                    player.physics.velocity.x -= 1;
                    player.animation.flipped = false;
                }
                if (p1Controls.right) {
                    if (player.physics.velocity.x < 0 && player.animation.flipped != true) {
                        player.animation.Reset();
                    }
                    player.physics.velocity.x += 1;
                    
                    player.animation.flipped = true;
                }
                if (p1Controls.down) {

                    player.physics.velocity.y += 1;
                }
                if (p1Controls.up) {
                    player.physics.velocity.y -= 1;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
                    editMode = true;
                }
                player.animation.framerate = std::abs((player.physics.velocity.x))*2;
                
               
                p2Controls.Refresh();
                if (p2Controls.left) {
                    player2.physics.velocity.x -= 1;
                }
                if (p2Controls.right) {
                    player2.physics.velocity.x += 1;
                }
                if (p2Controls.down) {

                    player2.physics.velocity.y += 1;
                }
                if (p2Controls.up) {
                    player2.physics.velocity.y -= 1;
                }
                //after all movements are updated do a check for collisions.
                //Run physics.

                //if (Collision::AABB(player.box2d, floor.box2d)) {
                //    player.box2d.isColliding = true;
                //}
                //else {
                //    player.box2d.isColliding = false;
                //}

                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }
                gameObjects = world.Update(gameObjects);
                //graphics
               // draw.Draw();
                cam.SetPos(player.box2d.position + sf::Vector2f(-350,-200));
                Draw::DrawObjects(window, gameObjects,cam);
                
            }
        }


    }

    return 0;

}
