#pragma once
class CDisplayManager
{
private:
	
	static CDisplayManager *pInstance;

	CDisplayManager();
	~CDisplayManager();
public:

	static CDisplayManager* GetInstance();

	void Display();
	//�̷��� ���� �� �� �ܺο��� ������ ȣ������� �Ѵ�.
	//���� �δ� ����
	//�ν��Ͻ� �����ÿ� 
	/*
	atexit(release_instance); : 
		return type�� parameter�� ��� void�� �Լ� �����͸� ���޹޴� �Լ��̸�,
		������ �� ������ �Լ��� ó���Ѵٰ� �մϴ�. ���� �ش� API�� �ִ� 32������ 
		�߰��� �� ������ LIFO ���·� �������� ���� �Լ��� ���� ���� ����ȴ�.
	*/
	//�Լ��� �ڿ����� �Լ��� ����Ͽ� ���� �� ���� ȣ�� ���� �ڿ�����

	void Destroy();
};

