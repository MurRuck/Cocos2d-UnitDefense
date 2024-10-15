#include "Collocate.h"
#include "InGame.h"
#include "UnitsAddress.h"
#include "SimpleAudioEngine.h"
#include "Control.h"

USING_NS_CC;

Scene* Collocate::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Collocate::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Collocate::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}


	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto mmenu = MenuItemImage::create("UI/button/button_n/start_n.png", "UI/button/button_c.png", CC_CALLBACK_1(Collocate::menuCloseCallback, this));
	mmenu->setAnchorPoint(Vec2(1.f, 1.f));
	mmenu->setPosition(Vec2(1280, 720));
	mmenu->setTag(1);

	auto menu = Menu::create(mmenu, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 100);


	Sprite* backgroundimage[3];

	backgroundimage[0] = Sprite::create("map/stage_1/bottom.png");
	backgroundimage[0]->setAnchorPoint(Vec2(0, 0));
	backgroundimage[0]->setPosition(Vec2::ZERO);
	this->addChild(backgroundimage[0]);


	backgroundimage[1] = Sprite::create("map/stage_1/top.png");
	backgroundimage[1]->setAnchorPoint(Vec2(0, 0));
	backgroundimage[1]->setPosition(Vec2(0, backgroundimage[0]->getContentSize().height));
	this->addChild(backgroundimage[1]);

	backgroundimage[2] = Sprite::create("test_bar.png");
	backgroundimage[2]->setAnchorPoint(Vec2(0, 0));
	backgroundimage[2]->setScaleY(0.6);
	backgroundimage[2]->setOpacity(220);
	backgroundimage[2]->setPosition(Vec2(0, 570));
	this->addChild(backgroundimage[2], 5);


	auto select = *SelectUnit::getInstance()->getUnitnum();

	unitsbar = new Unitsbar[select.maxunit];
	check = new Sprite*[select.maxunit];
	units = new Sprite*[select.maxunit];

	for (int i = 0;i < select.maxunit;i++)
	{
		if (select.botton > 0)
		{
			units[i] = Sprite::create("botton/stand/sprite_1.png");
			units[i]->setScale(1.1);
			check[i] = Sprite::create("check.png");
			check[i]->setScale(1.1);
			units[i]->setTag(1);
			select.botton -= 1;
		}
		else if (select.gunner > 0)
		{
			units[i] = Sprite::create("gunner/stand/sprite_1.png");
			units[i]->setScale(1.1);
			check[i] = Sprite::create("check.png");
			check[i]->setScale(1.1);
			units[i]->setTag(2);
			select.gunner -= 1;
		}
		else if (select.shield > 0)
		{
			units[i] = Sprite::create("shield/stand/sprite_1.png");
			units[i]->setScale(1.1);
			check[i] = Sprite::create("check.png");
			check[i]->setScale(1.1);
			units[i]->setTag(3);
			select.shield -= 1;
		}

		units[i]->setPosition(Vec2(60 * (i + 1), backgroundimage[2]->getPosition().y + 65));
		this->addChild(units[i], 10);

		check[i]->setPosition(Vec2(60 * (i + 1), backgroundimage[2]->getPosition().y + 65));
		this->addChild(check[i], 9);

		unitsbar[i].units = units[i];
		unitsbar[i].check = check[i];
		unitsbar[i].unitsbar = true;
	}

	this->scheduleUpdate();

	return true;
}

void Collocate::update(float dt)
{
	
}

void Collocate::menuCloseCallback(Ref* pSender)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
	switch (((Node*)pSender)->getTag())
	{
	case 1:

		for (int i = 0; i < SelectUnit::getInstance()->getUnitnum()->maxunit; i++)
		{
			if (unitsbar[i].units != nullptr)
				return;
		}

		savePos();
		Director::getInstance()->replaceScene(InGame::createScene());
		break;
	default:
		break;
	}
}

bool Collocate::onTouchBegan(Touch * touch, Event * unused_event)
{
	auto select = *SelectUnit::getInstance()->getUnitnum();

	for (int i = 0;i < select.maxunit;i++)
	{
		if (units[i]->getBoundingBox().containsPoint(touch->getLocation()))
		{
			touched = units[i];
			firstpos = touched->getPosition();
			break;
		}
	}
	return true;
}

void Collocate::onTouchMoved(Touch * touch, Event * unused_event)
{
	if(touched != nullptr)
		touched->setPosition(touch->getLocation());
}

void Collocate::onTouchEnded(Touch * touch, Event * unused_event)
{
	if (touched != nullptr)
	{
		auto pos = touched->getPosition();
		if (0 < pos.x && touched->getPosition().x < 1280)			//มฆวั
		{
			static int num = SelectUnit::getInstance()->getUnitnum()->maxunit;
			bool isfind = false;
			for (int i = 0;i < num;i++)
			{
				if (touched == unitsbar[i].units || isfind)
				{
					if (i == num - 1)
					{
						unitsbar[i].units = nullptr;
						unitsbar[i].check = nullptr;
						this->removeChild(check[i], true);
						unitsbar[i].unitsbar = false;
						num -= 1;
						continue;
					}

					if (!unitsbar[i].unitsbar)
						continue;

					if (unitsbar[i + 1].unitsbar)
					{
						unitsbar[i].units = unitsbar[i + 1].units;
						unitsbar[i].check = unitsbar[i + 1].check;
						unitsbar[i].unitsbar = unitsbar[i + 1].unitsbar;
					}

					unitsbar[i].units->runAction(MoveBy::create(0.5f, Vec2(-60, 0)));
					unitsbar[i].check->runAction(MoveBy::create(0.5f, Vec2(-60, 0)));

					isfind = true;
				}
			}
		}
		else
		{
			touched->setPosition(firstpos);
		}
	}

	touched = nullptr;
}

void Collocate::savePos()
{
	SelectUnit::getInstance()->vecCreate();

	int num[3] = { 0,0,0 };
	for (int i = 0;i < SelectUnit::getInstance()->getUnitnum()->maxunit;i++)
	{
		switch (units[i]->getTag())
		{
		case 1:
			SelectUnit::getInstance()->getUnitvec()->botton[num[0]] = units[i]->getPosition();
			num[0] += 1;
			break;
		case 2:
			SelectUnit::getInstance()->getUnitvec()->gunner[num[1]] = units[i]->getPosition();
			num[1] += 1;
			break;
		case 3:
			SelectUnit::getInstance()->getUnitvec()->shield[num[2]] = units[i]->getPosition();
			num[2] += 1;
			break;
		default:
			break;
		}
	}
}