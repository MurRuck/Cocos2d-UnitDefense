#pragma once

#include "cocos2d.h"

USING_NS_CC;

class bz
{
public:
	ccBezierConfig *bezier = new ccBezierConfig();
	bool dead;
	Sprite* bzsp;
	Sprite* bzsprite;
	bz(Layer* layer);
	void create(Vec2 point);
	void Destroy();
	void move(float x, float y);
	double GetDegree(Vec2 from, Vec2 to);
};