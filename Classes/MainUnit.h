#pragma once
#include "cocos2d.h"

USING_NS_CC;

#define TEST 0


class Unit
{
public:

	struct Status
	{
		float attack_range;
		float attack_power;
		float attack_speed;
		
		float health;
		float max_health;
		float shield_point;
		
		float speed;
		
		bool canRunF = true;
	};
public:
	Unit();
	~Unit();

	void hpbarCreate();
	void hpbarUpdate();
	void hpbarRemove();

	virtual void createUnit(char* SpriteName, Vec2 pos, Layer* layer);	//create Sprite & addChild & store address of layer


	float attackRange(Sprite* sprite, float Range, bool checkRange = false);	//Check if there is a conflict with connected Sprite

	virtual void hittedUnit(float hitdamage);

	virtual void attackUnit();

	virtual void standAnimation(int direction);		//stand runAcion
	virtual void moveAnimation(int direction, Vec2 movepos);		//mvoe runAction
	virtual void attackAnimation(int direction);		//attack runAction
	virtual void hittedAnimation(int direction);		//hitted runAction
	virtual void deadAnimation(int direction);			//dead runAction

	virtual void Animateinit(Layer* layer);

	//void status


	Sprite* getUnit();		//get the address of Police
	Status* getStatus();		//get the address of Status
	Layer* getMainlayer();


private:
	LayerColor* healthbar;

	Sprite* unit;
	Status* status;
	Layer* mainlayer;
};



class Police : public Unit
{
public:
	struct Companion
	{
		bool haveCompanion = false;
		Police* companionUnit = nullptr;
	};

public:
	Police();
	~Police();


	void getCompanion(Police* CompanionUnit);		//Store the address of Companion

	virtual void attackUnit();

	void moveUnit(Vec2 movepos, bool canCompanionMove = true);		//Move Police to movepos (use MoveTo) & with Companion & Call moveAnimation

	virtual void hittedUnit(float hitdamage, int direction);

	virtual void standAnimation(int direction);		//stand runAcion
	virtual void moveAnimation(int direction, Vec2 movepos);		//mvoe runAction
	virtual void attackAnimation(int direction);		//attack runAction
	virtual void hittedAnimation(int direction);		//hitted runAction

	Companion* getCompanion();		//get the address of Companion

private:
	bool delay = true;

	Companion* companion;
};




class Citizen : public Unit
{ 
public:
	struct Closest
	{
		float closest = 0;
		Police* closestPolice = 0;
	};
public:
	Citizen();
	~Citizen();


	void RunFunction();

	virtual void attackUnit(Closest _closest);

	void moveUnit();		//The nearest move after confirming the police

	virtual void hittedUnit(float hitdamage, int direction);

	virtual void deadAnimation(int direction);
	virtual void standAnimation(int direction);		//stand runAcion
	virtual void moveAnimation(int direction, Vec2 movepos);		//mvoe runAction
	virtual void attackAnimation(int direction);		//attack runAction
	virtual void hittedAnimation(int direction);		//hitted runAction

	
protected:
	bool delay = true;


	Sequence* movetoAction = nullptr;
	RepeatForever* LeftmoveAction;
	RepeatForever* RigthmoveAction;
	RepeatForever* standAction;
	Animate* LeftdeadAction;
	Animate* RightdeadAction;
	Animate* LefthittedAction;
	Animate* RighthittedAction;
	Animate* LeftattackAction;
	Animate* RightattackAction;
	RepeatForever* nowRunAction;
};