#include "Player.h"
#include "Utils.h"
#include <iostream>

Player::Player(sf::Vector2f position) {
    std::string playerWalk = "animations/playerWalk/playerWalkSheet.png";
    sf::Texture playerWalkImage;
    playerWalkImage.loadFromFile(playerWalk);
    playerWalkImage.setSmooth(true);
    this->box2d = Box2D(position, sf::Vector2f(50, 100));
    this->type = "Player";
    this->layer = 2;
    this->physics = Physics2D(sf::Vector2f(50 + 5, 100 + 5));
    this->animation = Animation(playerWalkImage, 4);
    this->animation.framerate = 60;
    this->debugDraw = false;
}

void Player::PlayerJump() {
	physics.velocity.y = -10;
}

void Player::PlayerMovement(Controls controls) {
	float setSpeed = speed;
	float setFriction = friction;
	if (!onGround) {
		setFriction = friction/5;
		setSpeed = speed / 10;
	}
	controls.Refresh();//????? shouldn't do anything? reminder to call in gameloop instead.
    if (controls.left && physics.velocity.x > -speedCap) {
        if (physics.velocity.x > 0 && animation.flipped != false) {
            animation.Reset();
        }
        physics.velocity.x -= speed;
        animation.flipped = false;
    }
    if (controls.right && physics.velocity.x < speedCap) {
        if (physics.velocity.x < 0 && animation.flipped != true) {
            animation.Reset();
        }
        physics.velocity.x += speed;
        animation.flipped = true;
    }

    if (!controls.right && !controls.left) {
        if (std::abs(physics.velocity.x) < 0.55f) {
            physics.velocity.x = 0;
        }
        else if (physics.velocity.x > 0) {
            physics.velocity.x -= friction;
        }
        else if (physics.velocity.x < 0) {
            physics.velocity.x += friction;
        }
    }
    if (controls.jump && onGround) {
        PlayerJump();
    }

    //If you hold space while jumping you should have a longer arc.
    if (controls.jump && physics.velocity.y < 0) {
        physics.gravityRatio = 0.3f;
    }
    else {
        physics.gravityRatio = 1.0f;
    }
    animation.framerate = std::abs((physics.velocity.x)) * 2;
}


Bullet Fire (GameObject weapon, sf::Vector2f fireDirection) {

    if (weapon.type == "ak47") {
        std::string bulletString = "images/bullets/bullet-basic.png";
        sf::Texture bulletText;
        bulletText.loadFromFile(bulletString);
        bulletText.setSmooth(true);
        GameObject bulletGameObject(Box2D(weapon.box2d.position, sf::Vector2f(10, 10)), "bullet", 3);
        Bullet bullet;
        bullet.animation = Animation(bulletText, 1);
    }


    bullet.physics.enabled = true;
    bullet.physics.collisionsEnabled = false;
    bullet.physics.gravityRatio = 0;
    bullet.debugDraw = false;
    bullet.physics.velocity = fireDirection;
    bullet.physics.velocity = sf::Vector2f(bullet.physics.velocity.x * speed, bullet.physics.velocity.y * speed);
    return bullet;
}
