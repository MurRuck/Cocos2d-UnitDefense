#pragma once
#include "cocos2d.h"

USING_NS_CC;
class Store : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	// implement the "static create()" method manually
	CREATE_FUNC(Store);
	Sprite* store;
	Sprite* sul;

	MenuItemImage* item[1];



	Label * itemnumber;
	Label * itemnumbers;

	void buy(Ref* pSender);
	void atore(Ref* pSender);
	void back(Ref* pSender);
};