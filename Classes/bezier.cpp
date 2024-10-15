#include "bezier.h"


bz::bz(Layer* layer)
{
	bzsp = Sprite::create("CloseSelected.png");
	bzsp->setPosition(1280, 720);
	Destroy();
	layer->addChild(bzsp, 1);
}

void bz::create(Vec2 point)
{
	dead = true;
	bzsp->setVisible(dead);
	//bzsp->setPosition(point);

	//y = ax^2+bx+c
	//a = x line value
	//...so a = touchPos x
	//controlpoint_1 = the highest value
	// highestvalue's x = -b/2a, y = -(b^2-4ac)/4a

	bezier->controlPoint_1 = Point(1280 - ((1280 - point.x) / 2), 600);
	bezier->controlPoint_2 = point;
	bezier->endPosition = point;
	BezierTo* action = BezierTo::create(3.0f, (*bezier));

	bzsp->setTexture("CloseSelected.png");
	bzsp->setPosition(1280, 360);//start pos

	auto Seq = Sequence::create(action, CallFunc::create(CC_CALLBACK_0(bz::Destroy, this)), NULL);
	bzsp->runAction(Seq);
}

void bz::Destroy()
{
	dead = false;
	bzsp->setVisible(dead);
	bzsp->setPosition(0, 0);
	bzsp->stopAllActions();
}