#include "cocos2d.h"
#include "Map.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void AutoTurnOver(float db);

	// a selector callback

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
};

class TeamLogo : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);


	// implement the "static create()" method manually
	CREATE_FUNC(TeamLogo);
};