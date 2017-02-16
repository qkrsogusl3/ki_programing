#include "Juggler.h"
#include "JugglerParts.h"
#include "JugglerFiniteState.h"

#define PI 3.14159
#define LIFEPARTS_KEY -1

bool Juggler::init()
{
	if (!Enemy::init())
	{
		return false;
	}
	mCircleCount = 12;
	mCircleRadius = 90;
	mCirclePivot = (PI * 2) * 0.75;

	auto lifeParts = JugglerCircle::create();
	lifeParts->SetState(JugglerCircle::State::State_None);
	lifeParts->GetSprite()->setColor(Color3B::RED);
	this->AddParts(LIFEPARTS_KEY, lifeParts, true);

	JugglerCircle * circle = nullptr;
	//Vec2 pos;
	for (int i = 0; i < mCircleCount; i++)
	{
		circle = JugglerCircle::create();
		circle->SetRotateData(CircleRotateData(i, mCircleCount, mCircleRadius, mCirclePivot));
		this->AddParts(i, circle);
		if (i == 0)
		{
			circle->GetSprite()->setColor(Color3B::GREEN);
		}
	}

	this->AddState(State::State_Idle, JugglerIdleState::Create(this));
	this->ChangeState(State::State_Idle);


	return true;
}

void Juggler::OnActivate(bool isActive)
{

}

int Juggler::GetCircleCount()
{
	return mCircleCount;
}

float Juggler::GetCircleRadius()
{
	return mCircleRadius;
}

float Juggler::GetCirclePivot()
{
	return mCirclePivot;
}

