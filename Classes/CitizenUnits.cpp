#include "CitizenUnits.h"
#include "UnitsAddress.h"
#include "Control.h"

People::People()
{
	getStatus()->attack_range = 50;
	getStatus()->attack_speed = 0.5f;
	getStatus()->health = 100;
	getStatus()->max_health = getStatus()->health;
	getStatus()->attack_power = 10;
	getStatus()->shield_point = 40;
}

People::~People()
{
}

void People::setType(int type)
{
	if (UnitsAddress::WEAK_PEOPLE == type)
	{
		citizenType = WEAK;
	}
	else if (UnitsAddress::NORMAL_PEOPLE == type)
	{
		citizenType = NORMAL;
	}
	else if (UnitsAddress::STRONG_PEOPLE == type)
	{
		citizenType = NORMAL;
	}
}

void People::standAnimation(int direction)
{/*
	if (!getStatus()->canRunF)
		return;

	getUnit()->stopAction(nowRunAction);

	if (TEST_1) log("stop nowRunAction");

	if (movetoAction != nullptr)
	{
		getUnit()->stopAction(movetoAction);

	if (TEST_1) log("stop movetoAction");

		movetoAction = nullptr;
	}


	if (TEST_1) log("Running standAnimation");

	nowRunAction = standAction->clone();
	getUnit()->runAction(nowRunAction);*/
	if (!getStatus()->canRunF)
		return;

	if (TEST_1) log("stop nowRunAction	1");
	getUnit()->stopAction(nowRunAction);
	if (movetoAction != nullptr)
	{
		getUnit()->stopAction(movetoAction);
		movetoAction = nullptr;
	}


	nowRunAction = standAction->clone();
	getUnit()->runAction(nowRunAction);
}

void People::moveAnimation(int direction, Vec2 movepos)
{/*
	if (!getStatus()->canRunF)
		return;

	getUnit()->stopAction(nowRunAction);
	if (TEST_1) log("stop nowRunAction");
	if (movetoAction != nullptr)
	{
		getUnit()->stopAction(movetoAction);
	if (TEST_1) log("stop movetoAction");
		movetoAction = nullptr;
	}

	float length = sqrt(pow(getUnit()->getPosition().x - movepos.x, 2) + pow(getUnit()->getPosition().y - movepos.y, 2));


	if (TEST_1) log("Running moveAnimation");
	movetoAction = Sequence::create(MoveTo::create(length * 0.01f, movepos), CallFunc::create([&]() {standAnimation(0);}), nullptr);


	getUnit()->runAction(movetoAction);

	if (direction < 0)
	{
		nowRunAction = LeftmoveAction->clone();
		getUnit()->runAction(nowRunAction);
	}
	else
	{

		nowRunAction = RigthmoveAction->clone();
		getUnit()->runAction(nowRunAction);
	}*/
	if (!getStatus()->canRunF)
		return;

	if (TEST_1) log("stop nowRunAction	2");
	getUnit()->stopAction(nowRunAction);
	if (movetoAction != nullptr)
	{
		getUnit()->stopAction(movetoAction);
		movetoAction = nullptr;
	}

	float length = sqrt(pow(getUnit()->getPosition().x - movepos.x, 2) + pow(getUnit()->getPosition().y - movepos.y, 2));

	movetoAction = Sequence::create(MoveTo::create(length * 0.01f, movepos), CallFunc::create([&]() {standAnimation(0);}), nullptr);


	if (TEST_1) log("runAnimation movetoAction");
	getUnit()->runAction(movetoAction);

	if (direction < 0)
	{
		if (TEST_1) log("runAnimation move");
		nowRunAction = LeftmoveAction->clone();
		getUnit()->runAction(nowRunAction);
	}
	else
	{
		if (TEST_1) log("runAnimation move");
		nowRunAction = RigthmoveAction->clone();
		getUnit()->runAction(nowRunAction);
	}
}

void People::attackAnimation(int direction)
{/*
	if (!getStatus()->canRunF)
		return;

	getUnit()->stopAction(nowRunAction);
	if (TEST_1) log("stop nowRunAction");

	if (movetoAction != nullptr)
	{
		getUnit()->stopAction(movetoAction);
		if (TEST_1) log("stop movetoAction");
		movetoAction = nullptr;
	}

	if (TEST_1) log("Running attackAnimation");
	if (direction < 0)
	{
		nowRunAction = (RepeatForever*)Sequence::create(LeftattackAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
	else
	{
		nowRunAction = (RepeatForever*)Sequence::create(RightattackAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}*/

	if (!getStatus()->canRunF)
		return;

	if (TEST_1) log("stop nowRunAction	3");
	getUnit()->stopAction(nowRunAction);

	if (movetoAction != nullptr)
	{
		getUnit()->stopAction(movetoAction);
		movetoAction = nullptr;
	}

	if (direction < 0)
	{
		nowRunAction = (RepeatForever*)Sequence::create(LeftattackAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true; standAnimation(1);}), nullptr);
		getStatus()->canRunF = false;
		getUnit()->runAction(nowRunAction);
	}
	else
	{
		nowRunAction = (RepeatForever*)Sequence::create(RightattackAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true;standAnimation(-1);}), nullptr);
		getStatus()->canRunF = false;
		getUnit()->runAction(nowRunAction);
	}
}

void People::hittedAnimation(int direction)
{/*
	if (!getStatus()->canRunF)
		return;

	getUnit()->stopAction(nowRunAction);
	if (TEST_1) log("stop nowRunAction");

	if (movetoAction != nullptr)
	{
		getUnit()->stopAction(movetoAction);
		if (TEST_1) log("stop movetoAction");
		movetoAction = nullptr;
	}

	static auto thisUnit = this;

	if (TEST_1) log("Running hittedAnimation");
	if (direction > 0)
	{
		nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.7f), LefthittedAction->clone(), CallFunc::create([&]() {thisUnit->getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
	else
	{
		nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.7f), RighthittedAction->clone(), CallFunc::create([&]() {thisUnit->getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}*/

	/*if (!getStatus()->canRunF)
		return;*/

	//log("Citizen hittid\n");

	standAnimation(0);

	auto runFunc = CallFunc::create([&]() {

		getUnit()->stopAction(nowRunAction);

		if (movetoAction != nullptr)
		{
			getUnit()->stopAction(movetoAction);
			movetoAction = nullptr;
		}
		if(TEST_1)log("stop animation in hittedAnimation");
	});


	if (direction < 0)
	{
		//nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.7f), runFunc, LefthittedAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true; standAnimation(0);}), nullptr);
		
		getStatus()->canRunF = false;

		getUnit()->runAction(Sequence::create(DelayTime::create(0.7f), runFunc, LefthittedAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true; standAnimation(0);}), nullptr));
	}
	else
	{
		//nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.7f), runFunc, RighthittedAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true; standAnimation(0);}), nullptr);
		
		getStatus()->canRunF = false;

		getUnit()->runAction(Sequence::create(DelayTime::create(0.7f), runFunc, RighthittedAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true; standAnimation(0);}), nullptr));
	}
}

void People::deadAnimation(int direction)
{/*
	if (!getStatus()->canRunF)
		return;

	getUnit()->stopAction(nowRunAction);
	if (TEST_1) log("stop nowRunAction");

	if (movetoAction != nullptr)
	{
		getUnit()->stopAction(movetoAction);
	if (TEST_1) log("stop movetoAction");
		movetoAction = nullptr;
	}


	if (TEST_1) log("Running deadAnimation");
	if (direction < 0)
	{
		nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.6f), LeftdeadAction->clone(), CallFunc::create([&]() {getStatus()->canRunF= true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
	else
	{
		nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.6f), RightdeadAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}*/
	//if (!getStatus()->canRunF)
	//	return;
	//
	//if (TEST_1) log("stop nowRunAction	5");
	//getUnit()->stopAction(nowRunAction);
	//
	//if (movetoAction != nullptr)
	//{
	//	getUnit()->stopAction(movetoAction);
	//	movetoAction = nullptr;
	//}


	getUnit()->stopAllActions();


	if (direction < 0)
	{
		nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.6f), LeftdeadAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
	else
	{
		nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.6f), RightdeadAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
}

void People::Animateinit(Layer * layer)
{
	Animation* deadAnimation = Animation::create();
	Animation* deadAnimation2 = Animation::create();
	Animation* moveAnimation2 = Animation::create();
	Animation* moveAnimation = Animation::create();
	Animation* standAnimation = Animation::create();
	Animation* attackAnimation = Animation::create();
	Animation* attackAnimation2 = Animation::create();
	Animation* hittedAnimation = Animation::create();
	Animation* hittedAnimation2 = Animation::create();

	//시민이미지로 바꿔야해

	//char Leftdeadfilename[][50]
	//{
	//	"citizen/dead/left/sprite_1.png",
	//	"citizen/dead/left/sprite_2.png",
	//	"citizen/dead/left/sprite_3.png",
	//	"citizen/dead/left/sprite_4.png",
	//	"citizen/dead/left/sprite_5.png",
	//	"citizen/dead/left/sprite_6.png",
	//	"citizen/dead/left/sprite_7.png",
	//	"citizen/dead/left/sprite_8.png",
	//	"end"
	//};

	////시민이미지로 바꿔야해

	//char Rightdeadfilename[][50]
	//{
	//	"citizen/dead/right/sprite_1.png",
	//	"citizen/dead/right/sprite_2.png",
	//	"citizen/dead/right/sprite_3.png",
	//	"citizen/dead/right/sprite_4.png",
	//	"citizen/dead/right/sprite_5.png",
	//	"citizen/dead/right/sprite_6.png",
	//	"citizen/dead/right/sprite_7.png",
	//	"citizen/dead/right/sprite_8.png",
	//	"end"
	//};

	////시민이미지로 바꿔야해

	//char Lefthittedfilename[][50]
	//{
	//	"citizen/hitted/left/sprite_1.png",
	//	"citizen/hitted/left/sprite_2.png",
	//	"citizen/hitted/left/sprite_3.png",
	//	"citizen/hitted/left/sprite_4.png",
	//	"citizen/hitted/left/sprite_5.png",
	//	"end"
	//};

	////시민이미지로 바꿔야해

	//char Righthittedfilename[][50]
	//{
	//	"citizen/hitted/right/sprite_1.png",
	//	"citizen/hitted/right/sprite_2.png",
	//	"citizen/hitted/right/sprite_3.png",
	//	"citizen/hitted/right/sprite_4.png",
	//	"citizen/hitted/right/sprite_5.png",
	//	"end"
	//};

	////시민이미지로 바꿔야해

	//char Leftattackfilename[][50]
	//{
	//	"citizen/attack/left/sprite_1.png",
	//	"citizen/attack/left/sprite_2.png",
	//	"citizen/attack/left/sprite_3.png",
	//	"citizen/attack/left/sprite_4.png",
	//	"citizen/attack/left/sprite_5.png",
	//	"citizen/attack/left/sprite_6.png",
	//	"citizen/attack/left/sprite_7.png",
	//	"citizen/attack/left/sprite_8.png",
	//	"citizen/attack/left/sprite_9.png",
	//	"citizen/attack/left/sprite_10.png",
	//	"citizen/attack/left/sprite_11.png",
	//	"citizen/attack/left/sprite_12.png",
	//	"citizen/attack/left/sprite_13.png",
	//	"end"
	//};

	////시민이미지로 바꿔야해

	//char Rightattackfilename[][50]
	//{
	//	"citizen/attack/right/sprite_1.png",
	//	"citizen/attack/right/sprite_2.png",
	//	"citizen/attack/right/sprite_3.png",
	//	"citizen/attack/right/sprite_4.png",
	//	"citizen/attack/right/sprite_5.png",
	//	"citizen/attack/right/sprite_6.png",
	//	"citizen/attack/right/sprite_7.png",
	//	"citizen/attack/right/sprite_8.png",
	//	"citizen/attack/right/sprite_9.png",
	//	"citizen/attack/right/sprite_10.png",
	//	"citizen/attack/right/sprite_11.png",
	//	"citizen/attack/right/sprite_12.png",
	//	"citizen/attack/right/sprite_13.png",
	//	"end"
	//};

	////시민이미지로 바꿔야해

	//char Lmovefilename[][50]
	//{
	//	"citizen/run/left/sprite_1.png",
	//	"citizen/run/left/sprite_2.png",
	//	"citizen/run/left/sprite_3.png",
	//	"citizen/run/left/sprite_4.png",
	//	"citizen/run/left/sprite_5.png",
	//	"citizen/run/left/sprite_6.png",
	//	"citizen/run/left/sprite_7.png",
	//	"citizen/run/left/sprite_8.png",
	//	"end"
	//};

	////시민이미지로 바꿔야해

	//char Rmovefilename[][50]
	//{
	//	"citizen/run/right/sprite_1.png",
	//	"citizen/run/right/sprite_2.png",
	//	"citizen/run/right/sprite_3.png",
	//	"citizen/run/right/sprite_4.png",
	//	"citizen/run/right/sprite_5.png",
	//	"citizen/run/right/sprite_6.png",
	//	"citizen/run/right/sprite_7.png",
	//	"citizen/run/right/sprite_8.png",
	//	"end"
	//};

	////시민이미지로 바꿔야해

	//char standfilename[][50]
	//{
	//	"citizen/stand/sprite_1.png",
	//	"citizen/stand/sprite_2.png",
	//	"citizen/stand/sprite_3.png",
	//	"citizen/stand/sprite_4.png",
	//	"end",
	//};


	//for (int i = 0;strcmp("end", Leftdeadfilename[i]);i++)
	//{
	//	deadAnimation->addSpriteFrameWithFile(Leftdeadfilename[i]);
	//	deadAnimation2->addSpriteFrameWithFile(Rightdeadfilename[i]);
	//}

	//for (int i = 0;strcmp("end", Righthittedfilename[i]);i++)
	//{
	//	hittedAnimation->addSpriteFrameWithFile(Lefthittedfilename[i]);
	//	hittedAnimation2->addSpriteFrameWithFile(Righthittedfilename[i]);
	//}

	//for (int i = 0;strcmp("end", Leftattackfilename[i]);i++)
	//{
	//	attackAnimation->addSpriteFrameWithFile(Leftattackfilename[i]);
	//	attackAnimation2->addSpriteFrameWithFile(Rightattackfilename[i]);
	//}

	//for (int i = 0;strcmp("end", Lmovefilename[i]);i++)
	//	moveAnimation->addSpriteFrameWithFile(Lmovefilename[i]);

	//for (int i = 0;strcmp("end", Rmovefilename[i]);i++)
	//	moveAnimation2->addSpriteFrameWithFile(Rmovefilename[i]);

	//for (int i = 0;strcmp("end", standfilename[i]);i++)
	//	standAnimation->addSpriteFrameWithFile(standfilename[i]);

int end_of_filename[][5] =
{
	// dead, hitted,attack,move,stand
	{ 14,   11,   13,   8,   4 },
	{ 8,   11,   13,   8,   4 },
	{ 0,   0,   13,   13,   4, },
};
char type[][20] = { "weak","normal","strong" };

for (int i = 0; i < end_of_filename[citizenType][0]; i++)
{
	deadAnimation->addSpriteFrameWithFile(StringUtils::format("citizen/%s/dead/left/sprite_%d.png", type[citizenType], i + 1));
	deadAnimation2->addSpriteFrameWithFile(StringUtils::format("citizen/%s/dead/right/sprite_%d.png", type[citizenType], i + 1));
}

for (int i = 0; i < end_of_filename[citizenType][1]; i++)
{
	hittedAnimation->addSpriteFrameWithFile(StringUtils::format("citizen/%s/hitted/left/sprite_%d.png", type[citizenType], i + 1));
	hittedAnimation2->addSpriteFrameWithFile(StringUtils::format("citizen/%s/hitted/right/sprite_%d.png", type[citizenType], i + 1));
}

for (int i = 0; i < end_of_filename[citizenType][2]; i++)
{
	attackAnimation->addSpriteFrameWithFile(StringUtils::format("citizen/%s/attack/left/sprite_%d.png", type[citizenType], i + 1));
	attackAnimation2->addSpriteFrameWithFile(StringUtils::format("citizen/%s/attack/right/sprite_%d.png", type[citizenType], i + 1));
}

for (int i = 0; i < end_of_filename[citizenType][3]; i++)
{
	moveAnimation->addSpriteFrameWithFile(StringUtils::format("citizen/%s/run/left/sprite_%d.png", type[citizenType], i + 1));
	moveAnimation2->addSpriteFrameWithFile(StringUtils::format("citizen/%s/run/right/sprite_%d.png", type[citizenType], i + 1));
}

for (int i = 0; i < end_of_filename[citizenType][4]; i++)
{
	standAnimation->addSpriteFrameWithFile(StringUtils::format("citizen/%s/stand/sprite_%d.png", type[citizenType], i + 1));
}
	deadAnimation->setDelayPerUnit(0.1f);
	deadAnimation2->setDelayPerUnit(0.1f);
	hittedAnimation->setDelayPerUnit(0.1f);
	hittedAnimation2->setDelayPerUnit(0.1f);
	attackAnimation->setDelayPerUnit(0.1f);
	attackAnimation2->setDelayPerUnit(0.1f);
	moveAnimation2->setDelayPerUnit(0.1f);
	moveAnimation->setDelayPerUnit(0.1f);
	standAnimation->setDelayPerUnit(0.1f);


	auto deadAnimate = Animate::create(deadAnimation);
	auto deadAnimate2 = Animate::create(deadAnimation2);
	auto hittedAnimate = Animate::create(hittedAnimation);
	auto hittedAnimate2 = Animate::create(hittedAnimation2);
	auto attackAnimate = Animate::create(attackAnimation);
	auto attackAnimate2 = Animate::create(attackAnimation2);
	auto moveAnimate = Animate::create(moveAnimation);
	auto moveAnimate2 = Animate::create(moveAnimation2);
	auto standAnimate = Animate::create(standAnimation);



	LeftdeadAction = deadAnimate;
	RightdeadAction = deadAnimate2;
	LefthittedAction = hittedAnimate;
	RighthittedAction = hittedAnimate2;
	LeftattackAction = attackAnimate;
	RightattackAction = attackAnimate2;
	LeftmoveAction = RepeatForever::create(moveAnimate);
	RigthmoveAction = RepeatForever::create(moveAnimate2);
	standAction = RepeatForever::create(standAnimate);






	RepeatForever* Actions[] = {
		LeftmoveAction,
		RigthmoveAction,
		standAction,
		RepeatForever::create(LeftdeadAction),
		RepeatForever::create(RightdeadAction),
		RepeatForever::create(LefthittedAction),
		RepeatForever::create(RighthittedAction),
		RepeatForever::create(LeftattackAction),
		RepeatForever::create(RightattackAction),
		nullptr,
	};


	for (int i = 0;Actions[i] != nullptr;i++)
	{
		Sprite* sprite = Sprite::create();
		sprite->runAction(Actions[i]);
		sprite->setPosition(Vec2(50, 100 * i + 100));
		sprite->setVisible(TEST);
		layer->addChild(sprite, 100000);
	}


	nowRunAction = standAction->clone();
	movetoAction = nullptr;
	getUnit()->runAction(nowRunAction);
}

// 여기는 새총의 영역이다 


Slingshoter::Slingshoter()
{
	getStatus()->attack_range = 300;
	getStatus()->attack_speed = 2.f;
	getStatus()->health = 100;
	getStatus()->max_health = getStatus()->health;
	getStatus()->attack_power = 10;
	getStatus()->shield_point = 100;
}


Slingshoter::~Slingshoter()
{
}


void Slingshoter::standAnimation(int direction)
{/*
 if (!getStatus()->canRunF)
 return;

 getUnit()->stopAction(nowRunAction);

 if (TEST_1) log("stop nowRunAction");

 if (movetoAction != nullptr)
 {
 getUnit()->stopAction(movetoAction);

 if (TEST_1) log("stop movetoAction");

 movetoAction = nullptr;
 }


 if (TEST_1) log("Running standAnimation");

 nowRunAction = standAction->clone();
 getUnit()->runAction(nowRunAction);*/
	if (!getStatus()->canRunF)
		return;

	if (TEST_1) log("stop nowRunAction	1");
	getUnit()->stopAction(nowRunAction);
	if (movetoAction != nullptr)
	{
		getUnit()->stopAction(movetoAction);
		movetoAction = nullptr;
	}


	nowRunAction = standAction->clone();
	getUnit()->runAction(nowRunAction);
}

void Slingshoter::moveAnimation(int direction, Vec2 movepos)
{/*
 if (!getStatus()->canRunF)
 return;

 getUnit()->stopAction(nowRunAction);
 if (TEST_1) log("stop nowRunAction");
 if (movetoAction != nullptr)
 {
 getUnit()->stopAction(movetoAction);
 if (TEST_1) log("stop movetoAction");
 movetoAction = nullptr;
 }

 float length = sqrt(pow(getUnit()->getPosition().x - movepos.x, 2) + pow(getUnit()->getPosition().y - movepos.y, 2));


 if (TEST_1) log("Running moveAnimation");
 movetoAction = Sequence::create(MoveTo::create(length * 0.01f, movepos), CallFunc::create([&]() {standAnimation(0);}), nullptr);


 getUnit()->runAction(movetoAction);

 if (direction < 0)
 {
 nowRunAction = LeftmoveAction->clone();
 getUnit()->runAction(nowRunAction);
 }
 else
 {

 nowRunAction = RigthmoveAction->clone();
 getUnit()->runAction(nowRunAction);
 }*/
	if (!getStatus()->canRunF)
		return;

	if (TEST_1) log("stop nowRunAction	2");
	getUnit()->stopAction(nowRunAction);
	if (movetoAction != nullptr)
	{
		getUnit()->stopAction(movetoAction);
		movetoAction = nullptr;
	}

	float length = sqrt(pow(getUnit()->getPosition().x - movepos.x, 2) + pow(getUnit()->getPosition().y - movepos.y, 2));

	movetoAction = Sequence::create(MoveTo::create(length * 0.01f, movepos), CallFunc::create([&]() {standAnimation(0);}), nullptr);


	if (TEST_1) log("runAnimation movetoAction");
	getUnit()->runAction(movetoAction);

	if (direction < 0)
	{
		if (TEST_1) log("runAnimation move");
		nowRunAction = LeftmoveAction->clone();
		getUnit()->runAction(nowRunAction);
	}
	else
	{
		if (TEST_1) log("runAnimation move");
		nowRunAction = RigthmoveAction->clone();
		getUnit()->runAction(nowRunAction);
	}
}

void Slingshoter::attackAnimation(int direction)
{/*
 if (!getStatus()->canRunF)
 return;

 getUnit()->stopAction(nowRunAction);
 if (TEST_1) log("stop nowRunAction");

 if (movetoAction != nullptr)
 {
 getUnit()->stopAction(movetoAction);
 if (TEST_1) log("stop movetoAction");
 movetoAction = nullptr;
 }

 if (TEST_1) log("Running attackAnimation");
 if (direction < 0)
 {
 nowRunAction = (RepeatForever*)Sequence::create(LeftattackAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true;}), nullptr);
 getUnit()->runAction(nowRunAction);
 }
 else
 {
 nowRunAction = (RepeatForever*)Sequence::create(RightattackAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true;}), nullptr);
 getUnit()->runAction(nowRunAction);
 }*/

	if (!getStatus()->canRunF)
		return;

	if (TEST_1) log("stop nowRunAction	3");
	getUnit()->stopAction(nowRunAction);

	if (movetoAction != nullptr)
	{
		getUnit()->stopAction(movetoAction);
		movetoAction = nullptr;
	}

	if (direction < 0)
	{
		nowRunAction = (RepeatForever*)Sequence::create(LeftattackAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true; standAnimation(1);}), nullptr);
		getStatus()->canRunF = false;
		getUnit()->runAction(nowRunAction);
	}
	else
	{
		nowRunAction = (RepeatForever*)Sequence::create(RightattackAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true;standAnimation(-1);}), nullptr);
		getStatus()->canRunF = false;
		getUnit()->runAction(nowRunAction);
	}
}

void Slingshoter::hittedAnimation(int direction)
{/*
 if (!getStatus()->canRunF)
 return;

 getUnit()->stopAction(nowRunAction);
 if (TEST_1) log("stop nowRunAction");

 if (movetoAction != nullptr)
 {
 getUnit()->stopAction(movetoAction);
 if (TEST_1) log("stop movetoAction");
 movetoAction = nullptr;
 }

 static auto thisUnit = this;

 if (TEST_1) log("Running hittedAnimation");
 if (direction > 0)
 {
 nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.7f), LefthittedAction->clone(), CallFunc::create([&]() {thisUnit->getStatus()->canRunF = true;}), nullptr);
 getUnit()->runAction(nowRunAction);
 }
 else
 {
 nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.7f), RighthittedAction->clone(), CallFunc::create([&]() {thisUnit->getStatus()->canRunF = true;}), nullptr);
 getUnit()->runAction(nowRunAction);
 }*/

 /*if (!getStatus()->canRunF)
 return;*/

 //log("Citizen hittid\n");

	standAnimation(0);

	auto runFunc = CallFunc::create([&]() {

		getUnit()->stopAction(nowRunAction);

		if (movetoAction != nullptr)
		{
			getUnit()->stopAction(movetoAction);
			movetoAction = nullptr;
		}
		if (TEST_1)log("stop animation in hittedAnimation");
	});


	if (direction < 0)
	{
		//nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.7f), runFunc, LefthittedAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true; standAnimation(0);}), nullptr);

		getStatus()->canRunF = false;

		getUnit()->runAction(Sequence::create(DelayTime::create(0.7f), runFunc, LefthittedAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true; standAnimation(0);}), nullptr));
	}
	else
	{
		//nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.7f), runFunc, RighthittedAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true; standAnimation(0);}), nullptr);

		getStatus()->canRunF = false;

		getUnit()->runAction(Sequence::create(DelayTime::create(0.7f), runFunc, RighthittedAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true; standAnimation(0);}), nullptr));
	}
}

void Slingshoter::deadAnimation(int direction)
{/*
 if (!getStatus()->canRunF)
 return;

 getUnit()->stopAction(nowRunAction);
 if (TEST_1) log("stop nowRunAction");

 if (movetoAction != nullptr)
 {
 getUnit()->stopAction(movetoAction);
 if (TEST_1) log("stop movetoAction");
 movetoAction = nullptr;
 }


 if (TEST_1) log("Running deadAnimation");
 if (direction < 0)
 {
 nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.6f), LeftdeadAction->clone(), CallFunc::create([&]() {getStatus()->canRunF= true;}), nullptr);
 getUnit()->runAction(nowRunAction);
 }
 else
 {
 nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.6f), RightdeadAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true;}), nullptr);
 getUnit()->runAction(nowRunAction);
 }*/
 //if (!getStatus()->canRunF)
 //	return;
 //
 //if (TEST_1) log("stop nowRunAction	5");
 //getUnit()->stopAction(nowRunAction);
 //
 //if (movetoAction != nullptr)
 //{
 //	getUnit()->stopAction(movetoAction);
 //	movetoAction = nullptr;
 //}


	getUnit()->stopAllActions();


	if (direction < 0)
	{
		nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.6f), LeftdeadAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
	else
	{
		nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.6f), RightdeadAction->clone(), CallFunc::create([&]() {getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
}

void Slingshoter::Animateinit(Layer * layer)
{
	Animation* deadAnimation = Animation::create();
	Animation* deadAnimation2 = Animation::create();
	Animation* moveAnimation2 = Animation::create();
	Animation* moveAnimation = Animation::create();
	Animation* standAnimation = Animation::create();
	Animation* attackAnimation = Animation::create();
	Animation* attackAnimation2 = Animation::create();
	Animation* hittedAnimation = Animation::create();
	Animation* hittedAnimation2 = Animation::create();

	//시민이미지로 바꿔야해

	char Leftdeadfilename[][50]
	{
		"citizen/dead/left/sprite_1.png",
		"citizen/dead/left/sprite_2.png",
		"citizen/dead/left/sprite_3.png",
		"citizen/dead/left/sprite_4.png",
		"citizen/dead/left/sprite_5.png",
		"citizen/dead/left/sprite_6.png",
		"citizen/dead/left/sprite_7.png",
		"citizen/dead/left/sprite_8.png",
		"end"
	};

	//시민이미지로 바꿔야해

	char Rightdeadfilename[][50]
	{
		"citizen/dead/right/sprite_1.png",
		"citizen/dead/right/sprite_2.png",
		"citizen/dead/right/sprite_3.png",
		"citizen/dead/right/sprite_4.png",
		"citizen/dead/right/sprite_5.png",
		"citizen/dead/right/sprite_6.png",
		"citizen/dead/right/sprite_7.png",
		"citizen/dead/right/sprite_8.png",
		"end"
	};

	//시민이미지로 바꿔야해

	char Lefthittedfilename[][50]
	{
		"citizen/hitted/left/sprite_1.png",
		"citizen/hitted/left/sprite_2.png",
		"citizen/hitted/left/sprite_3.png",
		"citizen/hitted/left/sprite_4.png",
		"citizen/hitted/left/sprite_5.png",
		"end"
	};

	//시민이미지로 바꿔야해

	char Righthittedfilename[][50]
	{
		"citizen/hitted/right/sprite_1.png",
		"citizen/hitted/right/sprite_2.png",
		"citizen/hitted/right/sprite_3.png",
		"citizen/hitted/right/sprite_4.png",
		"citizen/hitted/right/sprite_5.png",
		"end"
	};

	//시민이미지로 바꿔야해

	char Leftattackfilename[][50]
	{
		"citizen/attack/left/sprite_1.png",
		"citizen/attack/left/sprite_2.png",
		"citizen/attack/left/sprite_3.png",
		"citizen/attack/left/sprite_4.png",
		"citizen/attack/left/sprite_5.png",
		"citizen/attack/left/sprite_6.png",
		"citizen/attack/left/sprite_7.png",
		"citizen/attack/left/sprite_8.png",
		"citizen/attack/left/sprite_9.png",
		"citizen/attack/left/sprite_10.png",
		"citizen/attack/left/sprite_11.png",
		"citizen/attack/left/sprite_12.png",
		"citizen/attack/left/sprite_13.png",
		"end"
	};

	//시민이미지로 바꿔야해

	char Rightattackfilename[][50]
	{
		"citizen/attack/right/sprite_1.png",
		"citizen/attack/right/sprite_2.png",
		"citizen/attack/right/sprite_3.png",
		"citizen/attack/right/sprite_4.png",
		"citizen/attack/right/sprite_5.png",
		"citizen/attack/right/sprite_6.png",
		"citizen/attack/right/sprite_7.png",
		"citizen/attack/right/sprite_8.png",
		"citizen/attack/right/sprite_9.png",
		"citizen/attack/right/sprite_10.png",
		"citizen/attack/right/sprite_11.png",
		"citizen/attack/right/sprite_12.png",
		"citizen/attack/right/sprite_13.png",
		"end"
	};

	//시민이미지로 바꿔야해

	char Lmovefilename[][50]
	{
		"citizen/run/left/sprite_1.png",
		"citizen/run/left/sprite_2.png",
		"citizen/run/left/sprite_3.png",
		"citizen/run/left/sprite_4.png",
		"citizen/run/left/sprite_5.png",
		"citizen/run/left/sprite_6.png",
		"citizen/run/left/sprite_7.png",
		"citizen/run/left/sprite_8.png",
		"end"
	};

	//시민이미지로 바꿔야해

	char Rmovefilename[][50]
	{
		"citizen/run/right/sprite_1.png",
		"citizen/run/right/sprite_2.png",
		"citizen/run/right/sprite_3.png",
		"citizen/run/right/sprite_4.png",
		"citizen/run/right/sprite_5.png",
		"citizen/run/right/sprite_6.png",
		"citizen/run/right/sprite_7.png",
		"citizen/run/right/sprite_8.png",
		"end"
	};

	//시민이미지로 바꿔야해

	char standfilename[][50]
	{
		"citizen/stand/sprite_1.png",
		"citizen/stand/sprite_2.png",
		"citizen/stand/sprite_3.png",
		"citizen/stand/sprite_4.png",
		"end",
	};


	for (int i = 0;strcmp("end", Leftdeadfilename[i]);i++)
	{
		deadAnimation->addSpriteFrameWithFile(Leftdeadfilename[i]);
		deadAnimation2->addSpriteFrameWithFile(Rightdeadfilename[i]);
	}

	for (int i = 0;strcmp("end", Righthittedfilename[i]);i++)
	{
		hittedAnimation->addSpriteFrameWithFile(Lefthittedfilename[i]);
		hittedAnimation2->addSpriteFrameWithFile(Righthittedfilename[i]);
	}

	for (int i = 0;strcmp("end", Leftattackfilename[i]);i++)
	{
		attackAnimation->addSpriteFrameWithFile(Leftattackfilename[i]);
		attackAnimation2->addSpriteFrameWithFile(Rightattackfilename[i]);
	}

	for (int i = 0;strcmp("end", Lmovefilename[i]);i++)
		moveAnimation->addSpriteFrameWithFile(Lmovefilename[i]);

	for (int i = 0;strcmp("end", Rmovefilename[i]);i++)
		moveAnimation2->addSpriteFrameWithFile(Rmovefilename[i]);

	for (int i = 0;strcmp("end", standfilename[i]);i++)
		standAnimation->addSpriteFrameWithFile(standfilename[i]);


	deadAnimation->setDelayPerUnit(0.1f);
	deadAnimation2->setDelayPerUnit(0.1f);
	hittedAnimation->setDelayPerUnit(0.1f);
	hittedAnimation2->setDelayPerUnit(0.1f);
	attackAnimation->setDelayPerUnit(0.1f);
	attackAnimation2->setDelayPerUnit(0.1f);
	moveAnimation2->setDelayPerUnit(0.1f);
	moveAnimation->setDelayPerUnit(0.1f);
	standAnimation->setDelayPerUnit(0.1f);


	auto deadAnimate = Animate::create(deadAnimation);
	auto deadAnimate2 = Animate::create(deadAnimation2);
	auto hittedAnimate = Animate::create(hittedAnimation);
	auto hittedAnimate2 = Animate::create(hittedAnimation2);
	auto attackAnimate = Animate::create(attackAnimation);
	auto attackAnimate2 = Animate::create(attackAnimation2);
	auto moveAnimate = Animate::create(moveAnimation);
	auto moveAnimate2 = Animate::create(moveAnimation2);
	auto standAnimate = Animate::create(standAnimation);



	LeftdeadAction = deadAnimate;
	RightdeadAction = deadAnimate2;
	LefthittedAction = hittedAnimate;
	RighthittedAction = hittedAnimate2;
	LeftattackAction = attackAnimate;
	RightattackAction = attackAnimate2;
	LeftmoveAction = RepeatForever::create(moveAnimate);
	RigthmoveAction = RepeatForever::create(moveAnimate2);
	standAction = RepeatForever::create(standAnimate);






	RepeatForever* Actions[] = {
		LeftmoveAction,
		RigthmoveAction,
		standAction,
		RepeatForever::create(LeftdeadAction),
		RepeatForever::create(RightdeadAction),
		RepeatForever::create(LefthittedAction),
		RepeatForever::create(RighthittedAction),
		RepeatForever::create(LeftattackAction),
		RepeatForever::create(RightattackAction),
		nullptr,
	};


	for (int i = 0;Actions[i] != nullptr;i++)
	{
		Sprite* sprite = Sprite::create();
		sprite->runAction(Actions[i]);
		sprite->setPosition(Vec2(50, 100 * i + 100));
		sprite->setVisible(TEST);
		layer->addChild(sprite, 100000);
	}


	nowRunAction = standAction->clone();
	movetoAction = nullptr;
	getUnit()->runAction(nowRunAction);
}

void Slingshoter::attackUnit(Citizen::Closest _closest)
{

	Citizen::Closest closest;




	if (delay)
	{
		for (int i = 0;i < UnitsAddress::getInstance()->getMaxUnitsnum();i++)									//가장 가까운 경찾 찾기
		{																										//
			auto tmp = UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i);							//
																												//
			if (tmp == nullptr)																					//
				continue;																						//
																												//
			float range = attackRange(tmp->unitaddress->getUnit(), getStatus()->attack_range);					//
																												//
			if (range != 0 && (closest.closest == 0 || closest.closest > range))								//
			{																									//
				closest.closestPolice = (Police*)tmp->unitaddress;												//
				closest.closest = range;																		//
			}																									//
		}																										//
		if (closest.closestPolice == nullptr) return;															//가까운게 없을 시 리턴

		createBullet(closest.closestPolice, closest.closest);


		attackAnimation(1);

		getUnit()->runAction(Sequence::create(DelayTime::create(getStatus()->attack_speed), CallFunc::create([&]() {delay = true;}), nullptr));

		delay = false;
	}
}

void Slingshoter::createBullet(Police * closestPolice, float closest)
{
	if (closest == 9999)
	{
		delete bullet;
		bullet = nullptr;
		return;
	}
	if (bullet == nullptr)
	{
		tmpclosestPolice = closestPolice;
		getUnit()->runAction(Sequence::create(CallFunc::create([&]() {tmpclosestPolice->getUnit()->setColor(Color3B::RED);}), DelayTime::create(3.f), CallFunc::create([&]() {this->bullet = new Bullet; this->bullet->init(this, tmpclosestPolice);}), nullptr));
	}
}

Slingshoter::Bullet::Bullet()
{
}

Slingshoter::Bullet::~Bullet()
{
	bulletimage = nullptr;
	parent->getUnit()->setColor(Color3B::WHITE);
}

void Slingshoter::Bullet::init(Slingshoter * parent_, Police * police)
{
	targetUnit = police;

	parent = parent_;

	auto testpos = parent->getUnit()->getPosition();

	bulletimage = Sprite::create("gunner/bullet/sprite_1.png");
	bulletimage->setPosition(testpos);
	//bulletimage->setScale(0.3f);
	//parent->getUnit()->addChild(bulletimage);
	parent->getMainlayer()->addChild(bulletimage);
	damage = parent->getStatus()->attack_power;

	bulletimage->runAction(RepeatForever::create((Sequence::create((ActionInterval*)CallFunc::create([&]() {this->Collision();/* this->Exitscreen();*/}), nullptr))));
	bulletimage->runAction(Sequence::create(DelayTime::create(2.5f), CallFunc::create([&]() {this->Collision(true);}), nullptr));


	auto citizenpos = police->getUnit()->getPosition();
	auto bulletpos = bulletimage->getPosition();

	float degree = atan2f(citizenpos.y - bulletpos.y, citizenpos.x - bulletpos.x) /** 180 / 3.14f + 90*/;

	//bulletimage->setRotation(degree);
	bulletpos.x = bulletpos.x + cos(degree) * 1000;
	bulletpos.y = bulletpos.y + sin(degree) * 1000;

	log("degree %f", degree);

	auto movetime = sqrt(pow(bulletpos.x - bulletimage->getPosition().x, 2) + pow(bulletpos.y - bulletimage->getPosition().y, 2)) / 1000.f;


	bulletimage->runAction(Sequence::create(MoveTo::create(movetime, bulletpos), CallFunc::create([&]() {this->Collision(true);}), nullptr));

}

void Slingshoter::Bullet::Collision(bool isend)
{
	if (bulletimage == nullptr)
		return;

	if (isend)
	{
		if (UnitsAddress::getInstance()->searchUnit(parent))
			bulletimage->cleanup();
		parent->getUnit()->getParent()->removeChild(bulletimage);
		parent->createBullet(nullptr, 9999);
		return;
	}

	for (int i = 0;i < UnitsAddress::getInstance()->getMaxUnitsnum();i++)
	{
		if (UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i) == nullptr/* || !UnitsAddress::getInstance()->searchUnit(parent)*/)
			break;


		auto tmp = (Police*)UnitsAddress::getInstance()->getUnits(UnitsAddress::POLICE, i)->unitaddress;

		Vec2 bulletpos = bulletimage->getPosition();
		auto tmpcitizen = tmp->getUnit();

		auto tmppos = tmpcitizen->getPosition();
		auto tmpsize = tmpcitizen->getContentSize();
		//auto fwe = bulletimage->getBoundingBox().containsPoint(tmp->getUnit()->getPosition());
		//bulletpos.x += *(SelectUnit::getInstance()->getMovedXpos());

		if ((tmppos.x - (tmpsize.width / 2) < bulletpos.x && bulletpos.x < tmppos.x + (tmpsize.width / 2) &&
			tmppos.y - (tmpsize.height / 2) < bulletpos.y && bulletpos.y < tmppos.y + (tmpsize.height / 2)))
		{
			targetUnit->getUnit()->setColor(Color3B::WHITE);

			tmp->hittedUnit(damage, 0);
			bulletimage->cleanup();
			parent->getUnit()->getParent()->removeChild(bulletimage);
			parent->createBullet(nullptr, 9999);

		}
	}
}

void Slingshoter::Bullet::Exitscreen()
{
	if (bulletimage == nullptr)
		return;

	//log("Gunner's num %d", UnitsAddress::getInstance()->searchUnitnum(parent));


	//if (!(0 < bulletimage->getPosition().x && bulletimage->getPosition().x < 1280 && 0 < bulletimage->getPosition().y && bulletimage->getPosition().y < 720))
	//	Collision(true);
}
