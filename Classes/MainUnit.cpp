#include "MainUnit.h"
#include "Control.h"
#include "UnitsAddress.h"

//Main Unit Function
Unit::Unit()
{
	status = new Status;
}

Unit::~Unit()
{
}

void Unit::hpbarCreate()
{
	healthbar = LayerColor::create(Color4B::RED);
	healthbar->setAnchorPoint(Vec2(0.5f, 0.5f));
	healthbar->setPosition(Vec2(unit->getPosition().x - 10, unit->getPosition().y - 35));
	healthbar->setContentSize(Size(30, 3));
	mainlayer->addChild(healthbar);

	healthbar->runAction(RepeatForever::create((ActionInterval*)CallFunc::create([&]() {hpbarUpdate();})));
}

void Unit::hpbarUpdate()
{
	//((status->health / health) * 10) * 3
	//healthbar->setPosition(Vec2(unit->getPosition().x - 10, unit->getPosition().y - 35));
	healthbar->setPosition(Vec2(unit->getPosition().x - 10, unit->getPosition().y - 35));
	healthbar->setContentSize(Size(((status->health / status->max_health) * 10) * 3, 3));
}

void Unit::hpbarRemove()
{
	healthbar->getParent()->removeChild(healthbar);
}

void Unit::createUnit(char* SpriteName,Vec2 pos, Layer * layer)
{
	unit = Sprite::create(/*SpriteName*/);
	unit->setPosition(pos);
	layer->addChild(unit);

	unit->setScale(1.5f);

	mainlayer = layer;
	Animateinit(layer);

	hpbarCreate();
	standAnimation(0);
}


float Unit::attackRange(Sprite* sprite, float Range, bool checkRange)
{
	float Check = 0;

	if (unit == nullptr || sprite == nullptr)
		return false;

	float degree = atan2(unit->getPosition().y - sprite->getPosition().y, sprite->getPosition().x - unit->getPosition().x) * 180 / 3.1415926535;
	float length = sqrt(pow((unit->getPosition().x - sprite->getPosition().x), 2) + pow((unit->getPosition().y - sprite->getPosition().y), 2));

	if (length < Range)
	{
		Check = length;
	}
	else
		if (checkRange)
			Check = length;


	return Check;
}

void Unit::hittedUnit(float hitdamage)
{
}

void Unit::attackUnit()
{
}

void Unit::standAnimation(int direction)
{
}

void Unit::moveAnimation(int direction, Vec2 movepos)
{
}

void Unit::attackAnimation(int direction)
{
}

void Unit::hittedAnimation(int direction)
{
}

void Unit::deadAnimation(int direction)
{
}

void Unit::Animateinit(Layer * layer)
{
}

Sprite * Unit::getUnit()
{
	if (this == nullptr)
		return nullptr;
	return unit;
}

Unit::Status * Unit::getStatus()
{
	return status;
}

Layer * Unit::getMainlayer()
{
	return mainlayer;
}



//Police function
Police::Police()
{
	companion = new Companion;
}

Police::~Police()
{
}

void Police::getCompanion(Police * CompanionUnit)
{
	if (this == nullptr || CompanionUnit == nullptr)
		return;

	if (CompanionUnit != this && CompanionUnit->getCompanion()->haveCompanion == false && companion->haveCompanion == false)
	{
		//if (companion->companionUnit != nullptr || CompanionUnit->getCompanion() != nullptr)
		//	return;


		CompanionUnit->getCompanion()->haveCompanion = true;
		companion->haveCompanion = true;
		CompanionUnit->getCompanion()->companionUnit = this;
		companion->companionUnit = CompanionUnit;


		CompanionUnit->moveUnit(Vec2(getUnit()->getPosition().x + 50, getUnit()->getPosition().y), false);


		if(TEST) log("Companion  with (Ang?) unit");
	}
}

void Police::attackUnit()
{

	if (getStatus()->canRunF && delay)
	{
		Citizen* citizen = nullptr;
		float range;
		for (int i = 0;i < UnitsAddress::getInstance()->getMaxUnitsnum();i++)
		{
			auto tmp = UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i);

			if (tmp == nullptr)
				continue;

			if (attackRange(tmp->unitaddress->getUnit(), getStatus()->attack_range))
			{
				if (attackRange(tmp->unitaddress->getUnit(), getStatus()->attack_range) < getStatus()->attack_range)
				{
					citizen = (Citizen*)tmp->unitaddress;
					range = attackRange(tmp->unitaddress->getUnit(), getStatus()->attack_range);
				}
			}
		}

		if (citizen == nullptr)
			return;


		attackAnimation(citizen->getUnit()->getPosition().x - getUnit()->getPosition().x);

		if (citizen->getUnit()->getPosition().x - getUnit()->getPosition().x > 0)
			citizen->hittedUnit(getStatus()->attack_power, 1);
		else
			citizen->hittedUnit(getStatus()->attack_power, -1);


		getUnit()->runAction(Sequence::create(DelayTime::create(getStatus()->attack_speed), CallFunc::create([&]() {delay = true;}), nullptr));

		delay = false;
		getStatus()->canRunF = false;
	}

}

void Police::moveUnit(Vec2 movepos, bool canCompanionMove)
{
	if (getStatus()->canRunF)
	{

		if (companion->haveCompanion && canCompanionMove)
		{
			companion->companionUnit->moveUnit(Vec2(movepos.x + 50, movepos.y), false);
		}

		if (companion->haveCompanion && (!companion->companionUnit->getStatus()->canRunF || !getStatus()->canRunF))
			return;




		moveAnimation(movepos.x - getUnit()->getPosition().x, movepos);
	}
}

void Police::hittedUnit(float hitdamage, int direction)
{
	//데미지 - (데미지*(방어도/100))
	//방어도-(입은 데미지/10)

	getStatus()->health -= (hitdamage - (hitdamage * (getStatus()->shield_point / 100)));
	getStatus()->shield_point = (getStatus()->shield_point - (getStatus()->shield_point / 10));

	if (getStatus()->shield_point < 0)
		getStatus()->shield_point = 0;

	//log("Police's hittedUnit damage = %f", hitdamage);
	//log("Police's health = %f", getStatus()->health);
	//if (UnitsAddress::getInstance()->searchUnitnum(this) != -1)
	//	log("Police's %d\n\n", UnitsAddress::getInstance()->searchUnit(this));
	//else
	//	log("Police's no Search\n\n");


	if (getStatus()->health > 0)
	{
		if(direction < 0)
			getUnit()->runAction(Place::create(Vec2(getUnit()->getPosition().x - 20, getUnit()->getPosition().y)));
		else
			getUnit()->runAction(Place::create(Vec2(getUnit()->getPosition().x + 20, getUnit()->getPosition().y)));
	
		hittedAnimation(-direction);
	}
	else if (getStatus()->health <= 0)
	{
		if (getStatus()->health >= -8)
			SelectUnit::getInstance()->getUnits_result()->nodiePolice += 1;
		else
			SelectUnit::getInstance()->getUnits_result()->deadPolice += 1;

		deadAnimation(-direction);
		//getUnit()->setVisible(false);
		getUnit()->setTag(100);
		//getUnit()->getParent()->removeChild(getUnit());
		UnitsAddress::getInstance()->deleteUnit(this);
	}
}

void Police::standAnimation(int direction)
{
}

void Police::moveAnimation(int direction, Vec2 movepos)
{
}

void Police::attackAnimation(int direction)
{
}

void Police::hittedAnimation(int direction)
{
}

Police::Companion * Police::getCompanion()
{
	if (this == nullptr)
		return nullptr;
	return companion;
}



//main Citizen function
Citizen::Citizen()
{
	getStatus()->health = 150;
}

Citizen::~Citizen()
{
}


void Citizen::RunFunction()
{
	getUnit()->runAction(RepeatForever::create(Sequence::create(DelayTime::create(0.5f), CallFuncN::create([&](Node* node) {this->moveUnit();}), nullptr)));
}

void Citizen::attackUnit(Closest _closest)
{
	if (getStatus()->canRunF && delay)
	{
		struct Lamda
		{
			Closest clo;
			Status* sta;
		};

		Closest closest;
		closest = _closest;
		//for (int i = 0;i < UnitsAddress::getInstance()->getMaxUnitsnum();i++)									//가장 가까운 경찾 찾기
		//{																										//
		//	auto tmp = UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i);							//
		//																										//
		//	if (tmp == nullptr)																					//
		//		continue;																						//
		//																										//
		//	float range = attackRange(tmp->unitaddress->getUnit(), getStatus()->attack_range, true);			//
		//																										//
		//	if (range != 0 && (closest.closest == 0 || closest.closest > range))								//
		//	{																									//
		//		closest.closestPolice = (Police*)tmp->unitaddress;												//
		//		closest.closest = range;																		//
		//	}																									//
		//}																										//

		Lamda lamda;
		lamda.clo = closest;
		lamda.sta = getStatus();

		if (closest.closestPolice == nullptr) return;															//가까운게 없을 시 리턴


		if (getStatus()->attack_range > closest.closest)															//경찰이 공격범위에 들어왔을시
		{
			attackAnimation(closest.closestPolice->getUnit()->getPosition().x - getUnit()->getPosition().x); 



			getUnit()->runAction(Sequence::create(DelayTime::create(1.1f), CallFuncN::create([lamda](Node* node) {
																									if (lamda.clo.closestPolice->getUnit()->getPosition().x - node->getPosition().x > 0 /*&& getStatus()->canRunF == false*/)
																										lamda.clo.closestPolice->hittedUnit(lamda.sta->attack_power, 1);
																									else if(lamda.clo.closestPolice->getUnit()->getPosition().x - node->getPosition().x < 0/* && getStatus()->canRunF == false*/)
																										lamda.clo.closestPolice->hittedUnit(lamda.sta->attack_power, -1);
			}), nullptr));



			getUnit()->runAction(Sequence::create(DelayTime::create(getStatus()->attack_speed + 1.f), CallFunc::create([&]() {delay = true;}), nullptr));
			delay = false;
		}
	}
}

void Citizen::moveUnit()
{


	Closest closest;

	//static Closest best;

	for (int i = 0;i < UnitsAddress::getInstance()->getMaxUnitsnum();i++)									//가장 가까운 경찾 찾기
	{																										//
		auto tmp = UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i);							//
																											//
		if (tmp == nullptr)																					//
			continue;																						//
																											//
		float range = attackRange(tmp->unitaddress->getUnit(), getStatus()->attack_range, true);			//
																											//
		if (range != 0 && (closest.closest == 0 || closest.closest > range))								//
		{																									//
			closest.closestPolice = (Police*)tmp->unitaddress;												//
			closest.closest = range;																		//
		}																									//
	}																										//
	if (closest.closestPolice == nullptr) return;															//가까운게 없을 시 리턴

	//log("closest = %f", closest.closest);

	//if (best.closestPolice == closest.closestPolice)														//가장가까운 경찰이 움직였는지 확인
	//{																										//
	//	if (best.closest != closest.closest)																	//움직였는지 확인후 가까워 졌는지 확인
	//	{																									//
	//		best.closest = closest.closest;																	//
	//		best.closestPolice = closest.closestPolice;														//
	//	}																									//
	//	else return;																						//가까워 지지 않았을 시 리턴 
	//}																										//
	//else																									//가장 가까운 경찰유닛이 바뀌면 best에 유닛을 바꿈
	//{																										//
	//	best.closest = closest.closest;																		//
	//	best.closestPolice = closest.closestPolice;															//
	//}																										//




	if (closest.closest > getStatus()->attack_range)														//시민의 공격범위 안에 가장가까운 경찰 유닛이 있는지 확인
	{
		moveAnimation(closest.closestPolice->getUnit()->getPosition().x - getUnit()->getPosition().x, closest.closestPolice->getUnit()->getPosition());			//없을시 경찰이 움직임
	}
	else if (closest.closest < getStatus()->attack_range)													//있을시 경찰에게 공격함
	{																																			
		attackUnit(closest);
	}
}

void Citizen::hittedUnit(float hitdamage, int direction)
{												
																//데미지 - (데미지*(방어도/100))
																//방어도-(입은 데미지/10)

	getStatus()->health -= (hitdamage - (hitdamage * (getStatus()->shield_point / 100)));
	getStatus()->shield_point = (getStatus()->shield_point - (getStatus()->shield_point / 10));
	if (getStatus()->shield_point < 0)
		getStatus()->shield_point = 0;


	//log("Citizen's hittedUnit damage = %f", hitdamage);
	//log("Citizen's health = %f", getStatus()->health);

	if (getStatus()->health > 0)
	{

		if (direction < 0)
			getUnit()->runAction(Place::create(Vec2(getUnit()->getPosition().x - 20, getUnit()->getPosition().y)));
		else
			getUnit()->runAction(Place::create(Vec2(getUnit()->getPosition().x + 20, getUnit()->getPosition().y)));


		hittedAnimation(-direction);
	}
	else if (getStatus()->health <= 0)
	{
		if (getStatus()->health >= -8)
			SelectUnit::getInstance()->getUnits_result()->nodieCitizen += 1;
		else
			SelectUnit::getInstance()->getUnits_result()->deadCitizen += 1;



		deadAnimation(-direction);
		getUnit()->setVisible(false);
		//getUnit()->getParent()->removeChild(getUnit());
		getUnit()->stopAllActions();
		UnitsAddress::getInstance()->deleteUnit(this);
	}

}

void Citizen::deadAnimation(int direction)
{
}

void Citizen::standAnimation(int direction)
{

}

void Citizen::moveAnimation(int direction, Vec2 movepos)
{

}

void Citizen::attackAnimation(int direction)
{

}

void Citizen::hittedAnimation(int direction)
{
}
