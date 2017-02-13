#include "Boss.h"
#include "BossBody.h"
#include "BossHead.h"
#include "BossHand.h"
#include "ActorManager.h"
#include "Player.h"

bool Boss::init()
{
	if (!Enemy::init())
	{
		return true;
	}

	auto body = BossBody::create();
	this->AddParts(body);

	auto head = BossHead::create();
	head->setPosition(0, body->GetPartsSize().height* 0.55);
	this->AddParts(head);

	auto lefthand = BossHand::create();
	lefthand->InitHand(BossHand::HandDir::HandDir_Left);
	lefthand->setPosition(body->GetPartsSize().width * -0.6, body->GetPartsSize().height * -0.3);
	this->AddParts(lefthand);

	auto righthand = BossHand::create();
	righthand->InitHand(BossHand::HandDir::HandDir_Right);
	righthand->setPosition(body->GetPartsSize().width * 0.6, body->GetPartsSize().height * -0.3);
	this->AddParts(righthand);

	this->setScale(1.5 * CC_CONTENT_SCALE_FACTOR());
	this->scheduleUpdate();

	auto seq = Sequence::create(
		DelayTime::create(0.5),
		CallFunc::create([lefthand,this]()
	{
		//�÷��̾�� ������ ���� �θ� �����ֱ� ������
		//������ �θ� �������� ���� ���������� ��ȯ ��
		Vec2 pos = getParent()->convertToWorldSpace(ActorManager::GetInstance()->GetPlayer()->getPosition());
		//��ȯ�� �������� ������ ������������ ����ϴ� ���� ��������
		//�ùٸ��� �����ϱ� ���� ������ ���� ���������� ��ȯ �� �����Ѵ�.
		pos = convertToNodeSpace(pos);
		lefthand->OnAttack(pos);
	}),
		DelayTime::create(0.5),
		CallFunc::create([righthand, this]()
	{
		//�÷��̾�� ������ ���� �θ� �����ֱ� ������
		//������ �θ� �������� ���� ���������� ��ȯ ��
		Vec2 pos = getParent()->convertToWorldSpace(ActorManager::GetInstance()->GetPlayer()->getPosition());
		//��ȯ�� �������� ������ ������������ ����ϴ� ���� ��������
		//�ùٸ��� �����ϱ� ���� ������ ���� ���������� ��ȯ �� �����Ѵ�.
		pos = convertToNodeSpace(pos);
		righthand->OnAttack(pos);

	}),
		nullptr
	);

	this->runAction(seq);
	return true;
}

void Boss::update(float dt)
{

}
