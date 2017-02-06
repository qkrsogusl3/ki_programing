#ifndef __CACTOR_H__
#define __CACTOR_H__

#include "cocos2d.h"
#include "Actor.h"

using namespace cocos2d;

class SpriteAnimator;

class Player : public Actor
{
private:
	enum State
	{
		Idle = 0,
		Move = 1,
		Roll = 2,
	};

	SpriteAnimator * mSpriteAnim = nullptr;

	bool mIsControl = false;
	Player::State mState;

	//hit
	int mHP = 0;
	float mHitDelay = 0;
	float mCurrentHitDelay = 0;
	//move
	float mMoveSpeedPower = 0;
	Vec2 mMoveDir;
	//roll
	float mRollDistance;
	float mRollDuration;
	float mRollRadian;
	
	Vec2 mRollStartPos;
	Vec2 mRollDestPos;
	float mRollCurTime;


	Size mMoveArea;

	virtual ~Player();
public:
	CREATE_FUNC(Player);

	//����������Ŭ �������̵�
	virtual bool init() override;
	virtual void update(float dt) override;

	//Inputs
	bool onTouchBegan(Touch * touch, Event * unused_event);
	void onTouchMoved(Touch * touch, Event * unused_event);

	//getter,setter
	Sprite * GetSprite();
	void SetIsControl(bool tIsControl);
	bool GetIsControl();
	void SetMoveDir(Vec2 dir);
	void SetMoveArea(Size area);

	void Hit();
	void OnRoll(float rollRadian);

};

#endif // !__CACTOR_H__
