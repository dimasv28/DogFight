#include "Vehicle.h"

Vehicle::Vehicle(float x , float y) {
	size = CCDirector::sharedDirector()->getWinSize();

	location = new PVector(x, y);
    velocity = new PVector(0, 0);
	acceleration = new PVector(0, 0);

	maxspeed = 2;
	maxforce = 0.03;
	angle = 0;
	
	start = true;

	vehicleSprite = CCSprite::create("vehicle.png");
	vehicleSprite->setScale(0.5);
	addChild(vehicleSprite);
}

void Vehicle::update() {
	float realLocationX = player->getRealLocationX();
	float realVelocityX = player->getRealVelocityX();

	if(location->x < player->getLocation()->x) {
		start = false;
	}

	if(!start) {
		velocity->add(acceleration);
		velocity->limit(maxspeed);
		if(realLocationX > size.width/2 && realLocationX < (2048 - size.width/2)) {
				location->x -= realVelocityX;
		}
	} else {
		velocity->x = -2 - realVelocityX;
	}
	location->add(velocity);
	acceleration->mult(0);

	angle = velocity->heading();
}

void Vehicle::display() {
	vehicleSprite->setPosition(ccp(location->x, location->y));
	vehicleSprite->setRotation(180 - angle*180/M_PI);
}

void Vehicle::seek() {
	PVector *target = player->getLocation();
    PVector *desired = PVector::sub(target, location);
    desired->normalize();
    desired->mult(maxspeed);
    PVector *steer = PVector::sub(desired, velocity);
    steer->limit(maxforce);
    applyForce(steer);
  }

void Vehicle::applyForce(PVector *force) {
	acceleration->add(force);
}

bool Vehicle::isDead() {
	return location->y < 50 ? true : false;
}