#pragma once
#include "cocos2d.h"
#include "MainUnit.h"


class ShieldUnit : public Police
{
public:
	ShieldUnit()
	{
		getStatus()->health = 50;
		getStatus()->max_health = getStatus()->health;
		getStatus()->attack_range = 50;
		getStatus()->attack_speed = 3;
		getStatus()->attack_power = 18;
		getStatus()->shield_point = 100;
	}
	~ShieldUnit();


	//virtual void attackUnit();

	virtual void standAnimation(int direction);
	virtual void moveAnimation(int direction, Vec2 movepos);
	virtual void attackAnimation(int direction);
	virtual void hittedAnimation(int direction);
	virtual void deadAnimation(int direction);

	virtual void Animateinit(Layer* layer);
private:
	RepeatForever* LeftmoveAction;
	RepeatForever* RigthmoveAction;
	RepeatForever* standAction;
	Animate* LeftdeadAction;
	Animate* RightdeadAction;
	Animate* LefthittedAction;
	Animate* RighthittedAction;
	Animate* LeftattackAction;
	Animate* RightattackAction;
	Sequence* moveAction;
	RepeatForever* nowRunAction;
};


class BottonUnit : public Police
{
public:
	BottonUnit();
	~BottonUnit();


	//virtual void attackUnit();

	virtual void standAnimation(int direction);
	virtual void moveAnimation(int direction, Vec2 movepos);
	virtual void attackAnimation(int direction);
	virtual void hittedAnimation(int direction);
	virtual void deadAnimation(int direction);

	virtual void Animateinit(Layer* layer);
private:
	RepeatForever* LeftmoveAction;
	RepeatForever* RigthmoveAction;
	RepeatForever* standAction;
	Animate* LeftdeadAction;
	Animate* RightdeadAction;
	Animate* LefthittedAction;
	Animate* RighthittedAction;
	Animate* LeftattackAction;
	Animate* RightattackAction;
	Sequence* moveAction;
	RepeatForever* nowRunAction;
};

class GunnerUnit : public Police
{
public:
	class Bullet
	{
	public:
		Bullet();
		~Bullet();

		void init(GunnerUnit* parent_, Citizen* citizen);

		//void goToCitizen();
		void Collision(bool isend = false);
		
		void Exitscreen();

	private:
		GunnerUnit* parent;
		Citizen* targetUnit;
		Sprite* bulletimage;

		float damage = 0;
	};

	GunnerUnit();
	~GunnerUnit();


	virtual void standAnimation(int direction);
	virtual void moveAnimation(int direction, Vec2 movepos);
	virtual void attackAnimation(int direction);
	virtual void hittedAnimation(int direction);
	virtual void deadAnimation(int direction);

	virtual void Animateinit(Layer* layer);

	virtual void attackUnit();
	void createBullet(Citizen* closestCitizen, float closest);

private:
	bool delay = true;
	Bullet* bullet = nullptr;
	Citizen* tmpclosestCitizen;

	RepeatForever* LeftmoveAction;
	RepeatForever* RigthmoveAction;
	RepeatForever* standAction;
	Animate* LeftdeadAction;
	Animate* RightdeadAction;
	Animate* LefthittedAction;
	Animate* RighthittedAction;
	Animate* LeftattackAction;
	Animate* RightattackAction;
	Sequence* moveAction;
	RepeatForever* nowRunAction;
};