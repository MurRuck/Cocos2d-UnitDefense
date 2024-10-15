#pragma once
#pragma execution_character_set("utf-8")
#include "cocos2d.h"
#include "Map.h"
#include "store.h"
#include "Control.h"

USING_NS_CC;

class MenuScene : public cocos2d::Layer
{
public:
	MenuItemImage* Upgrade_Unit_Num[4];
	MenuItemImage* Reinforce_Unit_Num[3];
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	Sprite* Look_Unit;
	Sprite* ExplanationBackground;
	Label* Direction;
	
	Vector<MenuItemImage*> Button_Vec;

	LayerColor* PopUp_Layer_Color;
	LayerColor* Creater_Layer;

	void Setting(cocos2d::Ref* pSender);
	void Start(cocos2d::Ref* pSender);
	void PopUp_Layer_Back(cocos2d::Ref* pSender);
	void Shop(cocos2d::Ref* pSender);
	void Music(cocos2d::Ref* pSender);
	void Effect(cocos2d::Ref* pSender);
	void Creater_Button(Ref* pSender);
	void Creater_Layer_Back(cocos2d::Ref* pSender);
	// a selector callback

	void scheduleCallback(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(MenuScene);
};