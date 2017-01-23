#include "SceneBox2dCollision.h"

using namespace std;

Scene * SceneBox2DCollision::createScene()
{
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SceneBox2DCollision::create();

	// add layer as a child to scene
	scene->addChild(layer, 0);


	// return the scene
	return scene;
}

bool SceneBox2DCollision::init()
{
	if (!Layer::init())
	{
		return false;
	}


	


	mpLayerUI = Layer::create();
	this->addChild(mpLayerUI, 100);


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	mpSprBtn = Sprite::create("btn_push.png");
	mpSprBtn->setPosition(Vec2(700, 240));
	mpLayerUI->addChild(mpSprBtn, 100);


	mpLabelDebug = Label::createWithTTF("DEBUG: ", "fonts/BMJUA_ttf.ttf", 18);
	mpLabelDebug->setOpacity(128);
	mpLabelDebug->setAnchorPoint(Vec2(0, 0));
	mpLabelDebug->setPosition(Vec2(50, 50));

	mpLayerUI->addChild(mpLabelDebug, 100);


	return true;
}

void SceneBox2DCollision::update(float dt)
{
}

void SceneBox2DCollision::onEnter()
{
	Layer::onEnter();

	auto tListener = EventListenerTouchOneByOne::create();
	tListener->setSwallowTouches(true);
	tListener->onTouchBegan = CC_CALLBACK_2(SceneBox2DCollision::onTouchBegan, this);
	tListener->onTouchMoved = CC_CALLBACK_2(SceneBox2DCollision::onTouchMoved, this);
	tListener->onTouchEnded = CC_CALLBACK_2(SceneBox2DCollision::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(tListener, this);

	createPhysicsWorld();

	this->scheduleUpdate();

}

void SceneBox2DCollision::onExit()
{
	_eventDispatcher->removeEventListenersForTarget(this);

	destroyPhysicsWorld();

	this->unscheduleUpdate();

	Layer::onExit();
}

bool SceneBox2DCollision::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto tTouchPos = touch->getLocation();

	return true;
}

void SceneBox2DCollision::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto tTouchPos = touch->getLocation();
}

void SceneBox2DCollision::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto tTouchPos = touch->getLocation();

	if ((tTouchPos.x >= 700 - 40 && tTouchPos.x <= 700 + 40) &&
		(tTouchPos.y >= 240 - 40 && tTouchPos.y <= 240 + 40))
	{
		doFire();
		return;
	}

	log("Touch point : %f, %f", tTouchPos.x, tTouchPos.y);

	Sprite *tpSprite = Sprite::create("actor.png");

	tpSprite->setPosition(tTouchPos);
	this->addChild(tpSprite);

	b2BodyDef tBodyDef;
	tBodyDef.type = b2_dynamicBody;
	tBodyDef.position.Set(tTouchPos.x / PTM_RATIO, tTouchPos.y / PTM_RATIO);
	tBodyDef.userData = tpSprite;
	b2Body * tpBody = mpWorld->CreateBody(&tBodyDef);

	b2CircleShape tCircle;
	tCircle.m_radius = 1.0f;

	b2FixtureDef tFixtureDef;
	tFixtureDef.shape = &tCircle;
	tFixtureDef.density = 1.0f;
	tFixtureDef.friction = 0.5f;
	tFixtureDef.restitution = 0.0f;

	tpBody->CreateFixture(&tFixtureDef);


	/*
	//�簢���� ����( �簢���� �����￡ ���ϹǷ� b2PolygonShape�� ����

	b2PolygonShape tPolygonShape;

	tPolygonShape.SetAsBox(0.5f, 0.5f); //a 4x2 rectangle

	b2FixtureDef tFixtureDef;

	tFixtureDef.shape       = &tPolygonShape;
	tFixtureDef.density     = 1.0f;
	tFixtureDef.friction    = 0.5f;//0.2f;
	tFixtureDef.restitution = 0.0f;//0.7f;


	tpBody->CreateFixture(&tFixtureDef);
	*/

	//������ ��� �����Ǵ°�?
	//���� ��쿡 �������� 1�� ��� 3.14,
	//�簢���� ��쿡�� 0.5, 0.5 ( 1x1 ) �� ��� 1
	//Shape�� ũ�⿡ ����ϴ� ������ ���δ�.
	float32 tMass = tpBody->GetMass();
	log("tMass : %f", tMass);

	/*
	b2MassData tData;
	tData.mass = 1.0f;
	tpBody->SetMassData(&tData);

	tMass = tpBody->GetMass();
	log("==tMass: %f", tMass);
	*/

	//ī�޶� �� Layer�� ������ �����Ѵ�.
	Rect myBoundary = Rect(0, 0, mWinSize.width * 2, mWinSize.height * 2);
	this->runAction(Follow::create(this, myBoundary));

}

void SceneBox2DCollision::doFire()
{
	mpCurBody = mpWorld->GetBodyList();

	if (nullptr == (Sprite *)(mpCurBody->GetUserData()))
	{
		return;
	}

	//������ ���� 70��, ���� ũ��� 100�� ��츦 ���̰� �ִ�.
	double tTrigonoV = tan(CC_DEGREES_TO_RADIANS(70));
	double tFScalar = 100.0f;

	//���� �ﰢ������ �̿��Ͽ� �� ���� ���� ũ�⸦ ���Ͽ���.
	double tFX = tFScalar / sqrt((tTrigonoV*tTrigonoV + 1));
	double tFY = sqrt(tFScalar * tFScalar -
		(tFScalar / sqrt(1 + tTrigonoV * tTrigonoV))*
		(tFScalar / sqrt(1 + tTrigonoV*tTrigonoV))
	);

	//�־��� ���͸�ŭ�� ���� ���ϴ� �ڵ��̴�.
	mpCurBody->ApplyLinearImpulse(b2Vec2(tFX, tFY), b2Vec2(0.0f, 0.0f), true);

	//����ī�޶� �ش簴ü�� ����ٴϰ� �ϴ� �׼��̴�.
	Rect myBoundary = Rect(0, 0, mWinSize.width * 2, mWinSize.height * 2);
	this->runAction(Follow::create((Sprite *)(mpCurBody->GetUserData()), myBoundary));

}

void SceneBox2DCollision::createPhysicsWorld()
{
	mWinSize = Director::getInstance()->getWinSize();


	//�߷°��� �����ϰ�, �߷°��� �������� �������踦 �����.
	b2Vec2 tGravity = b2Vec2(0.0f, -30.0f);

	mpWorld = new b2World(tGravity);
	mpWorld->SetAllowSleeping(true);
	mpWorld->SetContinuousPhysics(true);

	//���������� ��踦 ���� Physical Body���� staticBody�� �����.
	b2BodyDef tGroundBodyDef;
	tGroundBodyDef.position.Set(0, 0);
	tGroundBodyDef.type = b2_staticBody;

	b2Body * tpGroundBody = mpWorld->CreateBody(&tGroundBodyDef);

	b2EdgeShape tGroundEdge;
	b2FixtureDef tBoxShapeDef;
	tBoxShapeDef.shape = &tGroundEdge;

	//left
	tGroundEdge.Set(b2Vec2(0, 0), b2Vec2(0, mWinSize.height * 2 / PTM_RATIO));
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//top
	tGroundEdge.Set(b2Vec2(0, mWinSize.height * 2 / PTM_RATIO),
		b2Vec2(mWinSize.width * 2 / PTM_RATIO, mWinSize.height * 2 / PTM_RATIO));
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//right
	tGroundEdge.Set(b2Vec2(mWinSize.width * 2 / PTM_RATIO, mWinSize.height * 2 / PTM_RATIO),
		b2Vec2(mWinSize.width * 2 / PTM_RATIO, 0));
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//bottom
	tGroundEdge.Set(b2Vec2(0, 0),
		b2Vec2(mWinSize.width * 2 / PTM_RATIO, 0));
	tpGroundBody->CreateFixture(&tBoxShapeDef);

	//���������� �������� �����ϱ� ���� ������ �����.
	//this->schedule(schedule_selector(SceneBox2DCollision::updatePhysicsWorld));
	this->schedule(CC_SCHEDULE_SELECTOR(SceneBox2DCollision::updatePhysicsWorld));


	//�������迡�� �Ͼ�� �浹���� �����ϱ� ���� �����ʸ� �����.
	mpContactListener = new ContactListener();
	mpWorld->SetContactListener((b2ContactListener *)mpContactListener);

	//debug
	// ����� ����� ����
	// ���� : ���� ���� ��� �ϴ� ��
	// ȸ�� : ���� ���� ����� ���� ��
	mDebugDraw = new GLESDebugDraw(PTM_RATIO);
	mpWorld->SetDebugDraw(mDebugDraw);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	mDebugDraw->SetFlags(flags);

}

void SceneBox2DCollision::destroyPhysicsWorld()
{
	//���� ��ü���� �����Ѵ�.
	//���� ��ü�� ����� ��������Ʈ(���)�� �����ؾ� �Ѵ�.


	for (b2Body *tpBody = mpWorld->GetBodyList(); tpBody; tpBody = tpBody->GetNext())
	{
		if (nullptr != tpBody->GetUserData())
		{
			Sprite * tpSprite = (Sprite *)tpBody->GetUserData();
			this->removeChild(tpSprite);

			mpWorld->DestroyBody(tpBody);
		}
	}

	//�������踦 �ı��Ѵ�.
	if (nullptr != mpWorld)
	{
		delete mpWorld;
		mpWorld = nullptr;
	}


}

void SceneBox2DCollision::updatePhysicsWorld(float dt)
{
	if (nullptr == mpWorld)
	{
		return;
	}
	//http://cafe.naver.com/cocos2dxusers/25620
	// velocityIterations : �ٵ���� ���������� �̵���Ű�� ���ؼ� �ʿ��� �浹���� �ݺ������� ���
	// positionIterations : ����Ʈ �и���, ��ħ������ ���̱� ���ؼ� �ٵ��� ��ġ�� �ݺ������� ����
	// ���� Ŭ���� ��Ȯ�� ������ ���������� ������ ��������.

	//�Ŵ��� ��õ��
	int tVelocityIterations = 8;
	int tPositionIterations = 3;

	//Step�޼ҵ��� ������ �����ΰ�? ������� ���踦 �����Ѵ�.
	mpWorld->Step(dt, tVelocityIterations, tPositionIterations);

	//�Ʒ� ������ ������ �ϴ� ���ΰ�?
	//��������� ����Ͽ� Sprite�� ��ġ�� ȸ������ �����ϴ� ���̴�.
	for (b2Body *tpBody = mpWorld->GetBodyList(); tpBody; tpBody = tpBody->GetNext())
	{
		if (nullptr != tpBody->GetUserData())
		{
			Sprite * tpSprite = (Sprite *)tpBody->GetUserData();

			if (nullptr != tpSprite)
			{
				//������� ������ ��ǥ���� �ȼ����� ��ǥ��� ���� ��ȯ���ش�.
				tpSprite->setPosition(Vec2(tpBody->GetPosition().x * PTM_RATIO,
					tpBody->GetPosition().y *PTM_RATIO));

				//���� ���ȿ��� �� ������ ��ȯ�Ѵ�.
				//-1�� ���ϴ� ������ �����ΰ�?
				tpSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(tpBody->GetAngle()));

			}
		}
	}
	
	//destroy physical body
	std::vector<b2Body *> tDestroyVec;
	std::vector<SContacts>::iterator tIterator;


	//�浹 ���� ����Ʈ�� ��� Physical Body���� ������ ��������Ͽ� �ִ´�.
	for (tIterator = mpContactListener->mSContacts.begin();
		tIterator != mpContactListener->mSContacts.end(); ++tIterator)
	{
		SContacts tSContacts = *tIterator;

		b2Body *tpBodyA = tSContacts.fixtureA->GetBody();
		b2Body *tpBodyB = tSContacts.fixtureB->GetBody();

		if (tpBodyA->GetUserData() != nullptr && tpBodyB->GetUserData() != nullptr)
		{
			Sprite * tpSpriteA = (Sprite *)tpBodyA->GetUserData();
			Sprite * tpSpriteB = (Sprite *)tpBodyB->GetUserData();

			if (nullptr != tpSpriteA && nullptr != tpSpriteB)
			{
				if (std::find(tDestroyVec.begin(), tDestroyVec.end(), tpBodyB) == tDestroyVec.end())
				{
					tDestroyVec.push_back(tpBodyB);
				}

				if (std::find(tDestroyVec.begin(), tDestroyVec.end(), tpBodyA) == tDestroyVec.end())
				{
					tDestroyVec.push_back(tpBodyA);
				}
			}
		}
	}

	//������� ��Ͽ� �ִ� Physical Body ���� �����Ѵ�.
	std::vector<b2Body *>::iterator tIterator_0;
	for (tIterator_0 = tDestroyVec.begin(); tIterator_0 != tDestroyVec.end(); ++tIterator_0)
	{
		b2Body * tpBody = *tIterator_0;
		if (tpBody->GetUserData() != nullptr)
		{
			Sprite * tpSprite = (Sprite *)tpBody->GetUserData();
			this->removeChild(tpSprite, true);

			tpSprite = NULL;
		}

		mpWorld->DestroyBody(tpBody);
	}

}

void SceneBox2DCollision::draw(Renderer * renderer, const Mat4 & transform, uint32_t flags)
{
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION);
	kmGLPushMatrix();
	mpWorld->DrawDebugData();
	kmGLPopMatrix();
}

void SceneBox2DCollision::onDraw(const Mat4 & transform, uint32_t flags)
{
}

