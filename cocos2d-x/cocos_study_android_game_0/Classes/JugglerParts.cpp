#include "JugglerParts.h"
#include "StopWatch.h"
#include "EasingFunc.h"
#include "Enemy.h"

#define PI 3.14159

#pragma region JuglerCircle

bool JugglerCircle::init()
{
	if (!EnemyParts::init())
	{
		return false;
	}

	auto sprite = this->SetSprite(Sprite::create("enemy/whitemask.png"));
	//sprite->getTexture()->setAliasTexParameters();
	


	mIdleWatch = StopWatch::create();
	mIdleWatch->OnStart();
	this->addChild(mIdleWatch);
	mAttackWatch = StopWatch::create();
	mAttackWatch->OnStart();
	this->addChild(mAttackWatch);

	this->scheduleUpdate();
	return true;
}

void JugglerCircle::update(float dt)
{
	
	switch (mState)
	{
	case State::State_Idle:
		UpdateIdle(dt);
		break;
	case State::State_SeqAttack:
		UpdateAttack(dt);
		break;
	}
}
void JugglerCircle::UpdateIdle(float dt)
{
	mIdleWatch->OnUpdate(dt *  (0.5 * mRotateSpeedRatio));
	float delta = PI * mIdleWatch->GetAccTime();

	mIdlePosition.x = cos(
		((PI * 2) * ((float)mRotateData.circleIndex / mRotateData.circleCount) + delta)
		+ mRotateData.circlePivot + 0) * (mRotateData.circleRadius * mCircleRadiusRatio);
	mIdlePosition.y = sin(
		((PI * 2) * ((float)mRotateData.circleIndex / mRotateData.circleCount) + delta)
		+ mRotateData.circlePivot + 0) * (mRotateData.circleRadius * mCircleRadiusRatio);
	if (delta >= PI * 2)
	{
		mIdleWatch->OnReset();
	}

	this->setPosition(mIdlePosition);
}
void JugglerCircle::UpdateAttack(float dt)
{
	mAttackWatch->OnUpdate(dt);

	Vec2 pos;
	//pos += EasingFunc::EaseSinInOut(sin((PI / mAttackDuration) * mAttackWatch->GetAccTime()) * mAttackDuration, mAttackStartPos, mAttackTargetPos - mAttackStartPos, mAttackDuration);
	pos.x += EasingFunc::EaseQuarticIn(sin((PI / mAttackDuration) * mAttackWatch->GetAccTime()) * mAttackDuration, mAttackStartPos.x, mAttackTargetPos.x - mAttackStartPos.x, mAttackDuration);
	pos.y += EasingFunc::EaseLinear(sin((PI / mAttackDuration) * mAttackWatch->GetAccTime()) * mAttackDuration, mAttackStartPos.y, mAttackTargetPos.y - mAttackStartPos.y, mAttackDuration);

	this->setPosition(pos);

	if (mAttackWatch->GetAccTime() >= mAttackDuration)
	{
		mAttackWatch->OnReset();
		SetState(State::State_None);
	}
}

void JugglerCircle::SetState(JugglerCircle::State state)
{
	mPrevState = mState;
	mState = state;
}

JugglerCircle::State JugglerCircle::GetState()
{
	return mState;
}

void JugglerCircle::SetRotateData(CircleRotateData data)
{
	mRotateData = data;
}

void JugglerCircle::SetRotateSpeedRatio(float ratio)
{
	mRotateSpeedRatio = ratio;
}

float JugglerCircle::GetRotateSpeedRatio()
{
	return mRotateSpeedRatio;
}

void JugglerCircle::SetCircleRadiusRatio(float ratio)
{
	mCircleRadiusRatio = ratio;
}

float JugglerCircle::GetCircleRadiusRatio()
{
	return mCircleRadiusRatio;
}


void JugglerCircle::OnAttack(Vec2 targetPos, float duration)
{

	mAttackStartPos = this->getPosition();

	mAttackTargetPos =  ((targetPos - Vec2::ZERO).getNormalized() * 700);
	
	mAttackDuration = duration == 0 ? 1 : duration;
	SetState(State::State_SeqAttack);
}



#pragma endregion
