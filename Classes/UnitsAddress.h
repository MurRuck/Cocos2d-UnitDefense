#pragma once
#include "cocos2d.h"
#include "MainUnit.h"



class UnitsAddress					//singleton	
{
public:
	enum
	{
		END,
		DELETE,
		POLICE,
		CITIZEN,
	};

	enum
	{
		SHIELD,
		BOTTON,
		GUNNER,
		//TEARTHROWER,
		WEAK_PEOPLE,
		NORMAL_PEOPLE,
		STRONG_PEOPLE,
		SLINGSHOTER,
	};

	struct Units
	{
		int type;
		int detailed_type;
		Unit* unitaddress;
	};

public:
	UnitsAddress();
	~UnitsAddress();

	static UnitsAddress* getInstance();

	Units* getUnits(int type, int num);
	Unit* RunUnitsFunction(Vec2 pos, int type, int detail, Layer* layer);		//유닛들 실행시켜야하는 함수 실행시키는 함수같은 함수일것같은 함수인가봐

	



	bool searchUnit(Unit* address);
	int searchUnitnum(Unit* address);

	void AddUnit(Unit* unit, int type);

	void deleteUnit(Unit* address);

	int getMaxUnitsnum();
private:
	static UnitsAddress* instance;

	Units* unitsaddress;
	int maxUnitsnum = 1;
};