#include "Player.h"

Player::Player(float m, float x , float y) {
	size = CCDirector::sharedDirector()->getWinSize();

	location = new PVector(x, y);
    velocity = new PVector(0, 0);
	acceleration = new PVector(0, 0);
	globalVelocity = 2;
	realLocationX = 0;
	topspeed = 6;
	mass = m;
	angle = 0;

	playerSprite = CCSprite::create("player.png");
	playerSprite->setScale(mass/10);
	addChild(playerSprite);
}

void Player::update() {
	//velocity->add(acceleration);
	//velocity->limit(topspeed);

	velocity->x = globalVelocity * cos(angle);
	velocity->y = globalVelocity * sin(angle);
	realLocationX += velocity->x;

	// center of the screen
	if(realLocationX > size.width/2 && realLocationX < (2048 - size.width/2)) {
		velocity->x = 0;
	}

    location->add(velocity);
}

void Player::display() {
	playerSprite->setPosition(ccp(location->x, location->y));
	playerSprite->setRotation(-angle*180/M_PI);
}

void Player::turn(float a) {
	angle += a;
}

void Player::checkEdges() {
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if (location->x > size.width) {
		location->x = size.width;
		velocity->x *= -1;
	} else if (location->x < 0) {
		velocity->x *= -1;
		location->x = 0;
	}
	if (location->y > size.height) {
		velocity->y *= -1;
		location->y = size.height;
	} else if (location->y <= 0) {
		velocity->y *= -1;
		location->y = 0;
	}
}

void Player::applyForce(PVector *force) {
	PVector *f = PVector::div(force,mass);				// Newton's second law
	acceleration->add(f);
}

bool Player::isDead() {
	return location->y < 50 ? true : false;
}