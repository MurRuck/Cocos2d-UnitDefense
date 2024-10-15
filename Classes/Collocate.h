#pragma once
#include "cocos2d.h"
#include "MainUnit.h"
#include "PoliceUnits.h"
#include "CitizenUnits.h"

USING_NS_CC;

class Collocate : public cocos2d::Layer
{
public:
	struct Unitsbar
	{
		Sprite* units;
		Sprite* check;
		bool unitsbar;
	};

	Sprite** units;
	Sprite** check;
	Unitsbar* unitsbar;
	Sprite* touched;

	Vec2 firstpos;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float dt);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	void savePos();

	// implement the "static create()" method manually
	CREATE_FUNC(Collocate);
};