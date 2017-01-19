#include "CActor.h"
#include "SpriteAnimator.h"
#include "CBulletFactory.h"
#include "CEnemy.h"
#include "CBulletDirection.h"
#include "CBulletCurve.h"

#define USE_MOUSE_POSITION true

#define BULLET_MAX_COUNT 30
#define BULLET_INTERVAL 0.1
#define BULLET_SPEED 600
#define IS_BULLET_3WAY false

CActor * CActor::create(Layer * tBulletLayer)
{
	auto actor = CActor::create();
	if (actor != nullptr)
	{
		actor->mBulletLayer = tBulletLayer;
		actor->lateInit();
	}
	return actor;
}

bool CActor::lateInit()
{
	if (!CUnit::lateInit())
	{
		return false;
	}

	mSpriteAnim = SpriteAnimator::create("actor", 0, 20, 0.1);
	mSpriteAnim->runAni();
	mSpriteAnim->setScale(1.8);
	this->addChild(mSpriteAnim);

	mHP = 10;
	mFollowSpeed = 15.0f;

	mBulletInterval = BULLET_INTERVAL;
	mBullets.reserve(BULLET_MAX_COUNT);

	CBullet * tTempBullet = nullptr;
	
#if IS_BULLET_3WAY
	for (int i = 0; i < BULLET_MAX_COUNT; i++)
	{
		
		tTempBullet = CBulletFactory::creataBullet3Way(
			DirSpeed(Vec2(1, 0), BULLET_SPEED),
			DirSpeed(Vec2(1, -0.3), BULLET_SPEED),
			DirSpeed(Vec2(1, 0.3), BULLET_SPEED));

		mBullets.pushBack(tTempBullet);
		mBulletLayer->addChild(tTempBullet);
	}
#else
	for (int i = 0; i < 30; i++)
	{
		auto tCurve = CBulletFactory::creataBulletCurveSide3Way(
			DirSpeed(Vec2(1,1),600),
			DirSpeed(Vec2(1,0), 600),
			DirSpeed(Vec2(1,-1),600),
			500
		);
		mBullets.pushBack(tCurve);
		mBulletLayer->addChild(tCurve);
	}
#endif


#if USE_MOUSE_POSITION

	auto tMouseListener = EventListenerMouse::create();
	tMouseListener->onMouseMove = [=](Event * event) 
	{
		auto tMouse = (EventMouse *)event;
		mLatestInputPos = tMouse->getLocationInView();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tMouseListener, this);

#else

	auto tTouchListener = EventListenerTouchOneByOne::create();
	tTouchListener->setSwallowTouches(true);
	tTouchListener->onTouchBegan = CC_CALLBACK_2(CActor::onTouchBegan, this);
	tTouchListener->onTouchMoved = CC_CALLBACK_2(CActor::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tTouchListener, this);

#endif
	mLatestInputPos = this->getPosition();

	this->scheduleUpdate();
	return true;
}


void CActor::update(float dt)
{
	if (mCurrentHitDelay >= 0)
	{
		mCurrentHitDelay -= dt;
	}

	if (mIsControl)
	{
		mLatestShotTime += dt;
		if (mLatestShotTime >= mBulletInterval)
		{
			if (mBullets.at(mCurrentBulletIndex)->getIsAlive() == false)
			{
				Vec2 tPos = this->getPosition();
				tPos.x += mSpriteAnim->getContentSize().width;
				tPos.y += mSpriteAnim->getContentSize().height * 0.5;

				mBullets.at(mCurrentBulletIndex)->shot(tPos);
				mCurrentBulletIndex++;
				if (mCurrentBulletIndex >= mBullets.size())
				{
					mCurrentBulletIndex = 0;
				}
			}
			mLatestShotTime = 0;
		}

		Vec2 tPos = this->getPosition();
		tPos = ccpLerp(tPos, mLatestInputPos, dt * mFollowSpeed);
		this->setPosition(tPos);
	}
}

void CActor::setIsControl(bool tIsControl)
{
	mIsControl = tIsControl;
}

bool CActor::getIsControl()
{
	return mIsControl;
}


//���ڷ� �Ѿ�� ���ʹ̿� �����浹üũ��
//���� ���Ͱ� �����ϴ� �Ѿ˿��� ���ʹ̸�
//�����Ͽ� �浹���� �˻� �� ���ʹ� Ÿ��
void CActor::checkCollisionByEnemy(CEnemy * enemy)
{
	Rect tEnemyBox = utils::getCascadeBoundingBox(enemy);
	Rect tActorBox = utils::getCascadeBoundingBox(this);

	if (tActorBox.intersectsRect(tEnemyBox))
	{
		//log("collision");
	}

	if (mBullets.size() > 0)
	{
		for (int i = 0; i < mBullets.size(); i++)
		{
			mBullets.at(i)->checkCollisionEnemy(enemy);
		}
	}
}

float CActor::getRedius()
{
	return mSpriteAnim->getSprite()->getContentSize().width / 2;
}


void CActor::hit()
{
	if (mCurrentHitDelay <= 0)
	{
		mHP--;
		log("parts hit count : %d", mHP);
		mCurrentHitDelay = mHitDelay;

		if (mHP <= 0)
		{
			mIsControl = false;
			mIsAlive = false;
		}

		if (mIsControl)
		{
			auto tHitSeq = Sequence::create(
				TintTo::create(0.05, Color3B::RED),
				TintTo::create(0.05, Color3B::WHITE),
				nullptr
			);
			mSpriteAnim->getSprite()->runAction(tHitSeq);
		}
	}
}


CActor::~CActor()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}


bool CActor::onTouchBegan(Touch * touch, Event * unused_event)
{
	mLatestInputPos = touch->getLocation();
	//this->setPosition(touch->getLocation());
	return true;
}

void CActor::onTouchMoved(Touch * touch, Event * unused_event)
{
	mLatestInputPos = touch->getLocation();
	//this->setPosition(touch->getLocation());
}

