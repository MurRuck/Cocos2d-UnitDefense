#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

Scene* TeamLogo::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TeamLogo::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto Background = Sprite::create("background/white.png");
	Background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(Background, 0);

	auto TeamLogo = Sprite::create("background/TeamLogo.png");
	TeamLogo->setPosition(Vec2(640, 360));
	TeamLogo->setScale(0.6);
	TeamLogo->setOpacity(0);
	this->addChild(TeamLogo, 1);


	auto fadein = FadeIn::create(1.0);
	auto fadeout = FadeOut::create(0.5);
	auto seq = Sequence::create(fadein, fadeout, NULL);
	TeamLogo->runAction(seq);

	this->schedule(schedule_selector(HelloWorld::AutoTurnOver), 1.0);

	return true;
}


// on "init" you need to initialize your instance
bool TeamLogo::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite::create("background/HelloWorldScene.png");

	// position the sprite on the center of  the screen
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);


	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	return true;
}

bool TeamLogo::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto scene = TransitionFade::create(1.5, MapChoice::createScene());
	Director::getInstance()->replaceScene(scene);

	return true;
}


void HelloWorld::AutoTurnOver(float db)
{
	auto scene = TransitionFade::create(0.5, TeamLogo::createScene());
	Director::getInstance()->replaceScene(scene);

}
