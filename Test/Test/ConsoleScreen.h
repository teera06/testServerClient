#pragma once
#include "Math.h"

class ConsoleScreen
{
public:
	// �����ڸ� ����ٴ°���
	// ���� ���� ������ �������θ� �����ض�.
	ConsoleScreen(char _BaseChar); // ������
	
	void PrintScreen(); // ȭ�� �����ֱ�
	

	void ClearScreen(); // �ܼ�â �ѹ� ����� �ٽ� ä��� ex) '*'

	// �����ε� -> �̰͵� �ϸ� ����. �ǹ����� ���� ȯ���� ���� �ִ�.
	void SetPixel(const int2& _Position, char _Char); // Player�� ��ǥ���� ������ �� �ޱ�

	void SetPixel(int _X, int _Y, char _Char); // �ش� ��ǥ���� Player ������ �� �־��ֱ�
	

protected:

private:
	char Arr[ScreenY][ScreenX] = { 0, }; // �ɹ����� �ʱ�ȭ
	char BaseCh = ' '; // �ɹ����� �ʱ�ȭ
	// [0][0][0][0][0][0]
	// [0][0][0][0][0][0]
	// [0][0][0][0][0][0]
	// [0][0][0][0][0][0]
	// [0][0][0][0][0][0]
};

