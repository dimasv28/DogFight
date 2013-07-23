#ifndef __BATTLE__
#define __BATTLE__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "keyboard_dispatcher\CCKeyboardDispatcher.h"
#include "Player.h"
#include "Vehicle.h"

#define LEFT_KEY 37
#define RIGHT_KEY 39
#define UP_KEY 38
#define DOWN_KEY 40
#define A_KEY 65
#define D_KEY 68
#define W_KEY 87
#define S_KEY 83

using namespace cocos2d;

class Battle : public CCLayer, public CCKeyboardDelegate {
protected:
	Player *player;
	Vehicle *vehicle;
	CCSprite *background;
	CCSize size;
	bool keyLeftFlag;
	bool keyRightFlag;

	void gameLogic(float dt);
	//void fireSomeBullets(float dt);
	void rotatePlayerLeft(float dt);
	void rotatePlayerRight(float dt);

	void keyUp(int keyCode);
	void keyDown(int keyCode);

	//void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	//void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	
    void goMainMenu(CCObject* pSender);

public:
    virtual bool init(); 
    static CCScene* scene();

    CREATE_FUNC(Battle);
};

#endif