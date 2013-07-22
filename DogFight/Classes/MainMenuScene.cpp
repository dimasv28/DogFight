#include "MainMenuScene.h"

using namespace cocos2d;

CCScene* MainMenu::scene() {
    CCScene * scene = NULL;
    do {
        scene = CCScene::create();
        MainMenu *layer = MainMenu::create();
        scene->addChild(layer);
    } while (0);
    return scene;
}

bool MainMenu::init() {
    bool bRet = false;
    do {
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CCLabelTTF* playLabel = CCLabelTTF::create("Play", "Arial", 20);

		CCMenuItemLabel *playItem = CCMenuItemLabel::create(playLabel,this,menu_selector(MainMenu::startDogFight));

		CCMenuItemImage *closeItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(MainMenu::menuCloseCallback));
		closeItem->setPosition(ccp(size.width - 20, 20));

		CCMenu* menu = CCMenu::create(playItem, closeItem, NULL);
        menu->setPosition(CCPointZero);
		playItem->setPosition(ccp(size.width / 2, size.height - 50));

		addChild(menu, 1);

        bRet = true;
    } while (0);

    return bRet;
}

void MainMenu::startDogFight(CCObject* pSender) {
	CCScene *pPlayScene = Battle::scene();
	CCDirector::sharedDirector()->replaceScene(pPlayScene);
}

void MainMenu::menuCloseCallback(CCObject* pSender) {
    CCDirector::sharedDirector()->end();
}