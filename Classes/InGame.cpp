#include "InGame.h"
#include "Map.h"
#include "UnitsAddress.h"
#include "SimpleAudioEngine.h"
#include "Control.h"
#include "Collocate.h"

USING_NS_CC;

Scene* InGame::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = InGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool InGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }


	this->setTouchEnabled(true);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);


	this->setKeyboardEnabled(true);


    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	show_time = Label::createWithTTF(StringUtils::format("%d : %.2d", time_minute, time_second), "fonts/Marker Felt.ttf", 48);
	show_time->setPosition(Vec2(640, 720));
	show_time->setAnchorPoint(Vec2(0.5, 1));
	this->addChild(show_time, 2);

	
	struct Unknown
	{
		Vec2 pos;
		int type;
		int detail;
	};

	Unknown data[] = {
		//{ Vec2(50,50), UnitsAddress::CITIZEN, UnitsAddress::NORMAL_PEOPLE },

		{ Vec2(20,50),	UnitsAddress::CITIZEN, UnitsAddress::NORMAL_PEOPLE },
		{ Vec2(35,120), UnitsAddress::CITIZEN, UnitsAddress::NORMAL_PEOPLE },
		{ Vec2(50,190), UnitsAddress::CITIZEN, UnitsAddress::NORMAL_PEOPLE },
		{ Vec2(35,260), UnitsAddress::CITIZEN, UnitsAddress::NORMAL_PEOPLE },
		{ Vec2(20,330), UnitsAddress::CITIZEN, UnitsAddress::NORMAL_PEOPLE },

		{Vec2(0,0),0,30 },
	};

	layer = LayerColor::create();
	layer->setPosition(getPosition().x - 1280, getPosition().y);
	this->addChild(layer);

	option_layer = LayerColor::create(Color4B(0, 0, 0, 100));
	option_layer->setVisible(false);
	this->addChild(option_layer, 5);

	sound_layer = LayerColor::create(Color4B(0, 0, 0, 100));
	sound_layer->setVisible(false);
	this->addChild(sound_layer, 5);

	confirm_layer = LayerColor::create(Color4B(0, 0, 0, 100));
	confirm_layer->setVisible(false);
	this->addChild(confirm_layer, 5);
	for (int i = 0;i < i + 1;i++)
	{
		if (data[i].detail == 30)
			break;

		data[i].pos.x -= 1280;

		UnitsAddress::getInstance()->RunUnitsFunction(data[i].pos, data[i].type, data[i].detail, layer);
	}

	{																																//¿©±â ÀÕ¾î¾ßµÊ Áö¿ì¸é¾ÈµÊ
		int detail;
		Vec2 pos;
		auto units = *SelectUnit::getInstance()->getUnitnum();
	
		for (int i = 0;i < SelectUnit::getInstance()->getUnitnum()->maxunit;i++)										
		{
			if (units.botton > 0)
			{
				detail = UnitsAddress::BOTTON;
				pos = SelectUnit::getInstance()->getUnitvec()->botton[units.botton - 1];
				units.botton -= 1;
			}
			else if (units.gunner > 0)
			{
				detail = UnitsAddress::GUNNER;
				pos = SelectUnit::getInstance()->getUnitvec()->gunner[units.gunner - 1];
	
				auto mtii = SelectUnit::getInstance()->getUnitvec()->gunner;
				units.gunner -= 1;
			}
			else if (units.shield > 0)
			{
				detail = UnitsAddress::SHIELD;
				pos = SelectUnit::getInstance()->getUnitvec()->shield[units.shield - 1];
				units.shield -= 1;
			}

			pos.x = pos.x + 1280;
	
			UnitsAddress::getInstance()->RunUnitsFunction(pos, UnitsAddress::POLICE, detail, layer);
	
			pos.x = 0;
			pos.y = 0;
		}
	}

	//touched[0] = new ShieldUnit;
	//touched[0]->createUnit("test.png", Vec2(300,300), this);
	//UnitsAddress::getInstance()->AddUnit(touched[0], UnitsAddress::POLICE);
	//touched[0]->Animateinit(this);
	//
	//touched[1] = new BottonUnit;
	//touched[1]->createUnit("test.png", Vec2(600, 600), this);
	//UnitsAddress::getInstance()->AddUnit(touched[1], UnitsAddress::POLICE);
	//touched[1]->Animateinit(this);
	//
	//touched[2] = new GunnerUnit;
	//touched[2]->createUnit("test.png", Vec2(900, 500), this);
	//UnitsAddress::getInstance()->AddUnit(touched[2], UnitsAddress::POLICE);
	//touched[2]->Animateinit(this);

	//citizen = new People;
	//citizen->createUnit("test.png", Vec2(200, 200), this);
	//UnitsAddress::getInstance()->AddUnit(citizen, UnitsAddress::CITIZEN);
	//citizen->Animateinit(this);

	//citizen->RunFunction();

	/*for (int i = 0;i < 10;i++)
	{
		shieldunit[i].createUnit("shield/stand/sprite_1.png", Vec2(i * 100 + 50, i * 50 + 50), this);
		shieldunit[i].createLine(this, 9);
		shieldunit[i].Animateinit(this);
		for (int j = 0;j < 10;j++)
		{
			if (i == j)
				continue;
			shieldunit[i].connectLine(shieldunit[j].getUnit());
		}
	}*/
	
	touchedunit = nullptr;

	//Sprite* mainmap = Sprite::create("map/stage_1/bottom.png");
	//mainmap->setAnchorPoint(Vec2::ZERO);
	//mainmap->setPosition(Vec2(0, 0));
	//layer->addChild(mainmap, -1);
	//
	//
	//Sprite* mainmap1 = Sprite::create("map/stage_1/top.png");
	//mainmap1->setAnchorPoint(Vec2::ZERO);
	//mainmap1->setPosition(Vec2(0, mainmap->getContentSize().height));
	//layer->addChild(mainmap1, -1);

	for (int i = -1;i < 2;i++)
	{
		Sprite* FWT = Sprite::create("map/stage_1/all.png");
		FWT->setAnchorPoint(Vec2(0.f, 0.f));
		FWT->setPosition(Vec2(1280 * i, 0));
		layer->addChild(FWT, -1);
	}


	/*MenuItemImage* button[2];

	for (int i = 0;i < 2;i++)
	{
		button[i] = MenuItemImage::create("test.png", "test.png", CC_CALLBACK_1(InGame::menuCloseCallback, this));
		button[i]->setPosition(Vec2(100 + i * 200, 100));
		button[i]->setTag(i);
	}

	auto menu = Menu::create(button[0], button[1], nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);*/

	sprite__ = Sprite::create("test.png");
	sprite__->setPosition(Vec2(300, 300));
	sprite__->setVisible(false);
	this->addChild(sprite__, 2);


	auto option = MenuItemImage::create(
		"UI/button/button_n/option_n.png",
		"UI/button/button_c/option_c.png",
		CC_CALLBACK_1(InGame::option, this));
	// increases X and Y size by 2.0 uniformly
	option->setAnchorPoint(Vec2(1, 1));
	option->setPosition(Vec2(1280, 720));
	option->setScale(0.7);
	Button_Vec.pushBack(option);

	auto option_ = Menu::create(option, NULL);
	option_->setPosition(Vec2::ZERO);
	this->addChild(option_, 6);

	auto go_menu = MenuItemImage::create(
		"UI/button/button_n/menu_n.png",
		"UI/button/button_c/menu_c.png",
		CC_CALLBACK_1(InGame::go_to_menu, this));
	go_menu->setPosition(Vec2(640, 200));

	auto menu_ = Menu::create(go_menu, NULL);
	menu_->setPosition(Vec2::ZERO);
	option_layer->addChild(menu_, 6);


	auto setting = MenuItemImage::create(
		"UI/button/button_n/setting_n.png",
		"UI/button/button_c/setting_c.png",
		CC_CALLBACK_1(InGame::setting, this));
	setting->setPosition(Vec2(640, 300));

	auto setting_ = Menu::create(setting, NULL);
	setting_->setPosition(Vec2::ZERO);
	option_layer->addChild(setting_, 6);


	auto restart = MenuItemImage::create(
		"UI/button/button_n/restart_n.png",
		"UI/button/button_c/restart_c.png",
		CC_CALLBACK_1(InGame::restart, this));
	restart->setPosition(Vec2(640, 400));

	auto restart_ = Menu::create(restart, NULL);
	restart_->setPosition(Vec2::ZERO);
	option_layer->addChild(restart_, 6);


	auto to_continue = MenuItemImage::create(
		"UI/button/button_n/continue_n.png",
		"UI/button/button_c/continue_c.png",
		CC_CALLBACK_1(InGame::continue_play, this));
	to_continue->setPosition(Vec2(640, 500));
	

	auto continue_ = Menu::create(to_continue, NULL);
	continue_->setPosition(Vec2::ZERO);
	option_layer->addChild(continue_, 6);


	auto music_01 = MenuItemImage::create("UI/button/toggle/Onbutton.png", "UI/button/toggle/Offbutton.png");
	auto music_02 = MenuItemImage::create("UI/button/toggle/Offbutton.png", "UI/button/toggle/Onbutton.png");
	auto music = MenuItemToggle::createWithCallback(CC_CALLBACK_1(InGame::music_control, this), music_01, music_02, NULL);
	music->setPosition(Vec2(820, 150));
	music->setScale(2.3);

	auto music_ = Menu::create(music, NULL);
	music_->setPosition(Vec2::ZERO);
	sound_layer->addChild(music_, 6);


	auto effect_01 = MenuItemImage::create("UI/button/toggle/Onbutton.png", "UI/button/toggle/Offbutton.png");
	auto effect_02 = MenuItemImage::create("UI/button/toggle/Offbutton.png", "UI/button/toggle/Onbutton.png");
	auto effect = MenuItemToggle::createWithCallback(CC_CALLBACK_1(InGame::effect_control, this), effect_01, effect_02, NULL);
	effect->setPosition(Vec2(820, 400));
	effect->setScale(2.3);

	auto effect_ = Menu::create(effect, NULL);
	effect_->setPosition(Vec2::ZERO);
	sound_layer->addChild(effect_, 6);

	auto close_sound = MenuItemImage::create(
		"UI/button/button_n/close_n.png",
		"UI/button/button_c/close_c.png",
		CC_CALLBACK_1(InGame::sound_close, this));
	close_sound->setPosition(Vec2(1014, 590));

	auto close_sound_ = Menu::create(close_sound, NULL);
	close_sound_->setPosition(Vec2::ZERO);
	sound_layer->addChild(close_sound_, 6);

	auto confirm_yes = MenuItemImage::create(
		"UI/button/button_n/continue_n.png",
		"UI/button/button_c/continue_c.png",
		CC_CALLBACK_1(InGame::confirm_c_yes, this));
	confirm_yes->setPosition(Vec2(500, 360));

	auto confirm_yes_ = Menu::create(confirm_yes, NULL);
	confirm_yes_->setPosition(Vec2::ZERO);
	confirm_layer->addChild(confirm_yes_, 6);

	auto confirm_no = MenuItemImage::create(
		"UI/button/button_n/close_n.png",
		"UI/button/button_c/close_c.png",
		CC_CALLBACK_1(InGame::confirm_c_no, this));
	confirm_no->setPosition(Vec2(780, 360));

	auto confirm_no_ = Menu::create(confirm_no, NULL);
	confirm_no_->setPosition(Vec2::ZERO);
	confirm_layer->addChild(confirm_no_, 6);


	Sprite* soundbackground = Sprite::create("background/SettingBackground.png");
	soundbackground->setScale(2.8);
	soundbackground->setPosition(Vec2(640, 360));
	sound_layer->addChild(soundbackground, 4);

	Sprite* pausebackground = Sprite::create("background/pausebackground.png");
	pausebackground->setPosition(Vec2(640, 360));
	pausebackground->setScaleY(0.8);
	pausebackground->setScaleX(1.3);
	pausebackground->setOpacity(500);
	option_layer->addChild(pausebackground, 4);

	Sprite* confirmbackground = Sprite::create("background/pausebackground.png");
	confirmbackground->setPosition(Vec2(640, 360));
	confirmbackground->setScaleY(0.5);
	confirmbackground->setScaleX(1.2);
	confirmbackground->setOpacity(500);
	confirm_layer->addChild(confirmbackground, 4);

	schedule(schedule_selector(InGame::time_later), 1.0f);
	
	this->scheduleUpdate();
	
	
    return true;
}

void InGame::update(float dt)
{
	/*for (int i = 0;i < 10;i++)
	{
		for (int j = 0;j < 10;j++)
			shieldunit[i].drawLine(j, 200, true);
	}*/


	for (int i = 0;i < UnitsAddress::getInstance()->getMaxUnitsnum();i++)
	{

		if (UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i) == nullptr)
			continue;


		if (UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i)->unitaddress->getUnit()->getTag() == 100)
			continue;
		UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i)->unitaddress->attackUnit();
	}

	finish();
}

void InGame::finish()
{
	static bool into = true;
	bool into_[2] = { true, true };

	for (int i = 0; i < UnitsAddress::getInstance()->getMaxUnitsnum(); i++)
	{
		if (UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i) != nullptr)
			into_[0] = false;
	}

	for (int i = 0; i < UnitsAddress::getInstance()->getMaxUnitsnum(); i++)
	{
		if (UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i) != nullptr)
			into_[1] = false;
	}



	if (!into)
		return;

	if (into_[0] || into_[1])
	{
		LayerColor* finish_layer = LayerColor::create(Color4B::BLACK);
		finish_layer->setOpacity(100);
		finish_layer->setPosition(Vec2(*SelectUnit::getInstance()->getMovedXpos(), 0));
		layer->addChild(finish_layer, 10);

		Sprite* finish_sprite = Sprite::create("finish/finish_popup.png");

		//if (SelectUnit::getInstance()->getUnits_result()->deadCitizen >= 1)
		//   finish_sprite->setColor(Color3B::RED);
		//else if (SelectUnit::getInstance()->getUnits_result()->nodieCitizen >= 1)
		//   finish_sprite->setColor(Color3B::YELLOW);


		finish_sprite->setPosition(Vec2(640, 460));
		finish_sprite->setScale(1.33f);
		finish_layer->addChild(finish_sprite, 99);


		MenuItemImage* menuitemiamge[3];

		char filename[3][2][50] =
		{
			{ "finish/result next.png","finish/result next pressed.png" },
			{ "finish/result retry.png", "finish/result retry pressd.png" },
			{ "finish/result exit.png", "finish/result exit pressed.png" },
		};

		for (int i = 0; i < 3; i++)
		{

			menuitemiamge[i] = MenuItemImage::create(filename[i][0], filename[i][1], CC_CALLBACK_1(InGame::menuCloseCallback, this));
			menuitemiamge[i]->setTag(i + 100);
			menuitemiamge[i]->setPosition(Vec2(50 + i * menuitemiamge[i]->getContentSize().width, 0));
		}

		Menu* menu = Menu::create(menuitemiamge[0], menuitemiamge[1], menuitemiamge[2], nullptr);
		menu->setPosition(Vec2(finish_sprite->getPosition().x - finish_sprite->getContentSize().width / 2 + 29, finish_sprite->getPosition().y - finish_sprite->getContentSize().height / 2 - 60));
		finish_layer->addChild(menu, 100);








		for (int i = 0; i < 4; i++)
		{
			int tmp[4] = {
				SelectUnit::getInstance()->getUnits_result()->nodieCitizen,
				SelectUnit::getInstance()->getUnits_result()->deadCitizen,
				SelectUnit::getInstance()->getUnits_result()->nodiePolice,
				SelectUnit::getInstance()->getUnits_result()->deadPolice,
			};

			if (tmp[i] > 9)
			{
				Sprite* numberChar = Sprite::create(StringUtils::format("number/wb%d.png", tmp[i] / 10));
				numberChar->setAnchorPoint(Vec2(0, 0));
				numberChar->setScale(1.5f);
				numberChar->setPosition(Vec2(475, 245 - 32 * i));
				finish_sprite->addChild(numberChar);


				Sprite* numberChar_1 = Sprite::create(StringUtils::format("number/wb%d.png", tmp[i] % 10));
				numberChar_1->setAnchorPoint(Vec2(0, 0));
				numberChar_1->setScale(1.5f);
				numberChar_1->setPosition(Vec2(475 + numberChar->getContentSize().width + 10, 245 - 32 * i));
				finish_sprite->addChild(numberChar_1);
			}
			else
			{
				Sprite* numberChar = Sprite::create(StringUtils::format("number/wb%d.png", tmp[i]));
				numberChar->setAnchorPoint(Vec2(0, 0));
				numberChar->setScale(1.5f);
				numberChar->setPosition(Vec2(475, 245 - 32 * i));
				finish_sprite->addChild(numberChar);
			}
		}
		ranking(1, finish_sprite);
		into = false;
	}

	//if (into_[1])
	//{
	//   LayerColor* finish_layer = LayerColor::create(/*Color4B::RED*/);
	//   finish_layer->setOpacity(100);
	//   finish_layer->setPosition(Vec2(*SelectUnit::getInstance()->getMovedXpos(), 0));
	//   layer->addChild(finish_layer, 10);

	//   Sprite* finish_sprite = Sprite::create("finish/finish_popup.png");

	//   //if (SelectUnit::getInstance()->getUnits_result()->deadPolice >= 1)
	//   //   finish_sprite->setColor(Color3B::RED);
	//   //else if (SelectUnit::getInstance()->getUnits_result()->nodiePolice >= 1)
	//   //   finish_sprite->setColor(Color3B::YELLOW);


	//   finish_sprite->setPosition(Vec2(640, 460));
	//   finish_layer->addChild(finish_sprite, 99);

	//   MenuItemImage* menuitemiamge[3];

	//   char filename[3][2][50] =
	//   {
	//      { "finish/result next.png","finish/result next pressed.png" },
	//      { "finish/result retry.png", "finish/result retry pressd.png" },
	//      { "finish/result exit.png", "finish/result exit pressed.png" },
	//   };

	//   for (int i = 0; i < 3; i++)
	//   {

	//      menuitemiamge[i] = MenuItemImage::create(filename[i][0], filename[i][1], CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	//      menuitemiamge[i]->setTag(i + 100);
	//      menuitemiamge[i]->setPosition(Vec2(50 + i * menuitemiamge[i]->getContentSize().width, 0));
	//   }

	//   Menu* menu = Menu::create(menuitemiamge[0], menuitemiamge[1], menuitemiamge[2], nullptr);
	//   menu->setPosition(Vec2::ZERO);
	//   finish_sprite->addChild(menu, 100);



	//   for (int i = 0; i < 4; i++)
	//   {
	//      int tmp[4] = {
	//         SelectUnit::getInstance()->getUnits_result()->nodieCitizen,
	//         SelectUnit::getInstance()->getUnits_result()->deadCitizen,
	//         SelectUnit::getInstance()->getUnits_result()->nodiePolice,
	//         SelectUnit::getInstance()->getUnits_result()->deadPolice,
	//      };



	//      if (tmp[i] > 9)
	//      {
	//         Sprite* numberChar = Sprite::create(StringUtils::format("number/wb%d.png", tmp[i] / 10));
	//         numberChar->setAnchorPoint(Vec2(0, 0));
	//         numberChar->setScale(1.5f);
	//         numberChar->setPosition(Vec2(475, 245 - 32 * i));
	//         finish_sprite->addChild(numberChar);


	//         Sprite* numberChar_1 = Sprite::create(StringUtils::format("number/wb%d.png", tmp[i] % 10));
	//         numberChar_1->setAnchorPoint(Vec2(0, 0));
	//         numberChar_1->setScale(1.5f);
	//         numberChar_1->setPosition(Vec2(475 + numberChar->getContentSize().width + 10, 245 - 32 * i));
	//         finish_sprite->addChild(numberChar_1);
	//      }
	//      else
	//      {
	//         Sprite* numberChar = Sprite::create(StringUtils::format("number/wb%d.png", tmp[i]));
	//         numberChar->setAnchorPoint(Vec2(0, 0));
	//         numberChar->setScale(1.5f);
	//         numberChar->setPosition(Vec2(475, 245 - 32 * i));
	//         finish_sprite->addChild(numberChar);
	//      }
	//   }
	//   ranking(1, finish_sprite);
	//   into = false;
	//}
}

//void InGame::finish()
//{
//	static bool into = true;
//	bool into_[2] = { true, true };
//
//	for (int i = 0;i < UnitsAddress::getInstance()->getMaxUnitsnum();i++)
//	{
//		if (UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i) != nullptr)
//			into_[0] = false;
//	}
//
//	for (int i = 0; i < UnitsAddress::getInstance()->getMaxUnitsnum(); i++)
//	{
//		if (UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i) != nullptr)
//			into_[1] = false;
//	}
//
//
//
//	if (!into)
//		return;
//
//	if (into_[0])
//	{
//		LayerColor* finish_layer = LayerColor::create(Color4B::BLACK);
//		finish_layer->setOpacity(100);
//		finish_layer->setPosition(Vec2(*SelectUnit::getInstance()->getMovedXpos(), 0));
//		layer->addChild(finish_layer,10);
//
//		Sprite* finish_sprite = Sprite::create("finish/finish_popup.png");
//
//		//if (SelectUnit::getInstance()->getUnits_result()->deadCitizen >= 1)
//		//	finish_sprite->setColor(Color3B::RED);
//		//else if (SelectUnit::getInstance()->getUnits_result()->nodieCitizen >= 1)
//		//	finish_sprite->setColor(Color3B::YELLOW);
//
//
//		finish_sprite->setPosition(Vec2(640, 460));
//		finish_layer->addChild(finish_sprite, 99);
//
//		MenuItemImage* menuitemiamge[3];
//
//		char filename[3][2][50] =
//		{
//			{"finish/result next.png","finish/result next pressed.png"},
//			{"finish/result retry.png", "finish/result retry pressd.png"},
//			{"finish/result exit.png", "finish/result exit pressed.png"},
//		};
//
//		for (int i = 0; i < 3; i++)
//		{
//
//			menuitemiamge[i] = MenuItemImage::create(filename[i][0], filename[i][1], CC_CALLBACK_1(InGame::menuCloseCallback, this));
//			menuitemiamge[i]->setTag(i + 100);
//			menuitemiamge[i]->setPosition(Vec2(50 + i * menuitemiamge[i]->getContentSize().width, 0));
//		}
//		
//		Menu* menu = Menu::create(menuitemiamge[0], menuitemiamge[1], menuitemiamge[2], nullptr);
//		menu->setPosition(Vec2::ZERO);
//		finish_sprite->addChild(menu, 100);
//
//
//
//
//
//
//
//
//		for (int i = 0; i < 4; i++)
//		{
//			int tmp[4] = {
//				SelectUnit::getInstance()->getUnits_result()->nodieCitizen,
//				SelectUnit::getInstance()->getUnits_result()->deadCitizen,
//				SelectUnit::getInstance()->getUnits_result()->nodiePolice,
//				SelectUnit::getInstance()->getUnits_result()->deadPolice,
//			};
//
//			if (tmp[i] > 9)
//			{
//				Sprite* numberChar = Sprite::create(StringUtils::format("number/wb%d.png", tmp[i] / 10));
//				numberChar->setAnchorPoint(Vec2(0, 0));
//				numberChar->setScale(1.5f);
//				numberChar->setPosition(Vec2(475, 245 - 32 * i));
//				finish_sprite->addChild(numberChar);
//
//
//				Sprite* numberChar_1 = Sprite::create(StringUtils::format("number/wb%d.png", tmp[i] % 10));
//				numberChar_1->setAnchorPoint(Vec2(0, 0));
//				numberChar_1->setScale(1.5f);
//				numberChar_1->setPosition(Vec2(475 + numberChar->getContentSize().width + 10, 245 - 32 * i));
//				finish_sprite->addChild(numberChar_1);
//			}
//			else
//			{
//				Sprite* numberChar = Sprite::create(StringUtils::format("number/wb%d.png", tmp[i]));
//				numberChar->setAnchorPoint(Vec2(0, 0));
//				numberChar->setScale(1.5f);
//				numberChar->setPosition(Vec2(475, 245 - 32 * i));
//				finish_sprite->addChild(numberChar);
//			}
//		}
//		ranking(1, finish_sprite);
//		into = false;
//	}
//
//	if (into_[1])
//	{
//		LayerColor* finish_layer = LayerColor::create(/*Color4B::RED*/);
//		finish_layer->setOpacity(100);
//		finish_layer->setPosition(Vec2(*SelectUnit::getInstance()->getMovedXpos(), 0));
//		layer->addChild(finish_layer, 10);
//
//		Sprite* finish_sprite = Sprite::create("finish/finish_popup.png");
//
//		//if (SelectUnit::getInstance()->getUnits_result()->deadPolice >= 1)
//		//	finish_sprite->setColor(Color3B::RED);
//		//else if (SelectUnit::getInstance()->getUnits_result()->nodiePolice >= 1)
//		//	finish_sprite->setColor(Color3B::YELLOW);
//
//
//		finish_sprite->setPosition(Vec2(640, 460));
//		finish_layer->addChild(finish_sprite, 99);
//
//		MenuItemImage* menuitemiamge[3];
//
//		char filename[3][2][50] =
//		{
//			{ "finish/result next.png","finish/result next pressed.png" },
//			{ "finish/result retry.png", "finish/result retry pressd.png" },
//			{ "finish/result exit.png", "finish/result exit pressed.png" },
//		};
//
//		for (int i = 0; i < 3; i++)
//		{
//
//			menuitemiamge[i] = MenuItemImage::create(filename[i][0], filename[i][1], CC_CALLBACK_1(InGame::menuCloseCallback, this));
//			menuitemiamge[i]->setTag(i + 100);
//			menuitemiamge[i]->setPosition(Vec2(50 + i * menuitemiamge[i]->getContentSize().width, 0));
//		}
//
//		Menu* menu = Menu::create(menuitemiamge[0], menuitemiamge[1], menuitemiamge[2], nullptr);
//		menu->setPosition(Vec2::ZERO);
//		finish_sprite->addChild(menu, 100);
//
//
//
//		for (int i = 0; i < 4; i++)
//		{
//			int tmp[4] = {
//				SelectUnit::getInstance()->getUnits_result()->nodieCitizen,
//				SelectUnit::getInstance()->getUnits_result()->deadCitizen,
//				SelectUnit::getInstance()->getUnits_result()->nodiePolice,
//				SelectUnit::getInstance()->getUnits_result()->deadPolice,
//			};
//
//
//
//			if (tmp[i] > 9)
//			{
//				Sprite* numberChar = Sprite::create(StringUtils::format("number/wb%d.png", tmp[i] / 10));
//				numberChar->setAnchorPoint(Vec2(0, 0));
//				numberChar->setScale(1.5f);
//				numberChar->setPosition(Vec2(475, 245 - 32 * i));
//				finish_sprite->addChild(numberChar);
//
//
//				Sprite* numberChar_1 = Sprite::create(StringUtils::format("number/wb%d.png", tmp[i] % 10));
//				numberChar_1->setAnchorPoint(Vec2(0, 0));
//				numberChar_1->setScale(1.5f);
//				numberChar_1->setPosition(Vec2(475 + numberChar->getContentSize().width + 10, 245 - 32 * i));
//				finish_sprite->addChild(numberChar_1);
//			}
//			else
//			{
//				Sprite* numberChar = Sprite::create(StringUtils::format("number/wb%d.png", tmp[i]));
//				numberChar->setAnchorPoint(Vec2(0, 0));
//				numberChar->setScale(1.5f);
//				numberChar->setPosition(Vec2(475, 245 - 32 * i));
//				finish_sprite->addChild(numberChar);
//			}
//		}
//		ranking(1, finish_sprite);
//		into = false;
//	}
//}

void InGame::ranking(int rank,Sprite* sprite_)
{
	int num[] = { 31,26,1,1 };

	Animation* animation = Animation::create();
	for (int i = 0; i < num[rank]; i++)
		animation->addSpriteFrameWithFile(StringUtils::format("rank/%d/sprite_%d.png", rank, i + 1));
	animation->setDelayPerUnit(0.1f);

	Animate* animate = Animate::create(animation);
	
	Sprite* sprite = Sprite::create("test.png");
	sprite->setPosition(Vec2(150,150)/*(640,360)*/);
	sprite->runAction(RepeatForever::create(animate));
	sprite->setScale(1.5f);

	sprite_->addChild(sprite,100);
}

void InGame::uningItem(int itemType)
{
	LayerColor* tmplayer = LayerColor::create(Color4B::GREEN);

	switch (itemType)
	{
	case 0:

		tmplayer->setOpacity(120);
		tmplayer->setTag(20);
		this->addChild(tmplayer);


		for (int i = 0; i < UnitsAddress::getInstance()->getMaxUnitsnum(); i++)
		{
			if (UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i) == nullptr)
				continue;
			auto tmp = UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i);

			tmp->unitaddress->getStatus()->health = tmp->unitaddress->getStatus()->max_health;

		}
		this->runAction(Sequence::create(DelayTime::create(0.5f), CallFuncN::create([](Node* node) {node->removeChild(node->getChildByTag(20)); }), nullptr));

		break;
	default:
		break;
	}
}

void InGame::menuCloseCallback(Ref* pSender)
{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

	static int movenum = 0;

	switch (((Node*)pSender)->getTag())
	{
	case 0:
		if (movenum < 20)
		{
			layer->setPosition(Vec2(layer->getPosition().x + 128, layer->getPosition().y));
			*(SelectUnit::getInstance()->getMovedXpos()) -= 128;
			movenum += 1;
		}
		break;
	case 1:
		if (movenum > 0)
		{
			layer->setPosition(Vec2(layer->getPosition().x - 128, layer->getPosition().y));
			*(SelectUnit::getInstance()->getMovedXpos()) += 128;
			movenum -= 1;
		}
		break;
	default:
		break;
	}
}

bool InGame::onTouchBegan(Touch * touch, Event * unused_event)
{


	/*sprite__->setPosition(Vec2(sprite__->getPosition().x + (touch->getLocation().x - sprite__->getPosition().x) / 100.f, sprite__->getPosition().y + (touch->getLocation().y - sprite__->getPosition().y) / 100.f));*/


	//sprite__->runAction(MoveTo::create(0.1f, touch->getLocation()));






	/*for (int i = 0;i < 10;i++)
	{
		auto tmpUnit = &shieldunit[i];
		if (tmpUnit->getUnit()->getBoundingBox().containsPoint(touch->getLocation()))
		{
			tmpUnit->getUnit()->setOpacity(150);
			touchedunit = tmpUnit;
			log("you touch %d unit", i);
			return true;
		}
	}*/

	Vec2 realpos;
	realpos = touch->getLocation();
	realpos.x = realpos.x + *SelectUnit::getInstance()->getMovedXpos();

	for (int i = 0;i < UnitsAddress::getInstance()->getMaxUnitsnum();i++)
	{
		if (UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i) == nullptr)
			continue;

		auto tmpUnit = UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i)->unitaddress;
		if (tmpUnit->getUnit()->getBoundingBox().containsPoint(realpos))
		{
			tmpUnit->getUnit()->setOpacity(150);
			touchedunit = (Police*)tmpUnit;
			return true;
		}
	}

	return true;
}

void InGame::onTouchMoved(Touch * touch, Event * unused_event)
{
}

void InGame::onTouchEnded(Touch * touch, Event * unused_event)
{
	/*if (touchedunit != nullptr)
	{
		for (int i = 0;i < 10;i++)
		{
			auto tmpUnit = &shieldunit[i];
			if (touchedunit != tmpUnit && tmpUnit->getUnit()->getBoundingBox().containsPoint(touch->getLocation()))
			{
				touchedunit->getCompanion(tmpUnit);
				log("Companion with %d unit", i);
			}
		}


		touchedunit->getUnit()->setOpacity(255);

		touchedunit->moveUnit(touch->getLocation());

	}
*/

	Vec2 realpos;
	realpos = touch->getLocation();
	realpos.x = realpos.x + *SelectUnit::getInstance()->getMovedXpos();

	if (touchedunit != nullptr)
	{
		for (int i = 0;i < UnitsAddress::getInstance()->getMaxUnitsnum();i++)
		{
			if (UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i) == nullptr || touchedunit == UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i)->unitaddress)
				continue;


			if (!(touchedunit->getCompanion()->haveCompanion) && UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i)->unitaddress->getUnit()->getBoundingBox().containsPoint(realpos))
				touchedunit->getCompanion((Police*)UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i)->unitaddress);
			else if (touchedunit->getCompanion()->haveCompanion && UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i)->unitaddress->getUnit()->getBoundingBox().containsPoint(realpos))
			{
				touchedunit->getCompanion()->companionUnit->getCompanion()->haveCompanion = false;
				touchedunit->getCompanion()->companionUnit->getCompanion()->companionUnit = nullptr;

				touchedunit->getCompanion()->haveCompanion = false;
				touchedunit->getCompanion()->companionUnit = nullptr;

				touchedunit->getUnit()->setOpacity(255);
				return;
			}
		}

		touchedunit->getUnit()->setOpacity(255);

		touchedunit->moveUnit(realpos);

		touchedunit = nullptr;
	}
}

void InGame::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{

	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_PAUSE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SCROLL_LOCK:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_PRINT:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SYSREQ:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_BREAK:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
		break;
	//case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
	//	break;
	case cocos2d::EventKeyboard::KeyCode::KEY_BACKSPACE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_TAB:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_BACK_TAB:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RETURN:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPS_LOCK:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SHIFT:
		break;
	//case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
	//	break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CTRL:
		break;
	//case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_CTRL:
	//	break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_CTRL:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_ALT:
		break;
	//case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ALT:
	//	break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ALT:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_MENU:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_HYPER:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_INSERT:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_HOME:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_PG_UP:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DELETE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_END:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_PG_DOWN:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:

		layer->setPosition(Vec2(layer->getPosition().x + 128, layer->getPosition().y));
		*(SelectUnit::getInstance()->getMovedXpos()) -= 128;

		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:

		layer->setPosition(Vec2(layer->getPosition().x - 128, layer->getPosition().y));
		*(SelectUnit::getInstance()->getMovedXpos()) += 128;

		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_NUM_LOCK:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_PLUS:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_MINUS:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_MULTIPLY:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_DIVIDE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_ENTER:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_HOME:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_UP:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_PG_UP:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_LEFT:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_FIVE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_RIGHT:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_END:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_DOWN:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_PG_DOWN:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_INSERT:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_KP_DELETE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_F1:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_F2:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_F3:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_F4:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_F5:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_F6:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_F7:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_F8:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_F9:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_F10:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_F11:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_F12:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SPACE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_EXCLAM:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_QUOTE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_NUMBER:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DOLLAR:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_PERCENT:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CIRCUMFLEX:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_AMPERSAND:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_APOSTROPHE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_PARENTHESIS:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_PARENTHESIS:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_ASTERISK:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_PLUS:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_COMMA:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_MINUS:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_PERIOD:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SLASH:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_0:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_1:
		UnitsAddress::getInstance()->RunUnitsFunction(Vec2(2280, 360), UnitsAddress::POLICE, UnitsAddress::SHIELD, layer);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_2:
		UnitsAddress::getInstance()->RunUnitsFunction(Vec2(2280, 360), UnitsAddress::POLICE, UnitsAddress::BOTTON, layer);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_3:
		UnitsAddress::getInstance()->RunUnitsFunction(Vec2(2280, 360), UnitsAddress::POLICE, UnitsAddress::GUNNER, layer);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_4:
		UnitsAddress::getInstance()->RunUnitsFunction(Vec2(-1000, 360), UnitsAddress::CITIZEN, UnitsAddress::WEAK_PEOPLE, layer);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_5:
		UnitsAddress::getInstance()->RunUnitsFunction(Vec2(-1000, 360), UnitsAddress::CITIZEN, UnitsAddress::NORMAL_PEOPLE, layer);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_6:
		UnitsAddress::getInstance()->RunUnitsFunction(Vec2(-1000, 360), UnitsAddress::CITIZEN, UnitsAddress::STRONG_PEOPLE, layer);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_7:
		UnitsAddress::getInstance()->RunUnitsFunction(Vec2(-1000, 360), UnitsAddress::CITIZEN, UnitsAddress::SLINGSHOTER, layer);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_8:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_9:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_COLON:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SEMICOLON:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_LESS_THAN:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_EQUAL:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_GREATER_THAN:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_QUESTION:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_AT:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_A:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_B:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_C:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_D:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_E:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_F:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_G:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_H:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_I:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_J:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_K:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_L:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_M:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_N:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_O:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_P:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_Q:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_R:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_S:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_T:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_U:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_V:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_W:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_X:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_Y:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_CAPITAL_Z:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_BRACKET:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_BACK_SLASH:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_BRACKET:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_UNDERSCORE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_GRAVE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_A:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_B:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_C:

		for (int i = 0; i < UnitsAddress::getInstance()->getMaxUnitsnum(); i++)
		{
			auto unit = UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i);

			if (unit == nullptr)
				continue;

			((Citizen*)unit->unitaddress)->hittedUnit(99999999,0);
		}

		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_D:
		for (int i = 0;i < UnitsAddress::getInstance()->getMaxUnitsnum();i++)
		{
			if (UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i) == nullptr)
				return;

			auto tmp = UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i)->unitaddress;

			((Citizen*)tmp)->RunFunction();
		}

		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_E:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_F:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_G:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_H:
		uningItem(0);
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_I:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_J:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_K:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_L:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_M:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_N:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_O:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_P:

		for (int i = 0; i < UnitsAddress::getInstance()->getMaxUnitsnum(); i++)
		{
			auto unit = UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i);

			if (unit == nullptr)
				continue;

			((Police*)unit->unitaddress)->hittedUnit(99999999,0);
		}

		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_Q:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_R:
		(*SelectUnit::getInstance()->getMovedXpos()) = 1280;
		Director::getInstance()->replaceScene(Collocate::createScene());
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_S:
		for (int i = 0;i < UnitsAddress::getInstance()->getMaxUnitsnum();i++)
		{
			if (UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i) == nullptr)
				return;

			auto tmp = UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i)->unitaddress;

			tmp->getUnit()->cleanup();

		}
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_T:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_U:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_V:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_W:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_X:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_Y:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_Z:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_BRACE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_BAR:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_BRACE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_TILDE:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_EURO:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_POUND:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_YEN:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_MIDDLE_DOT:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_SEARCH:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_LEFT:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_RIGHT:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_UP:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_DOWN:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_DPAD_CENTER:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
		break;
	case cocos2d::EventKeyboard::KeyCode::KEY_PLAY:
		break;
	default:
		break;
	}
}

void InGame::time_later(float db)
{
	time_second -= 1;
	if (time_second == -1)
	{
		time_minute -= 1;
		time_second = 59;
	}
	show_time->setString(StringUtils::format("%d : %.2d", time_minute, time_second));
}

void InGame::option(Ref* pSender)
{
	for (MenuItemImage* item : Button_Vec)
	{
		item->setEnabled(false);
	}
	pauseSchedulerAndActions();
	option_layer->setVisible(true);
	for (int i = 0; i < UnitsAddress::getInstance()->getMaxUnitsnum(); i++)
	{
		if (UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i) == nullptr)
			return;

		auto tmp = UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i)->unitaddress;

		tmp->getUnit()->cleanup();

	}
}

void InGame::setting(Ref* pSender)
{
	sound_layer->setVisible(true);
	option_layer->setVisible(false);
	for (int i = 0; i < UnitsAddress::getInstance()->getMaxUnitsnum(); i++)
	{
		if (UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i) == nullptr)
			return;

		auto tmp = UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i)->unitaddress;

		tmp->getUnit()->cleanup();

	}
}

void InGame::restart(Ref* pSender)
{
	/*auto scene = TransitionFade::create(0.5, InGame::createScene());
	Director::getInstance()->replaceScene(scene);*/
}

void InGame::continue_play(Ref* pSender)
{
	for (MenuItemImage* item : Button_Vec)
	{
		item->setEnabled(true);
	}
	resumeSchedulerAndActions();
	option_layer->setVisible(false);
	for (int i = 0; i < UnitsAddress::getInstance()->getMaxUnitsnum(); i++)
	{
		if (UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i) == nullptr)
			return;

		auto tmp = UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i)->unitaddress;
		
		((Citizen*)tmp)->RunFunction();

	}
}

void InGame::go_to_menu(Ref* pSender)
{
	confirm_layer->setVisible(true);
}

void InGame::confirm_c_yes(Ref* pSender)
{
	auto scene = TransitionFade::create(2.0, MapChoice::createScene());
	Director::getInstance()->replaceScene(scene);
}

void InGame::confirm_c_no(Ref* pSender)
{
	confirm_layer->setVisible(false);
}

void InGame::sound_close(Ref* pSender)
{
	sound_layer->setVisible(false);
	option_layer->setVisible(true);
}

void InGame::music_control(Ref* pSender)
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

void InGame::effect_control(Ref* pSender)
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

void InGame::sound_check(float df)
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
