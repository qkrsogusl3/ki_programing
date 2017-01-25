#ifndef __SCENEBOX2D_H__
#define __SCENEBOX2D_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "b2Custom\GLES-Render.h"

using namespace cocos2d;

#define PTM_RATIO 32

class SceneBox2D : public Layer
{
protected:
	Layer * mpLayer_0 = nullptr;
	Layer * mpLayer_1 = nullptr;

	Vector<Sprite *> mSpriteVec;

	Label * mplblDebug = nullptr;

	EventListenerTouchOneByOne * mpListener = nullptr;

	Size mWinSize;
	b2World * mpb2World = nullptr;

public:
	static Scene * createScene();

	virtual bool init();
	virtual void update(float dt);

	void updateTick(float dt);

	int doRandom();

	void menuCloseCallback(Ref * pSender);

	void onClickBtnGoMove(Ref * pSender);

	//��ġ�� ����(�հ����� ���), ��ġ�� ���·� �����̴� ��, ��ġ�� ��(�հ����� ����)
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);


	// implement the "static create()" method manually
	CREATE_FUNC(SceneBox2D);

	GLESDebugDraw * m_debugDraw;
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCmd;
};

#endif // !__SCENEBOX2D_H__
