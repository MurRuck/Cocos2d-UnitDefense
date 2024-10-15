#include "MenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool MenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//여기는 설정팝업 레이어 생성
	PopUp_Layer_Color = LayerColor::create(Color4B(255, 255, 255, 100));
	PopUp_Layer_Color->setPosition(Vec2::ZERO);
	PopUp_Layer_Color->setVisible(false);
	this->addChild(PopUp_Layer_Color, 2); 

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	

	//설정팝업 끄는 버튼
	auto PopUp_Layer_Back = MenuItemImage::create(
		"UI/button/button_n/Close_n.png",
		"UI/button/button_c/Close_c.png",
		CC_CALLBACK_1(MenuScene::PopUp_Layer_Back, this));

	PopUp_Layer_Back->setPosition(Vec2(970, 564));
	PopUp_Layer_Back->setTag(1);
	PopUp_Layer_Back->setScale(0.7);

	auto popup_layer_back = Menu::create(PopUp_Layer_Back, NULL);
	popup_layer_back->setPosition(Vec2::ZERO);
	PopUp_Layer_Color->addChild(popup_layer_back, 4);

	Sprite* PopUp_Layer_Sprite = Sprite::create("background/SettingBackground.png");
	PopUp_Layer_Sprite->setPosition(Vec2(640, 360));
	PopUp_Layer_Sprite->setScale(2.0);
	PopUp_Layer_Color->addChild(PopUp_Layer_Sprite, 1);


	//소리 조작 버튼

	//노래 조작 버튼
	auto Music_0_1 = MenuItemImage::create("UI/button/toggle/Onbutton.png", "UI/button/toggle/Offbutton.png");
	auto Music_0_2 = MenuItemImage::create("UI/button/toggle/Offbutton.png", "UI/button/toggle/Onbutton.png");
	auto MusicControl = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuScene::Music, this),
		Music_0_1, Music_0_2, NULL);

	MusicControl->setPosition(Vec2(780, 430));
	MusicControl->setScale(1.8);
	MusicControl->setTag(1);

	auto musiccontrol = Menu::create(MusicControl, NULL);
	musiccontrol->setPosition(Vec2::ZERO);
	PopUp_Layer_Color->addChild(musiccontrol, 3);

	//효과음 조작 버튼

	auto Effect_0_1 = MenuItemImage::create("UI/button/toggle/Onbutton.png", "UI/button/toggle/Offbutton.png");
	auto Effect_0_2 = MenuItemImage::create("UI/button/toggle/Offbutton.png", "UI/button/toggle/Onbutton.png");
	auto EffectControl = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuScene::Effect, this),
		Effect_0_1, Effect_0_2, NULL);

	EffectControl->setPosition(Vec2(780, 240));
	EffectControl->setScale(1.8);
	EffectControl->setTag(1);

	auto effectcontrol = Menu::create(EffectControl, NULL);
	effectcontrol->setPosition(Vec2::ZERO);
	PopUp_Layer_Color->addChild(effectcontrol, 3);

	//여기는 설정창
	auto Setting = MenuItemImage::create(
		"UI/button/button_n/Setting_n.png",
		"UI/button/button_c/Setting_c.png",
		CC_CALLBACK_1(MenuScene::Setting, this));

	Setting->setPosition(Vec2(0, -18));
	Setting->setAnchorPoint(Vec2(0, 0));
	Setting->setTag(1);
	Button_Vec.pushBack(Setting);


	auto setting = Menu::create(Setting, NULL);
	setting->setPosition(Vec2::ZERO);
	this->addChild(setting, 1);

	//여기는 시작버튼
	auto Start = MenuItemImage::create(
		"UI/button/button_n/Start_n.png",
		"UI/button/button_c/Start_c.png",
		CC_CALLBACK_1(MenuScene::Start, this));

	Start->setPosition(Vec2(1280, 360));
	Start->setAnchorPoint(Vec2(1, 0.5));
	Start->setScale(1.8);
	Start->setTag(1);
	Button_Vec.pushBack(Start);

	auto start = Menu::create(Start, NULL);
	start->setPosition(Vec2::ZERO);
	this->addChild(start, 1);



	//여기는 상점
	auto Shop = MenuItemImage::create(
		"UI/button/button_n/Shop_n.png",
		"UI/button/button_c/Shop_c.png",
		CC_CALLBACK_1(MenuScene::Shop, this));

	Shop->setPosition(Vec2(1280, 210));
	Shop->setAnchorPoint(Vec2(1, 0.5));
	Shop->setTag(1);
	Shop->setScale(0.8);
	Button_Vec.pushBack(Shop);


	auto shop = Menu::create(Shop, NULL);
	shop->setPosition(Vec2::ZERO);
	this->addChild(shop, 1);
	
	auto sprite = Sprite::create("background/MenuScene.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(sprite, 0);

	this->schedule(schedule_selector(MenuScene::scheduleCallback), 0.1);
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/BGM.wav", true);

	Sprite* Money = Sprite::create("UI/Money.png");
	Money->setAnchorPoint(Vec2(0, 1));
	Money->setPosition(Vec2(1280, 0));
	this->addChild(Money, 0);

	//제작자 레이어 생성
	Creater_Layer = LayerColor::create(Color4B(255, 255, 255, 0));
	Creater_Layer->setPosition(Vec2::ZERO);
	Creater_Layer->setVisible(false);
	this->addChild(Creater_Layer, 5);

	

	//제작자 버튼
	auto Creater_Button = MenuItemImage::create(
		"UI/button/button_n/creater_n.png", 
		"UI/button/button_c/creater_c.png",
		CC_CALLBACK_1(MenuScene::Creater_Button, this));

	Creater_Button->setPosition(Vec2(1280, 0));
	Creater_Button->setAnchorPoint(Vec2(1, 0));
	Creater_Button->setTag(2);
	Creater_Button->setScale(0.7);
	Button_Vec.pushBack(Creater_Button);

	auto creater_button = Menu::create(Creater_Button, NULL);
	creater_button->setPosition(Vec2::ZERO);
	this->addChild(creater_button, 1);
	
	//제작자 취소 버튼
	auto Creater_Layer_Back = MenuItemImage::create(
		"UI/button/button_n/Close_n.png",
		"UI/button/button_c/Close_c.png",
		CC_CALLBACK_1(MenuScene::Creater_Layer_Back, this));

	Creater_Layer_Back->setPosition(Vec2(1280, 720));
	Creater_Layer_Back->setAnchorPoint(Vec2(1, 1));

	auto creater_layer_back = Menu::create(Creater_Layer_Back, NULL);
	creater_layer_back->setPosition(Vec2::ZERO);
	Creater_Layer->addChild(creater_layer_back, 2);



	Sprite* creater_sprite = Sprite::create("HelloWorld.png");
	creater_sprite->setPosition(Vec2(720, 360));
	Creater_Layer->addChild(creater_sprite, 3);
	
	auto Effect_Sound = LabelTTF::create("BackSound", "Arial", 34);
	Effect_Sound->setPosition(Point(450, 430));
	PopUp_Layer_Color->addChild(Effect_Sound, 2);


	auto Background_Sound = LabelTTF::create("EffectSound", "Arial", 34);
	Background_Sound->setPosition(Vec2(450, 240));
	PopUp_Layer_Color->addChild(Background_Sound, 2);

	return true;
}

//설정버튼
void MenuScene::Setting(Ref* pSender)
{
	if (SelectUnit::getInstance()->getSound()->Effect == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/ui_button.wav");
	}
	//레이어 뒤에있는 버튼 안눌리는 것
	for (MenuItemImage* item : Button_Vec )
	{
		item->setEnabled(false);
	}
	switch (((Node*)pSender)->getTag())
	{
	case 1:
		PopUp_Layer_Color->setVisible(true);
		
		break;
	}
}


//시작버튼
void MenuScene::Start(Ref* pSender)
{
	if (SelectUnit::getInstance()->getSound()->Effect == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/ui_button.wav");
	}
	switch (((Node*)pSender)->getTag())
	{
	case 1:
		auto scene = TransitionFade::create(2.0, MapChoice::createScene());
		Director::getInstance()->replaceScene(scene);
		break;
	}
}
//설정창 없에는 버튼
void MenuScene::PopUp_Layer_Back(Ref* pSender)
{
	if (SelectUnit::getInstance()->getSound()->Effect == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/ui_button.wav");
	}
	for (MenuItemImage* item : Button_Vec)
	{
		item->setEnabled(true);
	}
	switch (((Node*)pSender)->getTag())
	{
	case 1:
		PopUp_Layer_Color->setVisible(false);
		break;
	}
}
//제작자 버튼
void MenuScene::Creater_Button(Ref* pSender)
{
	if (SelectUnit::getInstance()->getSound()->Effect == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/ui_button.wav");
	}

	for (MenuItemImage* item : Button_Vec)
	{
		item->setEnabled(false);
	}
	Creater_Layer->setVisible(true);
}
//제작자 끄는버튼
void MenuScene::Creater_Layer_Back(Ref* pSender)
{
	if (SelectUnit::getInstance()->getSound()->Effect == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/ui_button.wav");
	}
	for (MenuItemImage* item : Button_Vec)
	{
		item->setEnabled(true);
	}
	Creater_Layer->setVisible(false);
}
//상점버튼
void MenuScene::Shop(Ref* pSender)
{
	if (SelectUnit::getInstance()->getSound()->Effect == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/ui_button.wav");
	}
	Director::getInstance()->pushScene(Store::createScene());

}
//노래 on/off
void MenuScene::Music(Ref* pSender)
{
	if (SelectUnit::getInstance()->getSound()->Effect == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/ui_button.wav");
	}

	if (SelectUnit::getInstance()->getSound()->Music)
	{
		SelectUnit::getInstance()->getSound()->Music = false;
	}

	else if (SelectUnit::getInstance()->getSound()->Music == false)
	{
		SelectUnit::getInstance()->getSound()->Music = true;
	}
}
//효과음 on/off
void MenuScene::Effect(Ref* pSender)
{
	if (SelectUnit::getInstance()->getSound()->Effect == true)
	{
		SelectUnit::getInstance()->getSound()->Effect = false;
	}
	else if (SelectUnit::getInstance()->getSound()->Effect == false)
	{
		SelectUnit::getInstance()->getSound()->Effect = true;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/ui_button.wav");
	}
	
}
//노래 스케쥴
void MenuScene::scheduleCallback(float db)
{
	if (SelectUnit::getInstance()->getSound()->Music == true)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
	else if (SelectUnit::getInstance()->getSound()->Music == false)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); 
	}

}

