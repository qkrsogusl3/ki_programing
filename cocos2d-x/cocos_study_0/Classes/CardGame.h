#ifndef __CARDGAME_SCENE_H__
#define __CARDGAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class CCardGame : public Layer
{

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(CCardGame);
};

#endif // !__HELLOWORLD_SCENE_H__