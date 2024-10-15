#include "UnitsAddress.h"
#include "Control.h"
#include "PoliceUnits.h"
#include "CitizenUnits.h"


UnitsAddress* UnitsAddress::instance = nullptr;

UnitsAddress::UnitsAddress()
{
	unitsaddress = new Units[maxUnitsnum];

	unitsaddress[0].type = END;
	unitsaddress[0].unitaddress = nullptr;
}

UnitsAddress::~UnitsAddress()
{
}

UnitsAddress * UnitsAddress::getInstance()
{
	if (instance == nullptr)
		instance = new UnitsAddress;


	return instance;
}

UnitsAddress::Units * UnitsAddress::getUnits(int type, int num)
{
	int typenum = 0;
	for (int i = 0;i < maxUnitsnum;i++)
	{
		if (unitsaddress[i].type == type)
		{
			if (typenum == num)
				return &unitsaddress[i];
			typenum += 1;
		}
	}

	return nullptr;
}

Unit* UnitsAddress::RunUnitsFunction(Vec2 pos, int type, int detail, Layer* layer)
{
	Unit* tmpunit;


	switch (detail)
	{
	case SHIELD:
		tmpunit = new ShieldUnit;
		break;
	case BOTTON:
		tmpunit = new BottonUnit;
		break;
	case GUNNER:
		tmpunit = new GunnerUnit;
		break;
	case WEAK_PEOPLE:
		tmpunit = new People;
		((People*)tmpunit)->setType(WEAK_PEOPLE);
		break;
	case NORMAL_PEOPLE:
		tmpunit = new People;
		((People*)tmpunit)->setType(NORMAL_PEOPLE);
		break;
	case STRONG_PEOPLE:
		tmpunit = new People;
		((People*)tmpunit)->setType(STRONG_PEOPLE);
		break;
	case SLINGSHOTER:
		tmpunit = new Slingshoter;
		break;
	default:
		return nullptr;
		break;
	}


	tmpunit->createUnit("", pos, layer);
	AddUnit(tmpunit, type);
	//tmpunit->Animateinit(layer);

	if (type == CITIZEN)
	{
		((Citizen*)tmpunit)->RunFunction();
	}
	else if (type == POLICE)
	{
		((Police*)tmpunit)->getUnit()->runAction(RepeatForever::create(((ActionInterval*)CallFunc::create([tmpunit]() {tmpunit->attackUnit();}))));
	}

	return tmpunit;
}

bool UnitsAddress::searchUnit(Unit * address)
{
	for (int i = 0;i < maxUnitsnum;i++)
	{
		if (address == unitsaddress[i].unitaddress)
			return true;
	}

	return false;
}

int UnitsAddress::searchUnitnum(Unit * address)
{
	for (int i = 0;i < maxUnitsnum;i++)
	{
		if (address == unitsaddress[i].unitaddress)
			return i;
	}

	return -1;
}

void UnitsAddress::AddUnit(Unit * unit, int type)
{
	maxUnitsnum += 1;

	Units* tmp = new Units[maxUnitsnum];

	for (int i = 0;i < maxUnitsnum - 1;i++)
	{
		tmp[i].type = unitsaddress[i].type;
		tmp[i].unitaddress = unitsaddress[i].unitaddress;
	}

	delete[] unitsaddress;

	unitsaddress = tmp;
	/*

	for (int i = 0;i < maxUnitsnum;i++)
	{
	unitsaddress[i].type = tmp[i].type;
	unitsaddress[i].unitaddress = tmp[i].unitaddress;
	}*/

	unitsaddress[maxUnitsnum - 2].unitaddress = unit;
	unitsaddress[maxUnitsnum - 2].type = type;

	unitsaddress[maxUnitsnum - 1].unitaddress = nullptr;
	unitsaddress[maxUnitsnum - 1].type = END;

	//delete(tmp);
}

void UnitsAddress::deleteUnit(Unit * address)
{
	Units* deleteunit = nullptr;

	for (int i = 0;i < maxUnitsnum;i++)
	{
		if (unitsaddress[i].unitaddress == address)
		{
			deleteunit = &unitsaddress[i];
			unitsaddress[i].type = DELETE;
			maxUnitsnum -= 1;
			deleteunit->unitaddress->hpbarRemove();
			break;
		}
	}

	if (deleteunit == nullptr)
		return;

	Units* tmp = new Units[maxUnitsnum];
	int num = 0;
	for (int i = 0;i < maxUnitsnum;i++)
	{
		if (unitsaddress[i].type == DELETE)
			num = 1;


		tmp[i].type = unitsaddress[i + num].type;
		tmp[i].unitaddress = unitsaddress[i + num].unitaddress;
	}

	delete[] unitsaddress;

	unitsaddress = tmp;
	/*
	for (int i = 0;i < maxUnitsnum;i++)
	{
	unitsaddress[i].type = tmp[i].type;
	unitsaddress[i].unitaddress = tmp[i].unitaddress;
	}*/
	
}

int UnitsAddress::getMaxUnitsnum()
{
	return maxUnitsnum;
}