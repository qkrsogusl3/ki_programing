#ifndef __ARROW_H__
#define __ARROW_H__

#include "cocos2d.h"
#include "Actor.h"

using namespace cocos2d;

class Player;

class Arrow : public Actor
{
public:
	enum State
	{
		State_Idle = 0,
		State_LockOn = 1,
		State_Shot = 2,
		State_Drop = 3,
	};
private:
	
	Sprite * mSprite = nullptr;
	Player * mPlayer = nullptr;

	State mState;
	//�߻� ����
	Vec2 mMoveDirection;
	
	//�ִ� �ӷ�
	float mMaxSpeedPower = 0;
	//���� �ӷ�
	float mCurrentSpeedPower = 0;
	//�ִ� �ӷ¸� �������� ���� �� ����
	float mDecelRatio = 0;

	//�浹
	bool mIsPrevCollision = false;
	bool mIsCollision = false;

	bool mIsReturnArrow = false;

	//�� ���� �� ������Ʈ
	void updateLock(float dt);
	void updateShot(float dt);
	void updateDrop(float dt);

public:
	CREATE_FUNC(Arrow);
	
	virtual bool init() override;
	virtual void update(float dt) override;

	//get,set
	Arrow::State GetState();
	void SetReturnArrow(bool isReturn);


	void InitWithPlayer(Player * player);
	void LockOn(Vec2 dir);
	void DisableLockOn();
	void Shot();
	void OnCollisionOther(bool isCollision, Actor * other,Vec2 normal = Vec2::ZERO);

	bool IsShooting();
};

#endif // !__ARROW_H__
