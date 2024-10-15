#pragma once
#include "cocos2d.h"

USING_NS_CC;

class SelectUnit
{
public:
	struct Unitnum
	{
		int shield = 0;
		int botton = 0;
		int gunner = 1;

		int maxunit = 1;
	};

	struct Units_Result
	{
		int deadCitizen = 0;
		int nodieCitizen = 0;
		int deadPolice = 0;
		int nodiePolice = 0;
	};
	struct Unitvec
	{
		Vec2* shield;
		Vec2* botton;
		Vec2* gunner;
	};
	struct StageMap
	{
		int stage;
		int map;
	};
	struct Item
	{
		int heal_price = 300;
		int sprinkler_price = 700;
		int item = 0;
	};
	struct ItemBuy
	{
		Item sprinkler;
		Item firebomb;
		int money = 10000;
	};
	struct Collect
	{
		//char image
	};

	struct Sound
	{
		bool Music = true;
		bool Effect = true;
	};
public:
	SelectUnit();
	~SelectUnit();

	static SelectUnit* getInstance();

	Unitnum* getUnitnum();
	Unitvec* getUnitvec();
	StageMap* getStageMap();
	Sound* getSound();
	ItemBuy* getitembuy();
	Units_Result* getUnits_result();
	void vecCreate();

	int* getMovedXpos();


private:
	static SelectUnit* instance;
	Unitnum* unitnum;
	Unitvec* unitvec;
	StageMap* stagemap;
	Sound* sound;
	ItemBuy* itembuy;
	Units_Result* units_result;	

	int movedXpos = 1280;
};