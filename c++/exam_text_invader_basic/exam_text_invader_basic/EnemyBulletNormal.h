#pragma once
#include "EnemyBullet.h"

//���� ����� �ӵ������� ��� �����̴� ����
class CEnemyBulletNormal :
	public CEnemyBullet
{
public:
	CEnemyBulletNormal();
	CEnemyBulletNormal(int, int, int);
	~CEnemyBulletNormal();

	virtual void Update() override;
};

