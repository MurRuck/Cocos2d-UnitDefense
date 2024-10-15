#include "Map.h"
#include "UnitChoice.h"
#include "SimpleAudioEngine.h"
#include "Control.h"

USING_NS_CC;

Scene* MapChoice::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MapChoice::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MapChoice::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//////////////////////////////////////////////
	auto color = LayerColor::create(Color4B(0, 0, 0, 175));
	color->setPosition(Vec2::ZERO);
	this->addChild(color, -1);

	auto layer = LayerColor::create(Color4B(240, 240, 240, 70));
	layer->setPosition(Vec2::ZERO);
	this->addChild(layer, 1);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(MapChoice::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(MapChoice::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(MapChoice::onTouchEnded, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto background = Sprite::create("background/mapchoice.png");
	background->setAnchorPoint(Vec2(1, 1));
	background->setPosition(Vec2(1280, 720));
	background->setOpacity(115);
	this->addChild(background, 0);

	stage1 = MenuItemImage::create("UI/model/korea.png", "UI/model/korea.png", CC_CALLBACK_1(MapChoice::menu, this));//스테이지선택
	stage1->setAnchorPoint(Vec2(1, 1));
	stage1->setPosition(Vec2(730, 190));
	//stage1->setScale(0.65f);
	stage1->setTag(10);
	auto stage11 = Menu::create(stage1, NULL);
	stage11->setPosition(Vec2::ZERO);
	this->addChild(stage11, 1);

	stage2 = MenuItemImage::create("UI/model/brazil.png", "UI/model/brazil.png", CC_CALLBACK_1(MapChoice::menu, this));//스테이지선택
	stage2->setAnchorPoint(Vec2(1, 1));
	stage2->setPosition(Vec2(1210, 240));
	stage2->setScale(0.9f);
	stage2->setTag(20);
	auto stage22 = Menu::create(stage2, NULL);
	stage22->setPosition(Vec2::ZERO);
	this->addChild(stage22, 1);

	stage3 = MenuItemImage::create("UI/model/germany.png", "UI/model/germany.png", CC_CALLBACK_1(MapChoice::menu, this));//스테이지선택
	stage3->setAnchorPoint(Vec2(1, 1));
	stage3->setPosition(Vec2(1750, 240));
	stage3->setScale(0.9f);
	stage3->setTag(30);
	auto stage33 = Menu::create(stage3, NULL);
	stage33->setPosition(Vec2::ZERO);
	this->addChild(stage33, 1);

	stage4 = MenuItemImage::create("UI/model/united kingdom.png", "UI/model/united kingdom.png", CC_CALLBACK_1(MapChoice::menu, this));//스테이지선택
	stage4->setAnchorPoint(Vec2(1, 1));
	stage4->setPosition(Vec2(2175, 292));
	stage4->setScale(0.7f);
	stage4->setTag(40);
	auto stage44 = Menu::create(stage4, NULL);
	stage44->setPosition(Vec2::ZERO);
	this->addChild(stage44, 1);

	stage5 = MenuItemImage::create("UI/model/usa.png", "UI/model/usa.png", CC_CALLBACK_1(MapChoice::menu, this));//스테이지선택
	stage5->setAnchorPoint(Vec2(1, 1));
	stage5->setPosition(Vec2(2620, 285));
	stage5->setScale(0.82f);
	stage5->setTag(50);
	auto stage55 = Menu::create(stage5, NULL);
	stage55->setPosition(Vec2::ZERO);
	this->addChild(stage55, 1);

	stagemap1 = MenuItemImage::create("stage1.png", "stage1.png", CC_CALLBACK_1(MapChoice::menu1, this));//스테이지안에서 스테이지선택
	stagemap1->setAnchorPoint(Vec2(1, 1));
	stagemap1->setPosition(Vec2(770, 650));
	stagemap1->setScale(0.4);
	stagemap1->setTag(1);
	auto stagemap11 = Menu::create(stagemap1, NULL);
	stagemap11->setPosition(Vec2::ZERO);
	this->addChild(stagemap11, 1);

	stagemap2 = MenuItemImage::create("rockmap.png", "rockmap.png", CC_CALLBACK_1(MapChoice::menu1, this));//스테이지안에서 스테이지선택
	stagemap2->setAnchorPoint(Vec2(1, 1));
	stagemap2->setPosition(Vec2(1470, 650));
	stagemap2->setTag(2);
	stagemap2->setScale(0.4);
	stagemap2->setOpacity(150);
	auto stagemap22 = Menu::create(stagemap2, NULL);
	stagemap22->setPosition(Vec2::ZERO);
	this->addChild(stagemap22, 1);

	stagemap3 = MenuItemImage::create("rockmap.png", "rockmap.png", CC_CALLBACK_1(MapChoice::menu1, this));//스테이지안에서 스테이지선택
	stagemap3->setAnchorPoint(Vec2(1, 1));
	stagemap3->setPosition(Vec2(2170, 650));
	stagemap3->setTag(3);
	stagemap3->setScale(0.4);
	stagemap3->setOpacity(150);
	auto stagemap33 = Menu::create(stagemap3, NULL);
	stagemap33->setPosition(Vec2::ZERO);
	this->addChild(stagemap33, 1);

	stagemap4 = MenuItemImage::create("rockmap.png", "rockmap.png", CC_CALLBACK_1(MapChoice::menu1, this));//스테이지안에서 스테이지선택
	stagemap4->setAnchorPoint(Vec2(1, 1));
	stagemap4->setPosition(Vec2(2870, 650));
	stagemap4->setTag(4);
	stagemap4->setScale(0.4);
	stagemap4->setOpacity(150);
	auto stagemap44 = Menu::create(stagemap4, NULL);
	stagemap44->setPosition(Vec2::ZERO);
	this->addChild(stagemap44, 1);

	stagemap5 = MenuItemImage::create("rockmap.png", "rockmap.png", CC_CALLBACK_1(MapChoice::menu1, this));//스테이지안에서 스테이지선택
	stagemap5->setAnchorPoint(Vec2(1, 1));
	stagemap5->setPosition(Vec2(3570, 650));
	stagemap5->setTag(5);
	stagemap5->setScale(0.4);
	stagemap5->setOpacity(150);
	auto stagemap55 = Menu::create(stagemap5, NULL);
	stagemap55->setPosition(Vec2::ZERO);
	this->addChild(stagemap55, 1);

	stagemap6 = MenuItemImage::create("rockmap.png", "rockmap.png", CC_CALLBACK_1(MapChoice::menu1, this));//스테이지안에서 스테이지선택
	stagemap6->setAnchorPoint(Vec2(1, 1));
	stagemap6->setPosition(Vec2(4270, 650));
	stagemap6->setTag(6);
	stagemap6->setScale(0.4);
	stagemap6->setOpacity(150);
	auto stagemap66 = Menu::create(stagemap6, NULL);
	stagemap66->setPosition(Vec2::ZERO);
	this->addChild(stagemap66, 1);



	/*mapstageleft = MenuItemImage::create("UI/button/button_n/rightmove.png", "UI/button/button_c/rightmove1.png", CC_CALLBACK_1(MapChoice::mapstageleftButton, this));
	mapstageleft->setAnchorPoint(Vec2(1, 1));
	mapstageleft->setScale(0.5);
	mapstageleft->setPosition(Vec2(1100, 700));
	auto mapstageleft1 = Menu::create(mapstageleft, NULL);
	mapstageleft1->setPosition(Vec2::ZERO);
	this->addChild(mapstageleft1, 1);

	mapstagelight = MenuItemImage::create("UI/button/button_n/leftmove.png", "UI/button/button_c/leftmove1.png", CC_CALLBACK_1(MapChoice::mapstagelightButton, this));
	mapstagelight->setAnchorPoint(Vec2(1, 1));
	mapstagelight->setScale(0.5);
	mapstagelight->setPosition(Vec2(300, 700));
	auto mapstagelight1 = Menu::create(mapstagelight, NULL);
	mapstagelight1->setPosition(Vec2::ZERO);
	this->addChild(mapstagelight1, 1);

	stageleft = MenuItemImage::create("UI/button/button_n/rightmove.png", "UI/button/button_c/rightmove1.png", CC_CALLBACK_1(MapChoice::stageleftButton, this));
	stageleft->setAnchorPoint(Vec2(1, 1));
	stageleft->setScale(0.5);
	stageleft->setPosition(Vec2(1100, 300));
	auto stageleft1 = Menu::create(stageleft, NULL);
	stageleft1->setPosition(Vec2::ZERO);
	this->addChild(stageleft1, 1);

	stagelight = MenuItemImage::create("UI/button/button_n/leftmove.png", "UI/button/button_c/leftmove1.png", CC_CALLBACK_1(MapChoice::stagelightButton, this));
	stagelight->setAnchorPoint(Vec2(1, 1));
	stagelight->setScale(0.5);
	stagelight->setPosition(Vec2(300, 300));
	auto stagelight1 = Menu::create(stagelight, NULL);
	stagelight1->setPosition(Vec2::ZERO);
	this->addChild(stagelight1, 1);

	*/



	return true;
}

void MapChoice::Back(Ref* pSender)
{

}

void MapChoice::menu(Ref* pSender)
{
	MenuItemImage* unit[] = { stagemap1, stagemap2, stagemap3, stagemap4, stagemap5, stagemap6 };

	//if (((Node*)pSender)->getTag() == 10)
	//{
	//   for (int i = 0; i < 6; i++)
	//      //unit[i]->setDisabledImage("이미지경로");
	//}
	for (int i = 0; i<6; i++)
	{
		unit[i]->runAction(Place::create(Vec2(770 + (700 * i), 650)));
		unit[i]->setTag(i + (((Node*)pSender)->getTag() * 10));
	}/*
	 StageMapMove = 0;*/
}

void MapChoice::menu1(Ref* pSender)
{
	switch (int(((MenuItemImage*)pSender)->getTag() / 100))
	{


	case 1:
		n = ((MenuItemImage*)pSender)->getTag() % 100;
		SelectUnit::getInstance()->getStageMap()->stage = 1;
		SelectUnit::getInstance()->getStageMap()->map = n;
		{
			if (n == 0)
			{
				auto scene = TransitionFade::create(2.0, UnitChoice::createScene());
				Director::getInstance()->replaceScene(scene);
			}
		}
		break;
	case 2:
		n = ((MenuItemImage*)pSender)->getTag() % 100;
		SelectUnit::getInstance()->getStageMap()->stage = 2;
		SelectUnit::getInstance()->getStageMap()->map = n;
		{
			/*auto scene = TransitionFade::create(2.0, UnitChoice::createScene());
			Director::getInstance()->replaceScene(scene);*/
		}
		break;
	case 3:
		n = ((MenuItemImage*)pSender)->getTag() % 100;
		SelectUnit::getInstance()->getStageMap()->stage = 3;
		SelectUnit::getInstance()->getStageMap()->map = n;
		{
			/*auto scene = TransitionFade::create(2.0, UnitChoice::createScene());
			Director::getInstance()->replaceScene(scene);*/
		}
		break;
	case 4:
		n = ((MenuItemImage*)pSender)->getTag() % 100;
		SelectUnit::getInstance()->getStageMap()->stage = 4;
		SelectUnit::getInstance()->getStageMap()->map = n;
		{
			/*auto scene = TransitionFade::create(2.0, UnitChoice::createScene());
			Director::getInstance()->replaceScene(scene);*/
		}
		break;
	case 5:
		n = ((MenuItemImage*)pSender)->getTag() % 100;
		SelectUnit::getInstance()->getStageMap()->stage = 5;
		SelectUnit::getInstance()->getStageMap()->map = n;
		{
			/*auto scene = TransitionFade::create(2.0, UnitChoice::createScene());
			Director::getInstance()->replaceScene(scene);*/
		}
		break;

	}

	if (n == 0)
	{
		auto scene = TransitionFade::create(2.0, UnitChoice::createScene());
		Director::getInstance()->replaceScene(scene);
	}

}
//break;


bool MapChoice::onTouchBegan(Touch* touch, Event* unused_event)
{
	if (!(290 < touch->getLocation().y&& touch->getLocation().y < 690) && !(23 < touch->getLocation().y&& touch->getLocation().y < 210))
	{
		return false;
	}
	if (290 < touch->getLocation().y&& touch->getLocation().y < 690)
		touchpos = true;
	else
		touchpos = false;

	firstmousepos.setPoint(touch->getLocation().x, touch->getLocation().y);
	return true;
}
void MapChoice::onTouchMoved(Touch* touch, Event* unused_event)
{

	Vec2 pos;
	if (touchpos)
	{
		pos.setPoint(touch->getLocation().x - firstmousepos.x, touch->getLocation().y - firstmousepos.y);

		if ((stagemap1->getPosition().x > 640 && pos.x > 0) || (stagemap6->getPosition().x < 640 && pos.x < 0))
			pos.x = 0;

		stagemap1->setPosition(Vec2(stagemap1->getPosition().x + pos.x, stagemap1->getPosition().y));
		stagemap2->setPosition(Vec2(stagemap2->getPosition().x + pos.x, stagemap2->getPosition().y));
		stagemap3->setPosition(Vec2(stagemap3->getPosition().x + pos.x, stagemap3->getPosition().y));
		stagemap4->setPosition(Vec2(stagemap4->getPosition().x + pos.x, stagemap4->getPosition().y));
		stagemap5->setPosition(Vec2(stagemap5->getPosition().x + pos.x, stagemap5->getPosition().y));
		stagemap6->setPosition(Vec2(stagemap6->getPosition().x + pos.x, stagemap6->getPosition().y));
	}

	else
	{
		pos.setPoint(touch->getLocation().x - firstmousepos.x, touch->getLocation().y - firstmousepos.y);


		if ((stage1->getPosition().x > 640 && pos.x > 0) || (stage5->getPosition().x < 640 && pos.x < 0))
			pos.x = 0;


		stage1->setPosition(Vec2(stage1->getPosition().x + pos.x, stage1->getPosition().y));
		stage2->setPosition(Vec2(stage2->getPosition().x + pos.x, stage2->getPosition().y));
		stage3->setPosition(Vec2(stage3->getPosition().x + pos.x, stage3->getPosition().y));
		stage4->setPosition(Vec2(stage4->getPosition().x + pos.x, stage4->getPosition().y));
		stage5->setPosition(Vec2(stage5->getPosition().x + pos.x, stage5->getPosition().y));
	}
	firstmousepos.setPoint(touch->getLocation().x, touch->getLocation().y);
}
void MapChoice::onTouchEnded(Touch * touch, Event * unused_event)
{

}


//void MapChoice::mapstageleftButton(Ref* pSender)
//{
//
//   if (StageMapMove < 5 && StageMapLeftMove == true)
//   {
//      MenuItemImage* unit[] =
//      {
//         stagemap1,stagemap2,stagemap3,stagemap4,stagemap5,stagemap6
//      };
//      for (int i = 0; i < 6; i++)
//      {
//         unit[i]->runAction(Sequence::create(MoveBy::create(0.7f, Point(-500, 0)), CallFunc::create([&]() {StageMapLeftMove = true; }), nullptr));
//      }
//      StageMapLeftMove = false;
//      StageMapMove += 1;
//   }
//}
//void MapChoice::mapstagelightButton(Ref* pSender)
//{
//
//   if (StageMapMove > 0 && StageMapRightMove == true)
//   {
//      MenuItemImage* units[] =
//      {
//         stagemap1,stagemap2,stagemap3,stagemap4,stagemap5,stagemap6
//      };
//      for (int mm = 0; mm < 6; mm++)
//      {
//         units[mm]->runAction(Sequence::create(MoveBy::create(0.7f, Point(500, 0)), CallFunc::create([&]() {StageMapRightMove = true; }), nullptr));
//      }
//      StageMapRightMove = false;
//      StageMapMove -= 1;
//   }
//
//}
//void MapChoice::stageleftButton(Ref* pSender)
//{
//
//   if (StageMove < 4 && StageLeftMove == true)
//   {
//      MenuItemImage* unitss[] =
//      {
//         stage1,stage2,stage3,stage4,stage5
//      };
//      for (int ww = 0; ww <5; ww++)
//      {
//         unitss[ww]->runAction(Sequence::create(MoveBy::create(0.7f, Point(-410, 0)), CallFunc::create([&]() {StageLeftMove = true; }), nullptr));
//      }
//      StageLeftMove = false;
//      StageMove += 1;
//   }
//}
//void MapChoice::stagelightButton(Ref* pSender)
//{
//   if (StageMove > 0 && StageRightMove == true)
//   {
//      MenuItemImage* unitss[] =
//      {
//         stage1,stage2,stage3,stage4,stage5
//      };
//      for (int wwe = 0; wwe < 5; wwe++)
//      {
//         unitss[wwe]->runAction(Sequence::create(MoveBy::create(0.7f, Point(410, 0)), CallFunc::create([&]() {StageRightMove = true; }), nullptr));
//      }
//      StageRightMove = false;
//      StageMove -= 1;
//   }
//}