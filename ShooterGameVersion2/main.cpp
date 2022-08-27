
#include <SFML/Graphics.hpp>
#include "Controls.h"
#include "Collision.h"
#include "GameObject.h"
#include <iostream>
#include "Draw.h"
#include "PhysicsWorld.h"
#include "Camera.h"
//TODO LIST UPDATED:::
// 
// Make running animation based on velocity.
// Animation resets when velocity is equal to zero.
// Jumping
// Jumping animationdfwawedsAESAS
// 
// 
// If i want to change how i do things, make a gameworld object that you do GameObject.Add(GameObject(properties))
// 
// 
// Fix level editor problems.
// Level editor problems: Creates multiple game objects sometimes. (i think)
// 
// 
// ADD SPRITES
// ADD ANIMATION CLASS
// DO GAME
//
//file structure is all lowercase.
// 
//Todo list:
// +SORT DRAW VECTOR BY GAMEOBJECTS LAYER ATTRIBUTE. Either do my own sort function or use someone elses. DONE
//Physics -> Make 2 gameobjects, a floor and a player. Fix if i did something wrong. DONE
// Add physics -> Physics2D class. DONE
// Collisions on physics will be ran for every single pixel run. DONE
// Either reset velocity to zero OR reverse velocity for the side of the wall you hit and -90% of its value. DONE kinda
// 
// You press e, it brings up a grid 
// 
// 
// Static sprites comments and seperate functions into the cpp files instead of having them all be in .h files. (never gonna be done)
// 
// Player mechanics.
// Animation -> Just make a running animation.
// Attatch running animation to players movement. Try to base it on current players speed. do mario stuff.
// enemies
// weapon system
// enemies
//Score system
//Its just gonna be a game that spawns flying enemies while you fight on a singular screen OR a kind of wide screen. dunno yet.
int main()
{
    std::string playerJump = "animations/playerWalk/playerJumpSheet.png";
    std::string playerWalk = "animations/playerWalk/playerWalkSheet.png";
    //Animation playerWalk;
    //Animation playerIdle;
    //Animation playerJump;

    //grabbing image.
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
    std::vector<GameObject> gameObjectStorage;
    //Reserving gameobject storage space.
    gameObjectStorage.reserve(1000);
    std::vector<GameObject*> gameObjects;//should be sorted by gameobjects int property every now and then. this should also be a pointer now...
    sf::RenderWindow window(sf::VideoMode(800, 400), "");
    Controls p1Controls;
    Controls p2Controls(sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Space);
    
    float framerate = 60;//60 fps.
    float convertedFramerate = (1 / framerate) * 1000;//bad but fine...
    sf::Clock clock;
    
    //////GAME OBJECTS
    GameObject player(Box2D(sf::Vector2f(100, 100), sf::Vector2f(50, 100)),"Player",2,Physics2D(sf::Vector2f(50 + 5,100 + 5)));//id like to have gameObjects be a const or something I dont have to define in the class and can instead reference
    player.animation = Animation(playerWalkImage,4);
    player.animation.framerate = 12;
    player.debugDraw = false;
    
    GameObject player2(Box2D(sf::Vector2f(500, 500), sf::Vector2f(10, 10)), "Player2", 2, Physics2D(sf::Vector2f(50 + 5, 100 + 5)));//id like to have gameObjects be a const or something I dont have to define in the class and can instead reference
    GameObject floor(Box2D(sf::Vector2f(50, window.getSize().y-50), sf::Vector2f(window.getSize().x-100, 50)), "Floor",1,Physics2D(sf::Vector2f(0+window.getSize().x/2, (window.getSize().y-50)+25),false));
    GameObject roof(Box2D(sf::Vector2f(50, 0), sf::Vector2f(window.getSize().x - 100, 50)), "Floor", 1, Physics2D(sf::Vector2f(0 + window.getSize().x / 2, (window.getSize().y - 50) + 25), false));
    GameObject lWall(Box2D(sf::Vector2f(0, 0), sf::Vector2f(50, window.getSize().y)), "Floor", 1, Physics2D(sf::Vector2f(0 + window.getSize().x / 2, (window.getSize().y - 50) + 25), false));
    GameObject rWall(Box2D(sf::Vector2f(window.getSize().x-50, 0), sf::Vector2f(50, window.getSize().y)), "Floor", 1, Physics2D(sf::Vector2f(0 + window.getSize().x / 2, (window.getSize().y - 50) + 25), false));
    gameObjects.push_back(&player);
    gameObjects.push_back(&player2);
    gameObjects.push_back(&lWall);
    gameObjects.push_back(&rWall);
    gameObjects.push_back(&floor);
    gameObjects.push_back(&roof);

    //Why isnt this getting called?
    //how do i want to do drawing? --> every game object either has a reference to a layer vector OR a simple int? if its an int i'd have to iterate every time... 
    //When a game object gets created they get added to a public game object list. So in the constructor I wanna add a add to list function...
    int gameObjectsSize = gameObjects.size();
    gameObjects = Draw::SortByLayer(gameObjects);
    PhysicsWorld world;
    bool editMode = false;
    //box creation stuff.
    sf::Vector2f topLeft = sf::Vector2f(-300,-300);
    sf::Vector2f bottomRight = sf::Vector2f(-300, -300);

    Camera cam(sf::Vector2f(0, 0));
    
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