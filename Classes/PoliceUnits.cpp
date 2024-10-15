#include "PoliceUnits.h"
#include "UnitsAddress.h"
#include "CitizenUnits.h"
//방패조의 영역이다!

ShieldUnit::~ShieldUnit()
{
}

void ShieldUnit::standAnimation(int direction)
{

	if (!getStatus()->canRunF)
		return;

	getUnit()->stopAction(nowRunAction);
	if (moveAction != nullptr)
	{
		getUnit()->stopAction(moveAction);
		moveAction = nullptr;
	}


	nowRunAction = standAction->clone();
	getUnit()->runAction(nowRunAction);
}

void ShieldUnit::moveAnimation(int direction, Vec2 movepos)
{

	if (!getStatus()->canRunF)
		return;

	getUnit()->stopAction(nowRunAction);
	if (moveAction != nullptr)
	{
		getUnit()->stopAction(moveAction);
		moveAction = nullptr;
	}

	float length = sqrt(pow(getUnit()->getPosition().x - movepos.x, 2) + pow(getUnit()->getPosition().y - movepos.y, 2));

	moveAction = Sequence::create(MoveTo::create(length * 0.01f, movepos), CallFunc::create([&]() {standAnimation(0);}), nullptr);


	getUnit()->runAction(moveAction);

	if (direction < 0)
	{

		nowRunAction = LeftmoveAction->clone();
		getUnit()->runAction(nowRunAction);
	}
	else
	{

		nowRunAction = RigthmoveAction->clone();
		getUnit()->runAction(nowRunAction);
	}
}

void ShieldUnit::attackAnimation(int direction)
{
	if (!getStatus()->canRunF)
		return;

	getUnit()->stopAction(nowRunAction);

	if (moveAction != nullptr)
	{
		getUnit()->stopAction(moveAction);
		moveAction = nullptr;
	}

	if (direction < 0)
	{
		nowRunAction = (RepeatForever*)Sequence::create(LeftattackAction->clone(), CallFunc::create([&]() {standAnimation(0);  getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
	else
	{
		nowRunAction = (RepeatForever*)Sequence::create(RightattackAction->clone(), CallFunc::create([&]() {standAnimation(0);  getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
}

void ShieldUnit::hittedAnimation(int direction)
{
	if (!getStatus()->canRunF)
		return;

	getUnit()->stopAction(nowRunAction);

	if (moveAction != nullptr)
	{
		getUnit()->stopAction(moveAction);
		moveAction = nullptr;
	}


	if (direction < 0)
	{
		nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.7f), LefthittedAction->clone(), CallFunc::create([&]() {standAnimation(0);  getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
	else
	{
		nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.7f), RighthittedAction->clone(), CallFunc::create([&]() {standAnimation(0);  getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
}

void ShieldUnit::deadAnimation(int direction)
{
	//if (!getStatus()->canRunF)
	//	return;
	//
	//getUnit()->stopAction(nowRunAction);
	//
	//if (moveAction != nullptr)
	//{
	//	getUnit()->stopAction(moveAction);
	//	moveAction = nullptr;
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

void ShieldUnit::Animateinit(Layer* layer)
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

	//쉴드로 이미지다시넣어야해

	char Leftdeadfilename[][50]
	{
		"botton/dead/left/sprite_1.png",
		"botton/dead/left/sprite_2.png",
		"botton/dead/left/sprite_3.png",
		"botton/dead/left/sprite_4.png",
		"botton/dead/left/sprite_5.png",
		"botton/dead/left/sprite_6.png",
		"botton/dead/left/sprite_7.png",
		"botton/dead/left/sprite_8.png",
		"botton/dead/left/sprite_9.png",
		"botton/dead/left/sprite_10.png",
		"botton/dead/left/sprite_11.png",
		"botton/dead/left/sprite_12.png",
		"botton/dead/left/sprite_13.png",
		"botton/dead/left/sprite_14.png",
		"end"
	};

	//쉴드로 이미지다시넣어야해

	char Rightdeadfilename[][50]
	{
		"botton/dead/right/sprite_1.png",
		"botton/dead/right/sprite_2.png",
		"botton/dead/right/sprite_3.png",
		"botton/dead/right/sprite_4.png",
		"botton/dead/right/sprite_5.png",
		"botton/dead/right/sprite_6.png",
		"botton/dead/right/sprite_7.png",
		"botton/dead/right/sprite_8.png",
		"botton/dead/right/sprite_9.png",
		"botton/dead/right/sprite_10.png",
		"botton/dead/right/sprite_11.png",
		"botton/dead/right/sprite_12.png",
		"botton/dead/right/sprite_13.png",
		"botton/dead/right/sprite_14.png",
		"end"
	};

	//쉴드로 이미지다시넣어야해

	char Lefthittedfilename[][50]
	{
		"botton/hitted/left/sprite_1.png",
		"botton/hitted/left/sprite_2.png",
		"botton/hitted/left/sprite_3.png",
		"botton/hitted/left/sprite_4.png",
		"botton/hitted/left/sprite_5.png",
		"end"
	};

	//쉴드로 이미지다시넣어야해

	char Righthittedfilename[][50]
	{
		"botton/hitted/right/sprite_1.png",
		"botton/hitted/right/sprite_2.png",
		"botton/hitted/right/sprite_3.png",
		"botton/hitted/right/sprite_4.png",
		"botton/hitted/right/sprite_5.png",
		"end"
	};

	char Leftattackfilename[][50]
	{
		"shield/attack/left/sprite_1.png",
		"shield/attack/left/sprite_2.png",
		"shield/attack/left/sprite_3.png",
		"shield/attack/left/sprite_4.png",
		"shield/attack/left/sprite_5.png",
		"shield/attack/left/sprite_6.png",
		"shield/attack/left/sprite_7.png",
		"shield/attack/left/sprite_8.png",
		"shield/attack/left/sprite_9.png",
		"shield/attack/left/sprite_10.png",
		"shield/attack/left/sprite_11.png",
		"shield/attack/left/sprite_12.png",
		"shield/attack/left/sprite_13.png",
		"shield/attack/left/sprite_14.png",
		"end"
	};

	char Rightattackfilename[][50]
	{
		"shield/attack/right/sprite_1.png",
		"shield/attack/right/sprite_2.png",
		"shield/attack/right/sprite_3.png",
		"shield/attack/right/sprite_4.png",
		"shield/attack/right/sprite_5.png",
		"shield/attack/right/sprite_6.png",
		"shield/attack/right/sprite_7.png",
		"shield/attack/right/sprite_8.png",
		"shield/attack/right/sprite_9.png",
		"shield/attack/right/sprite_10.png",
		"shield/attack/right/sprite_11.png",
		"shield/attack/right/sprite_12.png",
		"shield/attack/right/sprite_13.png",
		"shield/attack/right/sprite_14.png",
		"end"
	};

	char Lmovefilename[][50]
	{
		"shield/run/left/sprite_1.png",
		"shield/run/left/sprite_2.png",
		"shield/run/left/sprite_3.png",
		"shield/run/left/sprite_4.png",
		"shield/run/left/sprite_5.png",
		"shield/run/left/sprite_6.png",
		"shield/run/left/sprite_7.png",
		"shield/run/left/sprite_8.png",
		"shield/run/left/sprite_9.png",
		"shield/run/left/sprite_10.png",
		"end"
	};

	char Rmovefilename[][50]
	{
		"shield/run/right/sprite_1.png",
		"shield/run/right/sprite_2.png",
		"shield/run/right/sprite_3.png",
		"shield/run/right/sprite_4.png",
		"shield/run/right/sprite_5.png",
		"shield/run/right/sprite_6.png",
		"shield/run/right/sprite_7.png",
		"shield/run/right/sprite_8.png",
		"shield/run/right/sprite_9.png",
		"shield/run/right/sprite_10.png",
		"end"
	};

	char standfilename[][50]
	{
		"shield/stand/sprite_1.png",
		"shield/stand/sprite_2.png",
		"shield/stand/sprite_3.png",
		"shield/stand/sprite_4.png",
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
	moveAction = nullptr;
	getUnit()->runAction(nowRunAction);
}


	//여기는 빠따조의 영역이다!~!~!~!~!~!~!~!~!~!~!~!~!~!~!@#$%^

BottonUnit::BottonUnit()
{
	getStatus()->attack_range = 100;
	getStatus()->attack_speed = 3;
	getStatus()->health = 50;
	getStatus()->max_health = getStatus()->health;
	getStatus()->attack_power = 18;
	getStatus()->shield_point = 100;
}

BottonUnit::~BottonUnit()
{
}

void BottonUnit::standAnimation(int direction)
{
	if (!getStatus()->canRunF)
		return;

	getUnit()->stopAction(nowRunAction);
	if (moveAction != nullptr)
	{
		getUnit()->stopAction(moveAction);
		moveAction = nullptr;
	}


	nowRunAction = standAction->clone();
	getUnit()->runAction(nowRunAction);
}

void BottonUnit::moveAnimation(int direction, Vec2 movepos)
{
	if (!getStatus()->canRunF)
		return;

	getUnit()->stopAction(nowRunAction);
	if (moveAction != nullptr)
	{
		getUnit()->stopAction(moveAction);
		moveAction = nullptr;
	}

	float length = sqrt(pow(getUnit()->getPosition().x - movepos.x, 2) + pow(getUnit()->getPosition().y - movepos.y, 2));

	moveAction = Sequence::create(MoveTo::create(length * 0.01f, movepos), CallFunc::create([&]() {standAnimation(0);}), nullptr);


	getUnit()->runAction(moveAction);

	if (direction < 0)
	{

		nowRunAction = LeftmoveAction->clone();
		getUnit()->runAction(nowRunAction);
	}
	else
	{

		nowRunAction = RigthmoveAction->clone();
		getUnit()->runAction(nowRunAction);
	}
}

void BottonUnit::attackAnimation(int direction)
{
	if (!getStatus()->canRunF)
		return;

	getUnit()->stopAction(nowRunAction);

	if (moveAction != nullptr)
	{
		getUnit()->stopAction(moveAction);
		moveAction = nullptr;
	}

	if (direction < 0)
	{
		nowRunAction = (RepeatForever*)Sequence::create(LeftattackAction->clone(), CallFunc::create([&]() {standAnimation(0);  getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
	else
	{
		nowRunAction = (RepeatForever*)Sequence::create(RightattackAction->clone(), CallFunc::create([&]() {standAnimation(0);  getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
}

void BottonUnit::hittedAnimation(int direction)
{


	getUnit()->stopAction(nowRunAction);

	if (moveAction != nullptr)
	{
		getUnit()->stopAction(moveAction);
		moveAction = nullptr;
	}


	if (direction < 0)
	{
		nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.7f), LefthittedAction->clone(), CallFunc::create([&]() {standAnimation(0);  getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
	else
	{
		nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.7f), RighthittedAction->clone(), CallFunc::create([&]() {standAnimation(0);  getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
}

void BottonUnit::deadAnimation(int direction)
{
	//if (!getStatus()->canRunF)
	//	return;
	//
	//getUnit()->stopAction(nowRunAction);
	//
	//if (moveAction != nullptr)
	//{
	//	getUnit()->setPosition(Vec2(getUnit()->getPosition().x + 30, getUnit()->getPosition().y));
	//	getUnit()->stopAction(moveAction);
	//	moveAction = nullptr;
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

void BottonUnit::Animateinit(Layer * layer)
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



	char Leftdeadfilename[][50]
	{
		"botton/dead/left/sprite_1.png",
		"botton/dead/left/sprite_2.png",
		"botton/dead/left/sprite_3.png",
		"botton/dead/left/sprite_4.png",
		"botton/dead/left/sprite_5.png",
		"botton/dead/left/sprite_6.png",
		"botton/dead/left/sprite_7.png",
		"botton/dead/left/sprite_8.png",
		"botton/dead/left/sprite_9.png",
		"botton/dead/left/sprite_10.png",
		"botton/dead/left/sprite_11.png",
		"botton/dead/left/sprite_12.png",
		"botton/dead/left/sprite_13.png",
		"botton/dead/left/sprite_14.png",
		"end"
	};



	char Rightdeadfilename[][50]
	{
		"botton/dead/right/sprite_1.png",
		"botton/dead/right/sprite_2.png",
		"botton/dead/right/sprite_3.png",
		"botton/dead/right/sprite_4.png",
		"botton/dead/right/sprite_5.png",
		"botton/dead/right/sprite_6.png",
		"botton/dead/right/sprite_7.png",
		"botton/dead/right/sprite_8.png",
		"botton/dead/right/sprite_9.png",
		"botton/dead/right/sprite_10.png",
		"botton/dead/right/sprite_11.png",
		"botton/dead/right/sprite_12.png",
		"botton/dead/right/sprite_13.png",
		"botton/dead/right/sprite_14.png",
		"end"
	};



	char Lefthittedfilename[][50]
	{
		"botton/hitted/left/sprite_1.png",
		"botton/hitted/left/sprite_2.png",
		"botton/hitted/left/sprite_3.png",
		"botton/hitted/left/sprite_4.png",
		"botton/hitted/left/sprite_5.png",
		"end"
	};



	char Righthittedfilename[][50]
	{
		"botton/hitted/right/sprite_1.png",
		"botton/hitted/right/sprite_2.png",
		"botton/hitted/right/sprite_3.png",
		"botton/hitted/right/sprite_4.png",
		"botton/hitted/right/sprite_5.png",
		"end"
	};

	char Leftattackfilename[][50]
	{
		"botton/attack/left/sprite_1.png",
		"botton/attack/left/sprite_2.png",
		"botton/attack/left/sprite_3.png",
		"botton/attack/left/sprite_4.png",
		"botton/attack/left/sprite_5.png",
		"botton/attack/left/sprite_6.png",
		"botton/attack/left/sprite_7.png",
		"botton/attack/left/sprite_8.png",
		"botton/attack/left/sprite_9.png",
		"botton/attack/left/sprite_10.png",
		"botton/attack/left/sprite_1.png",
		"end"
	};

	char Rightattackfilename[][50]
	{
		"botton/attack/right/sprite_1.png",
		"botton/attack/right/sprite_2.png",
		"botton/attack/right/sprite_3.png",
		"botton/attack/right/sprite_4.png",
		"botton/attack/right/sprite_5.png",
		"botton/attack/right/sprite_6.png",
		"botton/attack/right/sprite_7.png",
		"botton/attack/right/sprite_8.png",
		"botton/attack/right/sprite_9.png",
		"botton/attack/right/sprite_10.png",
		"botton/attack/right/sprite_1.png",
		"end"
	};

	char Lmovefilename[][50]
	{
		"botton/run/left/sprite_1.png",
		"botton/run/left/sprite_2.png",
		"botton/run/left/sprite_3.png",
		"botton/run/left/sprite_4.png",
		"botton/run/left/sprite_5.png",
		"botton/run/left/sprite_6.png",
		"botton/run/left/sprite_7.png",
		"botton/run/left/sprite_8.png",
		"botton/run/left/sprite_9.png",
		"botton/run/left/sprite_10.png",
		"end"
	};

	char Rmovefilename[][50]
	{
		"botton/run/right/sprite_1.png",
		"botton/run/right/sprite_2.png",
		"botton/run/right/sprite_3.png",
		"botton/run/right/sprite_4.png",
		"botton/run/right/sprite_5.png",
		"botton/run/right/sprite_6.png",
		"botton/run/right/sprite_7.png",
		"botton/run/right/sprite_8.png",
		"botton/run/right/sprite_9.png",
		"botton/run/right/sprite_10.png",
		"end"
	};

	char standfilename[][50]
	{
		"botton/stand/sprite_1.png",
		"botton/stand/sprite_2.png",
		"botton/stand/sprite_3.png",
		"botton/stand/sprite_4.png",
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
		sprite->setPosition(Vec2(100, 100 * i + 100));
		sprite->setVisible(TEST);
		layer->addChild(sprite, 100000);
	}


	nowRunAction = standAction->clone();
	moveAction = nullptr;
	getUnit()->runAction(nowRunAction);
}

//여기 총잡이들 있엉

GunnerUnit::GunnerUnit()
{
	getStatus()->attack_range = 300;
	getStatus()->attack_speed = 2.f;
	getStatus()->health = 100;
	getStatus()->max_health = getStatus()->health;
	getStatus()->attack_power = 18;
	getStatus()->shield_point = 100;
}

GunnerUnit::~GunnerUnit()
{
}

void GunnerUnit::standAnimation(int direction)
{
	if (!getStatus()->canRunF)
		return;

	getUnit()->stopAction(nowRunAction);
	if (moveAction != nullptr)
	{
		getUnit()->stopAction(moveAction);
		moveAction = nullptr;
	}


	nowRunAction = standAction->clone();
	getUnit()->runAction(nowRunAction);
}

void GunnerUnit::moveAnimation(int direction, Vec2 movepos)
{
	if (!getStatus()->canRunF)
		return;

	getUnit()->stopAction(nowRunAction);
	if (moveAction != nullptr)
	{
		getUnit()->stopAction(moveAction);
		moveAction = nullptr;
	}

	float length = sqrt(pow(getUnit()->getPosition().x - movepos.x, 2) + pow(getUnit()->getPosition().y - movepos.y, 2));

	moveAction = Sequence::create(MoveTo::create(length * 0.01f, movepos), CallFunc::create([&]() {standAnimation(0);}), nullptr);


	getUnit()->runAction(moveAction);

	if (direction < 0)
	{

		nowRunAction = LeftmoveAction->clone();
		getUnit()->runAction(nowRunAction);
	}
	else
	{

		nowRunAction = RigthmoveAction->clone();
		getUnit()->runAction(nowRunAction);
	}
}

void GunnerUnit::attackAnimation(int direction)
{
	if (!getStatus()->canRunF)
		return;

	getUnit()->stopAction(nowRunAction);

	if (moveAction != nullptr)
	{
		getUnit()->stopAction(moveAction);
		moveAction = nullptr;
	}

	if (direction < 0)
	{
		nowRunAction = (RepeatForever*)Sequence::create(LeftattackAction->clone(), CallFunc::create([&]() {standAnimation(0);  getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
	else
	{
		nowRunAction = (RepeatForever*)Sequence::create(RightattackAction->clone(), CallFunc::create([&]() {standAnimation(0);  getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
}

void GunnerUnit::hittedAnimation(int direction)
{
	getUnit()->stopAction(nowRunAction);

	if (moveAction != nullptr)
	{
		getUnit()->stopAction(moveAction);
		moveAction = nullptr;
	}


	if (direction < 0)
	{
		nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.7f), LefthittedAction->clone(), CallFunc::create([&]() {standAnimation(0);  getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
	else
	{
		nowRunAction = (RepeatForever*)Sequence::create(DelayTime::create(0.7f), RighthittedAction->clone(), CallFunc::create([&]() {standAnimation(0);  getStatus()->canRunF = true;}), nullptr);
		getUnit()->runAction(nowRunAction);
	}
}

void GunnerUnit::deadAnimation(int direction)
{
	//if (!getStatus()->canRunF)
	//	return;
	//
	//getUnit()->stopAction(nowRunAction);
	//
	//if (moveAction != nullptr)
	//{
	//	getUnit()->setPosition(Vec2(getUnit()->getPosition().x + 30, getUnit()->getPosition().y));
	//	getUnit()->stopAction(moveAction);
	//	moveAction = nullptr;
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

void GunnerUnit::Animateinit(Layer * layer)
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



	char Leftdeadfilename[][50]
	{
		"botton/dead/left/sprite_1.png",
		"botton/dead/left/sprite_2.png",
		"botton/dead/left/sprite_3.png",
		"botton/dead/left/sprite_4.png",
		"botton/dead/left/sprite_5.png",
		"botton/dead/left/sprite_6.png",
		"botton/dead/left/sprite_7.png",
		"botton/dead/left/sprite_8.png",
		"botton/dead/left/sprite_9.png",
		"botton/dead/left/sprite_10.png",
		"botton/dead/left/sprite_11.png",
		"botton/dead/left/sprite_12.png",
		"botton/dead/left/sprite_13.png",
		"botton/dead/left/sprite_14.png",
		"end"
	};



	char Rightdeadfilename[][50]
	{
		"botton/dead/right/sprite_1.png",
		"botton/dead/right/sprite_2.png",
		"botton/dead/right/sprite_3.png",
		"botton/dead/right/sprite_4.png",
		"botton/dead/right/sprite_5.png",
		"botton/dead/right/sprite_6.png",
		"botton/dead/right/sprite_7.png",
		"botton/dead/right/sprite_8.png",
		"botton/dead/right/sprite_9.png",
		"botton/dead/right/sprite_10.png",
		"botton/dead/right/sprite_11.png",
		"botton/dead/right/sprite_12.png",
		"botton/dead/right/sprite_13.png",
		"botton/dead/right/sprite_14.png",
		"end"
	};



	char Lefthittedfilename[][50]
	{
		"botton/hitted/left/sprite_1.png",
		"botton/hitted/left/sprite_2.png",
		"botton/hitted/left/sprite_3.png",
		"botton/hitted/left/sprite_4.png",
		"botton/hitted/left/sprite_5.png",
		"end"
	};



	char Righthittedfilename[][50]
	{
		"botton/hitted/right/sprite_1.png",
		"botton/hitted/right/sprite_2.png",
		"botton/hitted/right/sprite_3.png",
		"botton/hitted/right/sprite_4.png",
		"botton/hitted/right/sprite_5.png",
		"end"
	};

	char Leftattackfilename[][50]
	{
		"gunner/attack/left/sprite_1.png",
		"gunner/attack/left/sprite_2.png",
		"gunner/attack/left/sprite_3.png",
		"gunner/attack/left/sprite_4.png",
		"gunner/attack/left/sprite_5.png",
		"gunner/attack/left/sprite_6.png",
		"gunner/attack/left/sprite_7.png",
		"gunner/attack/left/sprite_8.png",
		"gunner/attack/left/sprite_9.png",
		"gunner/attack/left/sprite_10.png",
		"gunner/attack/left/sprite_11.png",
		"gunner/attack/left/sprite_12.png",
		"gunner/attack/left/sprite_13.png",
		"gunner/attack/left/sprite_14.png",
		"gunner/attack/left/sprite_15.png",
		"gunner/attack/left/sprite_16.png",
		"gunner/attack/left/sprite_17.png",
		"gunner/attack/left/sprite_18.png",
		"gunner/attack/left/sprite_19.png",
		"gunner/attack/left/sprite_20.png",
		"gunner/attack/left/sprite_21.png",
		"gunner/attack/left/sprite_1.png",
		"end"
	};

	char Rightattackfilename[][50]
	{
		"gunner/attack/right/sprite_1.png",
		"gunner/attack/right/sprite_2.png",
		"gunner/attack/right/sprite_3.png",
		"gunner/attack/right/sprite_4.png",
		"gunner/attack/right/sprite_5.png",
		"gunner/attack/right/sprite_6.png",
		"gunner/attack/right/sprite_7.png",
		"gunner/attack/right/sprite_8.png",
		"gunner/attack/right/sprite_9.png",
		"gunner/attack/right/sprite_10.png",
		"gunner/attack/right/sprite_11.png",
		"gunner/attack/right/sprite_12.png",
		"gunner/attack/right/sprite_13.png",
		"gunner/attack/right/sprite_14.png",
		"gunner/attack/right/sprite_15.png",
		"gunner/attack/right/sprite_16.png",
		"gunner/attack/right/sprite_17.png",
		"gunner/attack/right/sprite_18.png",
		"gunner/attack/right/sprite_19.png",
		"gunner/attack/right/sprite_20.png",
		"gunner/attack/right/sprite_21.png",
		"gunner/attack/right/sprite_1.png",
		"end"
	};

	char Lmovefilename[][50]
	{
		"gunner/run/left/sprite_1.png",
		"gunner/run/left/sprite_2.png",
		"gunner/run/left/sprite_3.png",
		"gunner/run/left/sprite_4.png",
		"gunner/run/left/sprite_5.png",
		"gunner/run/left/sprite_6.png",
		"gunner/run/left/sprite_7.png",
		"gunner/run/left/sprite_8.png",
		"gunner/run/left/sprite_9.png",
		"gunner/run/left/sprite_10.png",
		"end"
	};

	char Rmovefilename[][50]
	{
		"gunner/run/right/sprite_1.png",
		"gunner/run/right/sprite_2.png",
		"gunner/run/right/sprite_3.png",
		"gunner/run/right/sprite_4.png",
		"gunner/run/right/sprite_5.png",
		"gunner/run/right/sprite_6.png",
		"gunner/run/right/sprite_7.png",
		"gunner/run/right/sprite_8.png",
		"gunner/run/right/sprite_9.png",
		"gunner/run/right/sprite_10.png",
		"end"
	};

	char standfilename[][50]
	{
		"gunner/stand/sprite_1.png",
		"gunner/stand/sprite_2.png",
		"gunner/stand/sprite_3.png",
		"gunner/stand/sprite_4.png",
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
		sprite->setPosition(Vec2(100, 100 * i + 100));
		sprite->setVisible(TEST);
		layer->addChild(sprite, 100000);
	}


	nowRunAction = standAction->clone();
	moveAction = nullptr;
	getUnit()->runAction(nowRunAction);
}

void GunnerUnit::attackUnit()
{
	struct Closest
	{
		float closest = 0;
		Citizen* closestCitizen = 0;
	};

	Closest closest;




	if (delay)
	{
		for (int i = 0;i < UnitsAddress::getInstance()->getMaxUnitsnum();i++)									//가장 가까운 경찾 찾기
		{																										//
			auto tmp = UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i);							//
																												//
			if (tmp == nullptr)																					//
				continue;																						//
																												//
			float range = attackRange(tmp->unitaddress->getUnit(), getStatus()->attack_range);					//
																												//
			if (range != 0 && (closest.closest == 0 || closest.closest > range))								//
			{																									//
				closest.closestCitizen = (Citizen*)tmp->unitaddress;											//
				closest.closest = range;																		//
			}																									//
		}																										//
		if (closest.closestCitizen == nullptr) return;															//가까운게 없을 시 리턴

		createBullet(closest.closestCitizen, closest.closest);


		attackAnimation(-1);

		getUnit()->runAction(Sequence::create(DelayTime::create(getStatus()->attack_speed), CallFunc::create([&]() {delay = true;}), nullptr));

		delay = false;
	}



//	m_fDegree = atan2f((float)B.y - A.y, (float)B.x - A.x) * 180 / 3.1415f;
}

void GunnerUnit::createBullet(Citizen * closestCitizen, float closest)
{
	if (closest == 9999)
	{
		delete bullet;
		bullet = nullptr;
		return;
	}
	if (bullet == nullptr)
	{
		tmpclosestCitizen = closestCitizen;
		getUnit()->runAction(Sequence::create(CallFunc::create([&]() {tmpclosestCitizen->getUnit()->setColor(Color3B::RED);}), DelayTime::create(3.f), CallFunc::create([&]() {this->bullet = new Bullet; this->bullet->init(this, tmpclosestCitizen);}), nullptr));
	}
}

//		총잡이 총알

GunnerUnit::Bullet::Bullet()
{
}

GunnerUnit::Bullet::~Bullet()
{
}

void GunnerUnit::Bullet::init(GunnerUnit* parent_, Citizen* citizen)
{
	targetUnit = citizen;

	parent = parent_;

	bulletimage = Sprite::create("gunner/bullet/sprite_1.png");
	bulletimage->setPosition(parent->getUnit()->getPosition());
	//bulletimage->setScale(0.3f);
	//parent->getUnit()->addChild(bulletimage);
	parent->getUnit()->getParent()->addChild(bulletimage);
	damage = parent->getStatus()->attack_power;

	bulletimage->runAction(RepeatForever::create((Sequence::create((ActionInterval*)CallFunc::create([&]() {this->Collision();/* this->Exitscreen();*/}), nullptr))));
	bulletimage->runAction(Sequence::create(DelayTime::create(2.5f), CallFunc::create([&]() {this->Collision(true);}), nullptr));

	
	auto citizenpos = citizen->getUnit()->getPosition();
	auto bulletpos = bulletimage->getPosition();

	float degree = atan2f(citizenpos.y - bulletpos.y, citizenpos.x - bulletpos.x) /** 180 / 3.14f + 90*/;

	//bulletimage->setRotation(degree);
	bulletpos.x = bulletpos.x + cos(degree) * 1000;
	bulletpos.y = bulletpos.y + sin(degree) * 1000;

	log("degree %f", degree);


	bulletimage->runAction(Sequence::create(MoveTo::create(1.f, bulletpos), CallFunc::create([&]() {this->Collision(true);}), nullptr));
	//bulletimage->runAction(Sequence::create(MoveTo::create(1.f, Vec2(citizen->getUnit()->getPosition().x , citizen->getUnit()->getPosition().y)), CallFunc::create([&]() {this->Collision(true);}), nullptr));
}


void GunnerUnit::Bullet::Collision(bool isend)
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
		if (UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i) == nullptr || !UnitsAddress::getInstance()->searchUnit(parent))
			break;


		auto tmp = (Citizen*)UnitsAddress::getInstance()->getUnits(UnitsAddress::CITIZEN, i)->unitaddress;

		Vec2 bulletpos = bulletimage->getPosition();
		auto tmpcitizen = tmp->getUnit();
		
		//if (tmpcitizen->getPosition().x - (tmpcitizen->getContentSize().width / 2) < bulletpos.x && bulletpos.x < tmpcitizen->getPosition().x + (tmpcitizen->getContentSize().width / 2) && 
		//	tmpcitizen->getPosition().y - (tmpcitizen->getContentSize().height / 2) < bulletpos.y && bulletpos.y < tmpcitizen->getPosition().y + (tmpcitizen->getContentSize().height / 2)
		//	/*bulletimage->getBoundingBox().containsPoint(tmp->getUnit()->getPosition())*/)
		{
			targetUnit->getUnit()->setColor(Color3B::WHITE);

			tmp->hittedUnit(damage, -1);
			bulletimage->cleanup();
			parent->getUnit()->getParent()->removeChild(bulletimage);
			parent->createBullet(nullptr, 9999);
			
		}
	}
}

void GunnerUnit::Bullet::Exitscreen()
{
	if (bulletimage == nullptr)
		return;

	//log("Gunner's num %d", UnitsAddress::getInstance()->searchUnitnum(parent));

	
	if (!(0 < bulletimage->getPosition().x && bulletimage->getPosition().x < 1280 && 0 < bulletimage->getPosition().y && bulletimage->getPosition().y < 720))
		Collision(true);
}
