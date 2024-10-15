#include"UnitChoice.h"
#include"Map.h"
#include"store.h"
#include "Collocate.h"
#include"Control.h"

USING_NS_CC;

Scene* UnitChoice::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = UnitChoice::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
bool UnitChoice::init()
{
	if (!Layer::init())
	{
		return false;
	}

	color = LayerColor::create(Color4B(0, 0, 0, 175));
	color->setPosition(Vec2::ZERO);
	this->addChild(color, -1);

	auto background = Sprite::create("background/UnitChoiceBackground.png");
	background->setAnchorPoint(Vec2(1, 1));
	background->setPosition(Vec2(1280, 720));
	background->setOpacity(150);/*
								//background->setColor(Color3B::BLACK);*/
	this->addChild(background, 0);

	moneys = Sprite::create("UI/Money.png");
	moneys->setAnchorPoint(Vec2(1, 1));
	moneys->setPosition(Vec2(250, 717));
	this->addChild(moneys, 1);

	/*moneylabel = Label::createWithTTF(StringUtils::format("%d", SelectUnit::getInstance()->getitembuy()->money), "Marker Felt", 30);
	moneylabel->setPosition(Vec2(310, 717));
	moneylabel->setAnchorPoint(Vec2(1, 1));
	this->addChild(moneylabel, 2);*/

	soldierchoice[0] = Sprite::create("UI/button/button_n/shield.png");//방패병
	soldierchoice[1] = Sprite::create("UI/button/button_n/rubber.png");//고무탄
	soldierchoice[2] = Sprite::create("UI/button/button_n/stick.png");//막대병
	for (int i = 0; i < 3; i++)
	{
		soldierchoice[i]->setAnchorPoint(Vec2(1, 1));
		soldierchoice[i]->setPosition(Vec2(365 + 360 * i, 560));
		soldierchoice[i]->setScale(0.75f);
		soldierchoice[i]->setTag(i);
		this->addChild(soldierchoice[i], 1);
	}

	label[0] = Label::createWithTTF(StringUtils::format("%d", SelectUnit::getInstance()->getUnitnum()->shield), "fonts/Marker Felt.ttf", 60);
	label[1] = Label::createWithTTF(StringUtils::format("%d", SelectUnit::getInstance()->getUnitnum()->gunner), "fonts/Marker Felt.ttf", 60);
	label[2] = Label::createWithTTF(StringUtils::format("%d", SelectUnit::getInstance()->getUnitnum()->botton), "fonts/Marker Felt.ttf", 60);
	for (int a = 0; a < 3; a++)
	{
		label[a]->setPosition(Vec2(335 + 360 * a, 345));
		label[a]->setTag(a);
		label[a]->setColor(Color3B::BLACK);
		this->addChild(label[a], 1);
	}

	unitup[0] = MenuItemImage::create("UI/button/button_n/up1.png", "UI/button/button_c/up.png", CC_CALLBACK_1(UnitChoice::UnitUp, this));
	unitup[1] = MenuItemImage::create("UI/button/button_n/up1.png", "UI/button/button_c/up.png", CC_CALLBACK_1(UnitChoice::UnitUp, this));
	unitup[2] = MenuItemImage::create("UI/button/button_n/up1.png", "UI/button/button_c/up.png", CC_CALLBACK_1(UnitChoice::UnitUp, this));
	for (int i = 0; i <3; i++)
	{
		unitup[i]->setAnchorPoint(Vec2(1, 1));
		unitup[i]->setPosition(Vec2(315 + 360 * i, 612));
		unitup[i]->setScale(0.3f);
		unitup[i]->setTag(i);

		auto unitupdown = Menu::create(unitup[i], NULL);
		unitupdown->setPosition(Vec2::ZERO);
		this->addChild(unitupdown, 1);
	}

	unitdown[0] = MenuItemImage::create("UI/button/button_n/down1.png", "UI/button/button_c/down.png", CC_CALLBACK_1(UnitChoice::UnitDown, this));
	unitdown[0]->setTag(4);
	unitdown[1] = MenuItemImage::create("UI/button/button_n/down1.png", "UI/button/button_c/down.png", CC_CALLBACK_1(UnitChoice::UnitDown, this));
	unitdown[1]->setTag(5);
	unitdown[2] = MenuItemImage::create("UI/button/button_n/down1.png", "UI/button/button_c/down.png", CC_CALLBACK_1(UnitChoice::UnitDown, this));
	unitdown[2]->setTag(6);
	for (int i = 0; i < 3; i++)
	{
		unitdown[i]->setAnchorPoint(Vec2(1, 1));
		unitdown[i]->setPosition(Vec2(315 + 360 * i, 230));
		unitdown[i]->setScale(0.3f);

		auto unitdownup = Menu::create(unitdown[i], NULL);
		unitdownup->setPosition(Vec2::ZERO);
		this->addChild(unitdownup, 1);

	}

	//auto wepon = MenuItemImage::create("UI/button/button_n/wepon.png", "UI/button/button_c/wepon1.png", CC_CALLBACK_1(UnitChoice::Choice, this));//무기고
	//wepon->setAnchorPoint(Vec2(1, 1));
	//wepon->setPosition(Vec2(400, 150));
	//auto wepon1 = Menu::create(wepon, NULL);
	//wepon1->setPosition(Vec2::ZERO);
	//this->addChild(wepon1, 1);

	auto start = MenuItemImage::create("button/start.png", "button/start1.png", CC_CALLBACK_1(UnitChoice::start, this));//출동
	start->setAnchorPoint(Vec2(1, 1));
	start->setPosition(Vec2(1200, 160));
	start->setScale(0.82);
	auto start1 = Menu::create(start, NULL);
	start1->setPosition(Vec2::ZERO);
	this->addChild(start1, 1);

	store1 = MenuItemImage::create("UI/button/button_c/store.png", "UI/button/button_n/store_n.png", CC_CALLBACK_1(UnitChoice::store, this));//상점
	store1->setAnchorPoint(Vec2(1, 1));
	store1->setPosition(Vec2(300, 170));
	store1->setScale(0.8);
	auto store21 = Menu::create(store1, NULL);
	store21->setPosition(Vec2::ZERO);
	this->addChild(store21, 1);

	/*auto label = Label::create("MAX UNIT : 10","fonts/Marker Felt.ttf", 75);
	label->setPosition(Vec2(650, 100));
	this->addChild(label, 1);*/

	auto unitcount = Sprite::create("UI/score/max.png");
	unitcount->setAnchorPoint(Vec2(1, 1));
	unitcount->setPosition(Vec2(640, 130));
	unitcount->setScale(5.0);
	this->addChild(unitcount, 1);

	auto colon = Sprite::create("UI/score/colon.png");
	colon->setPosition(Vec2(700, 130));
	colon->setAnchorPoint(Vec2(1, 1));
	colon->setScale(5.0);
	this->addChild(colon, 1);

	auto number = Sprite::create("UI/score/b1.png");
	number->setPosition(Vec2(790, 130));
	number->setAnchorPoint(Vec2(1, 1));
	number->setScale(5.0);
	this->addChild(number, 1);

	auto number1 = Sprite::create("UI/score/b0.png");
	number1->setPosition(Vec2(880, 130));
	number1->setAnchorPoint(Vec2(1, 1));
	number1->setScale(5.0);
	this->addChild(number1, 1);

	auto scene = MenuItemImage::create("UI/button/button_n/Back_n.png", "UI/button/button_c/Back_c.png", CC_CALLBACK_1(UnitChoice::back, this));
	scene->setScale(0.68);
	scene->setAnchorPoint(Vec2(1, 1));
	scene->setPosition(Vec2(1320, 740));
	auto scenes = Menu::create(scene, NULL);
	scenes->setPosition(Vec2::ZERO);
	this->addChild(scenes, 1);


	//layerstick = MenuItemImage::create("UI/button/button_n/stick.png", "UI/button/button_c/stick1.png", CC_CALLBACK_1(UnitChoice::ChangeItem, this));//레이어화면에서봉조
	//layerstick->setPosition(Vec2(375, 520));
	//layerstick->setAnchorPoint(Vec2(1, 1));
	//layerstick->setTag(4);
	//layerstick->setScale(1.3);
	//auto layerstick1 = Menu::create(layerstick, NULL);
	//layerstick1->setPosition(Vec2::ZERO);
	//color->addChild(layerstick1, 3);

	//layershield = MenuItemImage::create("UI/button/button_n/shield.png", "UI/button/button_c/shield1.png", CC_CALLBACK_1(UnitChoice::ChangeItem, this)); //레이어화면에서방패조
	//layershield->setPosition(Vec2(585, 520));
	//layershield->setTag(5);
	//layershield->setScale(1.3);
	//layershield->setAnchorPoint(Vec2(1, 1));
	//auto layershield1 = Menu::create(layershield, NULL);
	//layershield1->setPosition(Vec2::ZERO);
	//color->addChild(layershield1, 3);

	//layerrubber = MenuItemImage::create("UI/button/button_n/rubber.png", "UI/button/button_c/rubber1.png", CC_CALLBACK_1(UnitChoice::ChangeItem, this));//레이어화면에서고무탄조
	//layerrubber->setPosition(Vec2(795, 520));
	//layerrubber->setTag(6);
	//layerrubber->setScale(1.3);
	//layerrubber->setAnchorPoint(Vec2(1, 1));
	//auto layerrubber1 = Menu::create(layerrubber, NULL);
	//layerrubber1->setPosition(Vec2::ZERO);
	//color->addChild(layerrubber1, 3);

	//layergas = MenuItemImage::create("UI/button/button_n/gas.png", "UI/button/button_c/gas1.png", CC_CALLBACK_1(UnitChoice::ChangeItem, this));//레이어화면에서최루탄조
	//layergas->setPosition(Vec2(1005, 520));
	//layergas->setTag(7);
	//layergas->setScale(1.3);
	//layergas->setAnchorPoint(Vec2(1, 1));
	//auto layergas1 = Menu::create(layergas, NULL);
	//layergas1->setPosition(Vec2::ZERO);
	//color->addChild(layergas1, 3);

	//auto back1 = MenuItemImage::create("UI/button/button_n/Close_n.png", "UI/button/button_c/Close_c.png", CC_CALLBACK_1(UnitChoice::back, this));//뒤로가기
	//back1->setAnchorPoint(Vec2(1, 1));
	//back1->setPosition(Vec2(950, 700));
	//auto back2 = Menu::create(back1, NULL);
	//back2->setPosition(Vec2::ZERO);
	//back2->addChild(back2, 3);

	return true;
}
void UnitChoice::start(Ref* pSender)
{
	auto scene = TransitionFade::create(1.0, Collocate::createScene());
	Director::getInstance()->replaceScene(scene);
}
void UnitChoice::UnitUp(Ref * pSender)
{
	if (SelectUnit::getInstance()->getUnitnum()->maxunit <= SelectUnit::getInstance()->getUnitnum()->shield + SelectUnit::getInstance()->getUnitnum()->gunner + SelectUnit::getInstance()->getUnitnum()->botton)
		return;

	switch (((Node*)pSender)->getTag())
	{
	case 0:
		label[0]->setString(StringUtils::format("%d", ++SelectUnit::getInstance()->getUnitnum()->shield));
		break;
	case 1:
		label[1]->setString(StringUtils::format("%d", ++SelectUnit::getInstance()->getUnitnum()->gunner));
		break;
	case 2:
		label[2]->setString(StringUtils::format("%d", ++SelectUnit::getInstance()->getUnitnum()->botton));
		break;
	default:
		break;
	}
}
void UnitChoice::UnitDown(Ref * pSender)
{
	switch (((Node*)pSender)->getTag())
	{
	case 4:
		if (SelectUnit::getInstance()->getUnitnum()->shield == 0)
			break;
		label[0]->setString(StringUtils::format("%d", --SelectUnit::getInstance()->getUnitnum()->shield));
		break;
	case 5:
		if (SelectUnit::getInstance()->getUnitnum()->gunner == 0)
			break;
		label[1]->setString(StringUtils::format("%d", --SelectUnit::getInstance()->getUnitnum()->gunner));
		break;
	case 6:
		if (SelectUnit::getInstance()->getUnitnum()->botton == 0)
			break;
		label[2]->setString(StringUtils::format("%d", --SelectUnit::getInstance()->getUnitnum()->botton));
		break;
	default:
		break;
	}
}
void UnitChoice::back(Ref* pSender)
{
	auto scene = TransitionFade::create(2.0, MapChoice::createScene());
	Director::getInstance()->replaceScene(scene);
	/*color->setVisible(false);
	store1->setEnabled(true);
	for (int i = 0; i < 4; i++)
	{
	soldierchoice[i]->setEnabled(true);
	}*/
}
void UnitChoice::ChangeItem(Ref* pSender)
{
	/*switch (((Sprite*)(pSender))->getTag())
	{
	case 4:
	soldierchoice[nItemNum]->setNormalImage(Sprite::create("UI/button/button_n/stick.png"));
	soldierchoice[nItemNum]->setSelectedImage(Sprite::create("UI/button/button_c/stick1.png"));
	break;
	case 5:
	soldierchoice[nItemNum]->setNormalImage(Sprite::create("UI/button/button_n/shield.png"));
	soldierchoice[nItemNum]->setSelectedImage(Sprite::create("UI/button/button_c/shield1.png"));
	break;
	case 6:
	soldierchoice[nItemNum]->setNormalImage(Sprite::create("UI/button/button_n/rubber.png"));
	soldierchoice[nItemNum]->setSelectedImage(Sprite::create("UI/button/button_c/rubber1.png"));
	break;
	case 7:
	soldierchoice[nItemNum]->setNormalImage(Sprite::create("UI/button/button_n/gas.png"));
	soldierchoice[nItemNum]->setSelectedImage(Sprite::create("UI/button/button_c/gas1.png"));
	break;
	}
	color->setVisible(false);
	store1->setEnabled(true);

	for (int i = 0; i < 4; i++)
	{
	soldierchoice[i]->setEnabled(true);
	}*/

}
void UnitChoice::Choice(Ref* pSender)
{

	nItemNum = ((Sprite*)(pSender))->getTag();
	for (int i = 0; i < 3; i++)
	{/*
	 store1->setEnabled(false);
	 soldierchoice[i]->setEnabled(false);*/
		switch (soldierchoice[i]->getTag())
		{
		case SHIELD:
			SelectUnit::getInstance()->getUnitnum()->shield += 1;
			break;
		case BOTTON:
			SelectUnit::getInstance()->getUnitnum()->botton += 1;
			break;
		case GUNNER:
			SelectUnit::getInstance()->getUnitnum()->gunner += 1;
			break;
			//case TEARTHROWER:
			//   //SelectUnit::getInstance()->getUnitnum()->tearthrower += 1;
			//   break;
		default:
			break;
		}
	}
}
void UnitChoice::store(Ref* pSender)
{
	auto scene = TransitionFade::create(2.0, Store::createScene());
	Director::getInstance()->replaceScene(scene);
}