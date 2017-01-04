#include "stdafx.h"
#include "EnemyFactorySample2.h"
//Enemys
#include "EnemyNormal.h"
//EnemyBullets
#include "EnemyBulletNormal.h"
#include "EnemyBulletPattern.h"

CEnemyFactorySample2::CEnemyFactorySample2()
{

	CEnemy *tpEnemy = NULL;
	int tiEnemy = 0;
	int tiBullet = 0;

	for (tiEnemy = 0; tiEnemy < 5; tiEnemy++)
	{
		tpEnemy = new CEnemyNormal();
		tpEnemy->SetUp((WIDTH * 0.2f) + (10 * tiEnemy), 3);
		tpEnemy->SetSpeedPower(3);
		tpEnemy->SetBulletInterval(100);
		//todo : issue
		//(�밢�� 2��, ������ 1��) * 5
		CEnemyBulletPattern *tpBulletPattern = NULL;
		for (tiBullet = 0; tiBullet < 5; tiBullet++)
		{
			tpBulletPattern = new CEnemyBulletPattern();
			tpBulletPattern
				->AddBullet(new CEnemyBulletNormal(-1, 1, 1))
				.AddBullet(new CEnemyBulletNormal(0, 1, 1))
				.AddBullet(new CEnemyBulletNormal(1, 1, 1));
			tpEnemy->AddBullet(tpBulletPattern);
		}
		mEnemys.push_back(tpEnemy);
	}

}


CEnemyFactorySample2::~CEnemyFactorySample2()
{
}
