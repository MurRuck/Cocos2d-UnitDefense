#include"Map.h"
#include"UnitChoice.h"
#include"SimpleAudioEngine.h"
#include"store.h"
#include"Control.h"
USING_NS_CC;

Scene* Store::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Store::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool Store::init()
{
	//////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	store = Sprite::create("UI/item/water item.png");
	store->setPosition(Vec2(620, 690));
	store->setScale(5.0f);
	store->setAnchorPoint(Vec2(1, 1));
	this->addChild(store, 1);

	sul = Sprite::create("UI/button/png/sul.png");
	sul->setPosition(Vec2(1020, 650));
	sul->setScale(0.2f);
	sul->setAnchorPoint(Vec2(1, 1));
	this->addChild(sul, 1);

	auto stores = Sprite::create("background/store.png");
	stores->setAnchorPoint(Vec2(1, 1));
	stores->setPosition(Vec2(1280, 720));
	this->addChild(stores, -1);

	/*itembuy = MenuItemImage::create("UI/button/png/buy.png", "UI/button/png/buy.png", CC_CALLBACK_1(Store::atore, this));
	itembuy->setPosition(Vec2(1100, 160));
	itembuy->setAnchorPoint(Vec2(1, 1));
	itembuy->setScale(0.2);
	auto buyitem = Menu::create(itembuy, NULL);
	buyitem->setPosition(Vec2::ZERO);
	this->addChild(buyitem,1);
	*/

	auto back = MenuItemImage::create("UI/button/button_n/back.png", "UI/button/button_c/back1.png", CC_CALLBACK_1(Store::back, this));
	back->setPosition(Vec2(300, 100));
	back->setAnchorPoint(Vec2(1, 1));
	auto back1 = Menu::create(back, NULL);
	back1->setPosition(Vec2::ZERO);
	this->addChild(back1, 1);

	item[0] = MenuItemImage::create("UI/button/png/sprinkler buy.png", "UI/button/png/sprinkler buy.png", CC_CALLBACK_1(Store::buy, this));//아이템 1
	item[1] = MenuItemImage::create("UI/button/png/healpack.png", "UI/button/png/healpack.png", CC_CALLBACK_1(Store::buy, this));//아이템 2
	for (int i = 0; i < 2; i++)
	{
		item[i]->setPosition(Vec2(680 + 450 * i, 400));
		item[i]->setAnchorPoint(Vec2(1, 1));
		item[i]->setScale(0.2f);
		item[i]->setTag(i);

		auto items = Menu::create(item[i], NULL);
		items->setPosition(Vec2::ZERO);
		this->addChild(items, 1);
	}

	itemnumber = Label::createWithTTF(StringUtils::format("%d", SelectUnit::getInstance()->getitembuy()->sprinkler.item), "fonts/Marker Felt.ttf", 24);
	itemnumber->setPosition(Vec2(500, 200));
	itemnumber->setTag(0);
	this->addChild(itemnumber, 1);

	itemnumbers = Label::createWithTTF(StringUtils::format("%d", SelectUnit::getInstance()->getitembuy()->firebomb.item), "fonts/Marker Felt.ttf", 24);
	itemnumbers->setPosition(Vec2(950, 200));
	itemnumbers->setTag(1);
	this->addChild(itemnumbers, 1);

	//pricenumber = Label::createWithTTF(StringUtils::format("%d", SelectUnit::getInstance()->getitembuy()->firebomb.item), "fonts/Marker Felt.ttf", 24);

	return true;
}
void Store::buy(Ref* pSender)
{

	switch (((Node*)pSender)->getTag())
	{
	case 0:
	{
		if (SelectUnit::getInstance()->getitembuy()->money < SelectUnit::getInstance()->getitembuy()->sprinkler.sprinkler_price)
			return;
		SelectUnit::getInstance()->getitembuy()->money -= SelectUnit::getInstance()->getitembuy()->sprinkler.sprinkler_price;
		SelectUnit::getInstance()->getitembuy()->sprinkler.item += 1;
		itemnumber->setString(StringUtils::format("%d", SelectUnit::getInstance()->getitembuy()->sprinkler.item));
		break;
	}
	case 1:
	{
		if (SelectUnit::getInstance()->getitembuy()->money < SelectUnit::getInstance()->getitembuy()->firebomb.heal_price)
			return;
		SelectUnit::getInstance()->getitembuy()->money -= SelectUnit::getInstance()->getitembuy()->firebomb.heal_price;
		SelectUnit::getInstance()->getitembuy()->firebomb.item += 1;
		itemnumbers->setString(StringUtils::format("%d", SelectUnit::getInstance()->getitembuy()->firebomb.item));
		break;
	}
	default:
		break;
	}

	switch (((Node*)pSender)->getTag())
	{
	case 0:
	{
		store->setTexture("UI/item/water item.png");
		sul->setTexture("UI/button/png/sul.png");
		break;
	}
	case 1:
	{
		store->setTexture("UI/item/meditem.png");
		sul->setTexture("UI/button/png/sul1.png");
		break;
	}
	}

}
void Store::back(Ref* pSender)
{
	auto scene = TransitionFade::create(2.0, UnitChoice::createScene());
	Director::getInstance()->replaceScene(scene);
}
//
//void Store::atore(Ref* pSender)
//{
//   
//   /*   switch (((Node*)pSender)->getTag())
//      {
//      case 1:
//      {
//         
//         break;
//      }
//      case 2:
//      {
//      
//         break;
//      }
//      }
//   */
//   //case 3:
//   //{
//   //   store->setTexture("UI/button/png/item2.png");
//   //   sul->setTexture("UI/button/png/sul2.png");
//   //    break;
//   //}
//   //case 4:
//   //{
//   //   store->setTexture("UI/button/png/item3.png");
//   //   sul->setTexture("UI/button/png/sul4.png");
//   //   break; 
//   //}
//   //case 5:
//   //{
//   //   store->setTexture("UI/button/png/item4.png");
//   //   sul->setTexture("UI/button/png/sul5.png");
//   //   break;
//   //}
//   
//}
//	