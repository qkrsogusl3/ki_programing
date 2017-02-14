#pragma once

#include "EnemyParts.h"

class BossHead : public EnemyParts
{
public:
	CREATE_FUNC(BossHead);
	virtual bool init() override;

	virtual const Size GetPartsSize() override;
};

class BossBody : public EnemyParts
{
public:
	CREATE_FUNC(BossBody);
	virtual bool init() override;

	virtual const Size GetPartsSize() override;
};
 
class BossHand : public EnemyParts
{
public:
	enum HandDir
	{
		HandDir_Left = -1,
		HandDir_Right = 1,
	};
private:
	enum State
	{
		Idle = 0,
		Attack_Shot = 1,
	};
	BossHand::State mState;

	char mHandDirection = 0;
	Vec2 mInitPosision;

	float mCurrentTime = 0;
	Vec2 mAttackTargetPos;

	void UpdateAttack(float dt);
public:
	CREATE_FUNC(BossHand);
	virtual bool init() override;
	virtual void update(float dt) override;
	virtual void onEnter() override;

	void InitHand(HandDir dir);

	//get,set
	Vec2 GetInitPosition();
	char GetHandDirection();

	void OnAttack(Vec2 pos);
};