#pragma once
#include "cocos2d.h"

USING_NS_CC;
class MapChoice : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	/*int StageMapMove = 0;
	int StageMove = 0;*/
	virtual bool init();
	/*bool StageMapLeftMove = true;
	bool StageMapRightMove = true;
	bool StageLeftMove = true;
	bool StageRightMove = true;*/

	Vec2 firstmousepos;

	bool touchpos = true;
	//Vec2 firstmousespos;


	MenuItemImage* stage1;
	MenuItemImage* stage2;
	MenuItemImage* stage3;
	MenuItemImage* stage4;
	MenuItemImage* stage5;
	//MenuItemImage* stage1Button;
	//MenuItemImage* stage2Button;
	//MenuItemImage* stage3Button;
	//MenuItemImage* stage4Button;
	//MenuItemImage* stage5Button;
	MenuItemImage* stageleft;
	MenuItemImage* stagelight;
	MenuItemImage* mapstagelight;
	MenuItemImage* mapstageleft;
	MenuItemImage* stagemap1;
	MenuItemImage* stagemap2;
	MenuItemImage* stagemap3;
	MenuItemImage* stagemap4;
	MenuItemImage* stagemap5;
	MenuItemImage* stagemap6;

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);
	virtual void onTouchEnded(Touch* touch, Event* unused_event);

	/*void stagelightButton(Ref* pSender);
	void stageleftButton(Ref* pSender);
	void mapstagelightButton(Ref* pSender);
	void mapstageleftButton(Ref* pSender);*/
	void Back(Ref* pSender);
	void menu(Ref* pSender);
	void menu1(Ref* pSender);
	int n;
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MapChoice);
};