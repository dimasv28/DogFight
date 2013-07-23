#ifndef __VEHICLE__
#define __VEHICLE__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "PVector.h"
#include "Player.h"

using namespace cocos2d;
class Player;




class Vehicle : public CCLayer {
protected:
	static Player *player;
	PVector *location;
	PVector *velocity;
	PVector *acceleration;
	float maxforce;
	float maxspeed;
	float angle;

	CCSprite *vehicleSprite;
	CCSize size;

public:
	Vehicle(float x , float y);
	static void initPlayer(Player *player_) { player = player_; }
	void update();
	void display();
	void seek();
	void applyForce(PVector *force);

	bool start;

	PVector *getLocation() { return location; };

	bool isDead();
};

#endif