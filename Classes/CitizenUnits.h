#pragma once
#include "cocos2d.h"
#include "MainUnit.h"

#define TEST_1 0

class People : public Citizen
{
public:
	enum
	{
		WEAK,
		NORMAL,
		STRONG,
	};
	//	����� (����, ����, ����)�ù��� �����̴پƾƾƾƾƾƾƾˤ�������㤿�����路������������Ĥ��u��������ä�����T�����g�����H����
	People();
	~People();

	void setType(int type);

	//virtual void attackUnit();

	virtual void standAnimation(int direction);
	virtual void moveAnimation(int direction, Vec2 movepos);
	virtual void attackAnimation(int direction);
	virtual void hittedAnimation(int direction);
	virtual void deadAnimation(int direction);

	virtual void Animateinit(Layer* layer);
private:
	int citizenType;
};


class Slingshoter : public Citizen
{
public:
	class Bullet
	{
	public:
		Bullet();
		~Bullet();

		void init(Slingshoter* parent_, Police* police);

		//void goToCitizen();
		void Collision(bool isend = false);

		void Exitscreen();

	private:
		Slingshoter* parent;
		Police* targetUnit;
		Sprite* bulletimage;

		float damage = 0;
	};
	

	struct Closest
	{
		float closest = 0;
		Police* closestPolice = 0;
	};


	Slingshoter();
	~Slingshoter();

	//virtual void attackUnit();

	virtual void standAnimation(int direction);
	virtual void moveAnimation(int direction, Vec2 movepos);
	virtual void attackAnimation(int direction);
	virtual void hittedAnimation(int direction);
	virtual void deadAnimation(int direction);

	virtual void Animateinit(Layer* layer);

	virtual void attackUnit(Citizen::Closest _closest);
	void createBullet(Police* closestPolice, float closest);
private:
	bool delay = true;
	Bullet* bullet = nullptr;
	Police* tmpclosestPolice;
};