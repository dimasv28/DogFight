#ifndef __MAIN_MENU__
#define __MAIN_MENU__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "BattleScene.h"

using namespace cocos2d;

class MainMenu : public CCLayer {
protected:

public:
    virtual bool init(); 
    static CCScene* scene();

	void startDogFight(CCObject* pSender);
    void menuCloseCallback(CCObject* pSender);

    CREATE_FUNC(MainMenu);
};

#endif