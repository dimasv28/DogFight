#ifndef __PLAYER__
#define __PLAYER__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "PVector.h"

using namespace cocos2d;

class Player : public CCLayer {
protected:
	PVector *location;
	PVector *velocity;
	PVector *acceleration;
	float globalVelocity;
	float realLocationX;
	float topspeed;
	float mass;
	float angle;

	CCSprite *playerSprite;
	CCSize size;

public:
	Player(float m, float x , float y);
	void update();
	void display();
	void checkEdges();
	void applyForce(PVector *force);

	PVector *getLocation() { return location; };
	PVector *getVelocity() { return velocity; };
	float getMass() { return mass; };
	float getRealLocationX() { return realLocationX; };
	float getRealVelocityX() { return globalVelocity * cos(angle); };
	void setVelocity(PVector *v) { velocity->x = v->x; velocity->y = v->y; };
	void turn(float a);
	
	bool isDead();
};

#endif