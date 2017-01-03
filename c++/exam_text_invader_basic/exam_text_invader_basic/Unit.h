#pragma once


class CUnit
{
protected:
	int mX = 0;
	int mY = 0;
	float mDirX = 0;
	float mDirY = 0;
	float mSpeedPower = 0;
	bool mIsAlive = true;
public:
	CUnit();
	virtual ~CUnit();

	virtual void SetUp(int tX, int tY);
	virtual void Update();
	virtual void Display(char *tpPixel) = 0;
	virtual void Clean(char *tpPixel);
	virtual void SetAlive(bool tAlive);
	virtual bool GetAlive();


	int GetX();
	void SetX(int);
	int GetY();
	void SetY(int);

	virtual void Destroy() = 0;
};

