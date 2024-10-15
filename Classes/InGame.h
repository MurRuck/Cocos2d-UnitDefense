#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "MainUnit.h"
#include "PoliceUnits.h"
#include "CitizenUnits.h"

USING_NS_CC;

class InGame : public cocos2d::Layer
{
public:
	LayerColor* layer;
	/*ShieldUnit shieldunit[10];*/
	LayerColor* time_over;

	LayerColor* option_layer;

	LayerColor* sound_layer;

	LayerColor* confirm_layer;

	Sprite* test;

	Sprite* sprite__;

	People* citizen;

	Police* touched[3];

	Police* touchedunit;

	Label* show_time;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void update(float dt);
	void time_later(float db);
	void sound_check(float df);
	Vector<MenuItemImage*> Button_Vec;

	void finish();
	void ranking(int rank,Sprite* sprite_);

	void uningItem(int itemType);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void option(cocos2d::Ref* pSender);
	void confirm_c_yes(cocos2d::Ref* pSender);
	void confirm_c_no(cocos2d::Ref* pSender);
	void go_to_menu(cocos2d::Ref* pSender);
	void continue_play(cocos2d::Ref* pSender);
	void setting(cocos2d::Ref* pSender);
	void restart(cocos2d::Ref* pSender);
	void sound_close(cocos2d::Ref* pSender);
	void music_control(cocos2d::Ref* pSender);
	void effect_control(cocos2d::Ref* pSender);

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	virtual void onTouchMoved(Touch *touch, Event *unused_event);
	virtual void onTouchEnded(Touch *touch, Event *unused_event);

	

	int time_minute = 5;
	int time_second = 0;


	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(InGame);
};

#endif // __HELLOWORLD_SCENE_H__
