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

	mpSpriteShooter = Sprite::create("f1.png");
	mpSpriteShooter->setAnchorPoint(Vec2(0, 0));
	mpSpriteShooter->setPosition(Vec2(100, 0));
	this->addChild(mpSpriteShooter, 1);
	return true;
}

void SceneBox2DCollision::update(float dt)
{
	static float time = 0;
	time += dt;
	if (time >= 1)
	{
		time = 0;
		if (mpCurBody == nullptr)
		{
			log("mpCurBody is Null");
		}
		else
		{
			log("mpCurbody : %f,%f", mpCurBody->GetPosition().x, mpCurBody->GetPosition().y);
			if (((Sprite *)mpCurBody->GetUserData()) == nullptr)
			{
				log("Sprite is null");
			}
		}
	}
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
	createBlocks();

	this->scheduleUpdate();

	this->runAction(ScaleTo::create(1, 0.99));
}

void SceneBox2DCollision::onExit()
{
	_eventDispatcher->removeEventListenersForTarget(this);

	destroyPhysicsWorld();

	this->unscheduleUpdate();

	Layer::onExit();
}

void SceneBox2DCollision::createBlocks()
{
	this->addNewBlock(Vec2(mWinSize.width, 300), Size(30, 100));
	this->addNewBlock(Vec2(mWinSize.width * 1.2, 300), Size(30, 100));
	this->addNewBlock(Vec2(mWinSize.width * 1.4, 300), Size(30, 100));
}

void SceneBox2DCollision::addNewBlock(Vec2 pos, Size size)
{

	b2BodyDef tBodyBlockDef;
	tBodyBlockDef.type = b2_dynamicBody;
	tBodyBlockDef.position.Set(pos.x / PTM_RATIO, pos.y / PTM_RATIO);
	Sprite * tSpriteBlock = Sprite::create("grossini.png");
	tSpriteBlock->setPosition(pos);
	this->addChild(tSpriteBlock);
	tBodyBlockDef.userData = tSpriteBlock;

	b2Body * tBodyBlock = mpWorld->CreateBody(&tBodyBlockDef);

	b2FixtureDef tFixtureBlockDef;
	b2PolygonShape tShape;
	tShape.SetAsBox(size.width / PTM_RATIO, size.height / PTM_RATIO);
	tFixtureBlockDef.shape = &tShape;
	tFixtureBlockDef.density = 1.0f;
	tFixtureBlockDef.friction = 0.5f;

	tBodyBlock->CreateFixture(&tFixtureBlockDef);

	mBlocks.push_back(tBodyBlock);
}


bool SceneBox2DCollision::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto tTouchPos = touch->getLocation();
	Rect myBoundary = Rect(0, 0, mWinSize.width * 2, mWinSize.height * 2);
	this->runAction(Follow::create(this, myBoundary));

	
	return true;
}

void SceneBox2DCollision::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto tTouchPos = touch->getLocation();

	float tdx = tTouchPos.x - mpSpriteShooter->getPosition().x;
	float tdy = tTouchPos.y - mpSpriteShooter->getPosition().y;

	float tDegree = CC_RADIANS_TO_DEGREES(atan2(-tdy, tdx));
	tDegree = clampf(tDegree, -90, 0);
	log("%f", tDegree);
	mpSpriteShooter->setRotation(tDegree);

	mTouchDistance = sqrt(pow(tdx, 2) + pow(tdy, 2));
	log("%f", mTouchDistance);
}

void SceneBox2DCollision::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	auto tTouchPos = touch->getLocation();

	/*if (mpSprBtn->getBoundingBox().containsPoint(tTouchPos))
	{
		return;
	}*/

	log("Touch point : %f, %f", tTouchPos.x, tTouchPos.y);

	Sprite *tpSprite = Sprite::create("actor.png");

	tpSprite->setPosition(tTouchPos);
	this->addChild(tpSprite);

	//Body ������ ����
	b2BodyDef tBodyDef;
	//b2_dynamicBody : ����Body, �����̴� ĳ����,�̻��� ��
	//b2_staticBody : ����Body, �������� �ʴ� ��, ��ֹ� �� 
	//b2_kinematicBody : staticBody�� ���� ���� Body������ �ӵ��� ������ �����Ͽ� �̵��� �� �ִ�.
	tBodyDef.type = b2_dynamicBody;
	tBodyDef.position.Set(mpSpriteShooter->getPosition().x / PTM_RATIO, mpSpriteShooter->getPosition().y / PTM_RATIO);
	tBodyDef.userData = tpSprite;
	//���忡 Body���� �� ������� Body�� Fixture�� �����ϱ� ���� Body�� ������ ����
	b2Body * tpBody = mpWorld->CreateBody(&tBodyDef);

	//Fixture�� Shape ����
	b2CircleShape tCircle;

	tCircle.m_radius = 1.0f;

	//Fixture������ �ʿ��� ������ ����
	//Fixture : ��ü�� ������ Body�� �ο��� �� ����
	b2FixtureDef tFixtureDef;
	tFixtureDef.shape = &tCircle;
	tFixtureDef.density = 1.0f;//�е�
	tFixtureDef.friction = 0.5f;//������
	tFixtureDef.restitution = 0.0f;//�ݹ߷�
	//Body�� Fixture����, CreateBody�� ���������� Body�� ������� Fixture�� 
	//���Ϲ޾� ���� ����
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

	mBullets.push_back(tpBody);
	doFire();

	//ī�޶� �� Layer�� ������ �����Ѵ�.
	//Body���� �� Push��ư�� ���̵��� ȭ�� �̵�
	/*Rect myBoundary = Rect(0, 0, mWinSize.width * 2, mWinSize.height * 2);
	this->runAction(Follow::create(tpSprite, myBoundary));
*/
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
	
	//�� 4���� ������ Fixture�� Shape������
	b2EdgeShape tGroundEdge;

	//GroundBody�� Fixture�� ������ ������
	b2FixtureDef tBoxShapeDef;
	//Fixture�����Ϳ� Shape�����͸� ������Ŵ���μ� 
	//Shape������ ���� �� Fixture�������� �߰� ���پ��� Fixture�� ������ �� �ֵ��� �Ѵ�.
	tBoxShapeDef.shape = &tGroundEdge;

	//left
	//Fixture�����Ϳ� ���� ���ѵ� Shape�����͸� �����Ͽ� ���ʺ��� ǥ���ϰ� 
	//Fixture�����͸� �Ѱ� GroundBody�� ���ʺ�Fixture�� ����
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

	mpBodyWall = tpGroundBody;

	//���� : http://thrillfighter.tistory.com/187
	//�� ó�� ������ ����� ���� ������ �߷¿� ���� Body ȭ��۱��� ������
	//�Ǵµ� �� ��� Sprite�� ������ �Ǿ� ��������� Body�� ������� �ʾ� ȭ�鿡
	//ǥ�õ����� ������ ������ ������ �޴´�. ��������� ������ �ʴ� ��ü�� �޸𸮿� ���̰� ��
	//�ذ� �� ���� ����� step loop���� ��ü�� ȭ������� ���� �� ���忡�� body�� Destroy�ǵ���
	//ó���ϸ� �ȴ�.
	

	//���������� �������� �����ϱ� ���� ������ �����.
	//this->schedule(schedule_selector(SceneBox2DCollision::updatePhysicsWorld)); //�� Api
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

	//���� �ݺ� ��
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

	//����� �����ʿ� ����� �ִ� 
	//�浹 ���� ����Ʈ�� ��� Physical Body���� ������ ���������(tDestroyVec)�� �ִ´�.

	for (tIterator = mpContactListener->mSContacts.begin();
		tIterator != mpContactListener->mSContacts.end(); ++tIterator)
	{
		SContacts tSContacts = *tIterator;

		b2Body *tpBodyA = tSContacts.fixtureA->GetBody();
		b2Body *tpBodyB = tSContacts.fixtureB->GetBody();

		if (tpBodyA->GetUserData() != nullptr && tpBodyB->GetUserData() != nullptr)
		{
			auto tBulletAIterater = std::find(mBullets.begin(), mBullets.end(), tpBodyA);
			auto tBulletBIterater = std::find(mBullets.begin(), mBullets.end(), tpBodyB);

			if (tBulletAIterater != mBullets.end() && tBulletBIterater != mBullets.end())
			{

				tDestroyVec.push_back(tpBodyA);
				tDestroyVec.push_back(tpBodyB);
			}

			

			/*if (std::find(mBlocks.begin(), mBlocks.end(), tpBodyB) != mBlocks.end())
			{
				tDestroyVec.push_back(tpBodyA);
			}

			if (std::find(mBlocks.begin(), mBlocks.end(), tpBodyA) != mBlocks.end())
			{
				tDestroyVec.push_back(tpBodyB);
			}*/
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

void SceneBox2DCollision::doFire()
{
	//��� ������ ���� Body���� LinkedList�� �޾ƿ�
	//���� �������� ������ Body�� ����
	//LinkedList�� Body���� ����Ǿ� �ֱ� ������
	//�ϳ��� Body�� ���ؼ� �ٸ� Body�鿡 ���������� ���ٰ����ϴ�.
	mpCurBody = mpWorld->GetBodyList();

	//������ ���� 70��, ���� ũ��� 100�� ��츦 ���̰� �ִ�.
	double tTrigonoV = tan(CC_DEGREES_TO_RADIANS(mpSpriteShooter->getRotation()));
	double tFScalar = mTouchDistance * 0.3f;

	//���� �ﰢ������ �̿��Ͽ� �� ���� ���� ũ�⸦ ���Ͽ���.
	double tFX = tFScalar / sqrt((tTrigonoV*tTrigonoV + 1));
	double tFY = sqrt(
		tFScalar * tFScalar -
		(tFScalar / sqrt(1 + tTrigonoV * tTrigonoV))*
		(tFScalar / sqrt(1 + tTrigonoV * tTrigonoV))
	);

	//�־��� ���͸�ŭ�� ���� ���ϴ� �ڵ��̴�.
	mpCurBody->ApplyLinearImpulse(b2Vec2(tFX, tFY), b2Vec2(0.0f, 0.0f), true);

	//����ī�޶� �ش簴ü�� ����ٴϰ� �ϴ� �׼��̴�.
	//ī�޶��� Follow����
	Rect myBoundary = Rect(0, 0, mWinSize.width * 2, mWinSize.height);

	if (nullptr == (Sprite *)(mpCurBody->GetUserData()))
	{
		return;
	}
	this->runAction(Follow::create((Sprite *)(mpCurBody->GetUserData()), myBoundary));
}

void SceneBox2DCollision::destroyPhysicsWorld()
{
	//���� ��ü���� �����Ѵ�.
	//���� ��ü�� ����� ��������Ʈ(���)�� �����ؾ� �Ѵ�.


	//for (b2Body *tpBody = mpWorld->GetBodyList(); tpBody; tpBody = tpBody->GetNext())
	//{
	//	if (nullptr != tpBody->GetUserData())
	//	{
	//		Sprite * tpSprite = (Sprite *)tpBody->GetUserData();
	//		this->removeChild(tpSprite);

	//	}
	//	mpWorld->DestroyBody(tpBody);
	//
	//}

	//�������踦 �ı��Ѵ�.
	if (nullptr != mpWorld)
	{
		delete mpWorld;
		mpWorld = nullptr;
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

