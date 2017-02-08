#ifndef __SCENEPLAY_H__
#define __SCENEPLAY_H__

#include "cocos2d.h"
#include "Player.h"
#include "Arrow.h"


using namespace cocos2d;

class StopWatch;
class Enemy;

enum TouchState
{
	None = 0,
	Move = 1,
	Shot = 2
};

class ScenePlay : public LayerColor
{
private:
	//���̾� ����
	Node * mRenderNode = nullptr;//this �������� �ֻ��� ���
	Node * mUINode = nullptr;//RenderNode�� ���ϴ� UI�κ� ��� ex) ��Ʈ�ѷ�,...
	Node * mPlayNode = nullptr;//UI���� ���� ������ �÷��� �κ� ���, ex) ��,�÷��̾�,��,...

	//player
	Player * mPlayer = nullptr;
	Arrow * mArrow = nullptr;


	//ui
	Sprite * mUIPadBack = nullptr;
	Sprite * mUIPadFront = nullptr;
	Image * mUIPadFrontImage = nullptr;
	
	//input
	float mPadMaxDistance;
	Vec2 mTouchBeganPos;
	TouchState mTouchState = TouchState::None;
	StopWatch * mTouchStopWatch = nullptr;
	float mTouchSlideTime;

	Size mPlayNodeSize;


	Enemy * mCurrentEnemy = nullptr;

public:
	static Scene * createScene();
	CREATE_FUNC(ScenePlay);

	//������ ����Ŭ �������̵�
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	virtual void update(float dt) override;

	//Input �������̽� �������̵�
	virtual bool onTouchBegan(Touch * touch, Event * unused_event) override;
	virtual void onTouchMoved(Touch * touch, Event * unused_event) override;
	virtual void onTouchEnded(Touch * touch, Event * unused_event) override;

};

#endif // !__SCENEPLAY_H__
