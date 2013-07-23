#include "BattleScene.h"
#include "MainMenuScene.h"

using namespace cocos2d;
Player *  Vehicle::player;

CCScene* Battle::scene() {
    CCScene * scene = NULL;
    do {
        scene = CCScene::create();
        Battle *layer = Battle::create();
        scene->addChild(layer);
    } while (0);
    return scene;
}

bool Battle::init() {
    bool bRet = false;
    do {
		size = CCDirector::sharedDirector()->getWinSize();
		keyLeftFlag = false;
		keyRightFlag = false;

		// add Player
		player = new Player(5, 0, size.height/2);
		this->addChild(player, 1);

		// add Vehicle
		Vehicle::initPlayer(player);
		vehicle = new Vehicle(size.width * 1.5, size.height * 0.75);
		this->addChild(vehicle, 1);

		// Close Menu
		CCMenuItemImage *mainMenuItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(Battle::goMainMenu));
		mainMenuItem->setPosition(ccp(size.width - 20, 20));

		CCMenu* menu = CCMenu::create(mainMenuItem, NULL);
		menu->setPosition(CCPointZero);
        addChild(menu, 3);

		// Backgraund
		CCSprite* backSprite = CCSprite::create("back.png");
		backSprite->setPosition(ccp(size.width/2, size.height/2));
		addChild(backSprite, 0);

		// move background
		background = CCSprite::create("moveBack.png");
		ccTexParams params = {GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
		background->getTexture()->setTexParameters(&params);
		background->setPosition( ccp(background->getContentSize().width/2,background->getContentSize().height/2) );
		addChild(background);

		schedule( schedule_selector(Battle::gameLogic), 0.0 );

		CCDirector::sharedDirector()->getKeyboardDispatcher()->addDelegate(this);
		setTouchEnabled(true);

        bRet = true;
    } while (0);

    return bRet;
}

void Battle::goMainMenu(CCObject* pSender) {
    CCScene *mainMenuScene = MainMenu::scene();
	CCDirector::sharedDirector()->replaceScene(mainMenuScene);
}

void Battle::gameLogic(float dt) {
	// move player
	player->update();
	player->display();

	// move vehicle
	vehicle->seek();
	vehicle->update();
	vehicle->display();

	// move background
	float realLocationX = player->getRealLocationX();
	float realVelocityX = player->getRealVelocityX();
	CCRect rect = background->getTextureRect();
	if(realLocationX > size.width/2 && realLocationX < (2048 - size.width/2)) {
		if(rect.origin.x > 4096) {
			background->setTextureRect(CCRectMake(0, rect.origin.y, rect.size.width, rect.size.height));
		} else {
			background->setTextureRect(CCRectMake(rect.origin.x + realVelocityX, rect.origin.y, rect.size.width, rect.size.height));
		}
	}

	// game over
	if(player->isDead()) {
		CCSprite *gameOver = CCSprite::create("gameover.png");
		gameOver->setPosition( ccp(size.width/2, size.height/2) );
		addChild(gameOver, 2);
		CCDirector::sharedDirector()->getKeyboardDispatcher()->removeDelegate(this);
		player->pauseSchedulerAndActions();
		pauseSchedulerAndActions();
	}
}

void Battle::keyUp(int keyCode) {
	unschedule( schedule_selector(Battle::rotatePlayerLeft));
	unschedule( schedule_selector(Battle::rotatePlayerRight));
	keyLeftFlag = false;
	keyRightFlag = false;
	if(keyCode == 27)
	{// exit with Esc
	    CCScene *pHelloScene = MainMenu::scene();
		CCDirector::sharedDirector()->replaceScene(pHelloScene);
	}
}

void Battle::keyDown(int keyCode) {
	if( (keyCode == LEFT_KEY || keyCode == UP_KEY || keyCode == W_KEY || keyCode == A_KEY) && !keyLeftFlag)
	{// up key
		keyLeftFlag = true;
		keyRightFlag = false;
		schedule( schedule_selector(Battle::rotatePlayerLeft), 0.0 );
		unschedule( schedule_selector(Battle::rotatePlayerRight));
	}
	else if( (keyCode == RIGHT_KEY || keyCode == DOWN_KEY || keyCode == D_KEY || keyCode == S_KEY) && !keyRightFlag)
	{// down key
		keyRightFlag = true;
		keyLeftFlag = false;
		schedule( schedule_selector(Battle::rotatePlayerRight), 0.0 );
		unschedule( schedule_selector(Battle::rotatePlayerLeft));
	}
}

void Battle::rotatePlayerLeft(float dt) {
	player->turn(0.05);
}

void Battle::rotatePlayerRight(float dt) {
	player->turn(-0.05);
}

//void Battle::fireSomeBullets(float dt) {
//	Bullet *bullet = Bullet::create();
//	addChild(bullet);
//}

//void Battle::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event) {
//	this->schedule( schedule_selector(Battle::fireSomeBullets), 0.2 );
//}
//
//void Battle::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event) {
//	this->unschedule( schedule_selector(Battle::fireSomeBullets) );
//}
