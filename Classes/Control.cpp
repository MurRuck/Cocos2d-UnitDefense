#include "Control.h"

SelectUnit* SelectUnit::instance = nullptr;

SelectUnit::SelectUnit()
{
	unitnum = new Unitnum;
	unitvec = new Unitvec;
	stagemap = new StageMap;
	sound = new Sound;
	itembuy = new ItemBuy;
	units_result = new Units_Result;

	unitnum->maxunit = unitnum->botton + unitnum->gunner + unitnum->shield;
}

SelectUnit::~SelectUnit()
{
}

SelectUnit * SelectUnit::getInstance()
{
	if (instance == nullptr)
		instance = new SelectUnit;

	return instance;
}

SelectUnit::Unitnum * SelectUnit::getUnitnum()
{
	unitnum->maxunit = unitnum->botton + unitnum->gunner + unitnum->shield;

	return unitnum;
}

SelectUnit::Unitvec * SelectUnit::getUnitvec()
{
	return unitvec;
}
SelectUnit::StageMap * SelectUnit::getStageMap()
{
	return stagemap;
}

SelectUnit::Sound * SelectUnit::getSound()
{
	return sound;
}

SelectUnit::ItemBuy * SelectUnit::getitembuy()
{
	return itembuy;
}

SelectUnit::Units_Result * SelectUnit::getUnits_result()
{
	return units_result;
}

void SelectUnit::vecCreate()
{
	unitvec->shield = new Vec2[unitnum->shield];
	unitvec->botton = new Vec2[unitnum->botton];
	unitvec->gunner = new Vec2[unitnum->gunner];
}

int* SelectUnit::getMovedXpos()
{
	return &movedXpos;
}
