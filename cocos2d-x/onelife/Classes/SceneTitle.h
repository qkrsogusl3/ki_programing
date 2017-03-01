#ifndef __SCENETITLE_H__
#define __SCENETITLE_H__

#include "cocos2d.h"
#include <functional>
#include <vector>

using namespace cocos2d;
using namespace std;

class StopWatch;

typedef function<bool(float)> UpdateFunc;

class SceneTitle : public LayerColor
{
public:
	static Scene * createScene();
	CREATE_FUNC(SceneTitle);

	virtual bool init() override;
	virtual void update(float dt) override;
	virtual void onEnter() override;
	virtual void onExit() override;

	virtual bool onTouchBegan(Touch * touch, Event * unused_event) override;
	virtual void onTouchMoved(Touch * touch, Event * unused_event) override;
	virtual void onTouchEnded(Touch * touch, Event * unused_event) override;

	virtual void onKeyPressed(EventKeyboard::KeyCode key, Event * event) override;
private:
	Size mVisibleSize;
	Vec2 mCenterPosition;
	Sprite * mMask = nullptr;
	Vec2 mMaskInitPosition;

	Node * mRenderNode = nullptr;

	StopWatch * mStopWatch = nullptr;

	//sequence update
	int mUpdateFunctionIndex = 0;
	vector<UpdateFunc> mUpdateFunctions;
	StopWatch * mUpdateFunctionWatch = nullptr;

	Label * mTitleNameLabel = nullptr;
	Sprite * mExclamationMark = nullptr;
	int mTitleScriptIndex = 0;
	int mScriptCharIndex = 0;
	vector<string> * mTitleScript = nullptr;
	Label * mTitleScriptLabel = nullptr;
	bool mIsPlayScript = false;

	//touch State
	bool mIsTouchBegan = false;
	

};

#endif // !__SCENETITLE_H__
