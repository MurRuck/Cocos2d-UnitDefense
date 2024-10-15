#pragma once
#include "cocos2d.h"


enum
{
	SHIELD,
	BOTTON,
	GUNNER,
};

USING_NS_CC;
class UnitChoice : public cocos2d::Layer
{
public:
	Sprite* soldierchoice[4];
	Label* label[4];
	MenuItemImage* unitup[4];
	MenuItemImage* unitdown[4];
public:
	LayerColor* color;
	MenuItemImage* layerstick;
	MenuItemImage* layershield;
	MenuItemImage* layerrubber;
	MenuItemImage* layergas;
	MenuItemImage * store1;
	Sprite* moneys;

	Label* moneylabel;
	static cocos2d::Scene* createScene();
	virtual bool init();
	void Choice(Ref* pSender);
	void store(Ref* pSender);
	void back(Ref* pSender);
	void ChangeItem(Ref* pSender);
	void start(Ref* pSender);
	void UnitUp(Ref* pSender);
	void UnitDown(Ref* pSender);
	int nItemNum;

	int all = 10;
	int max = 0;
	int max1 = 0;
	int max2 = 0;
	int max3 = 0;

	// implement the "static create()" method manually
	CREATE_FUNC(UnitChoice);
};