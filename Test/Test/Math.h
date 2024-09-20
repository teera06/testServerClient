#pragma once
#include <iostream>
#include <conio.h>

// �̷������� Ŭ������ ����� ������ �и����� �ʽ��ϴ�.
// ��δ� ���� ����ؾ� �Ѵ�.
// ���� ��θ� ������� �ʴ´�.

// ���ͳ� �÷��̾ 
// ����� ������ �и������� �ʴ´�.
// ���ʿ� ���� ���� Ŭ������ ����� �߰����� �ʴ� Ŭ������ �����?�� �����.

class int2
{
	// ���� �̷� ������ Ŭ������
	// public���� �ɹ������� �δ� ���Դϴ�.
public:
	int X = 0;
	int Y = 0;

	// ����Ʈ ���Կ�����.
	void operator=(const int2& _Other)
	{
		X = _Other.X;
		Y = _Other.Y;
	}

	int2 operator+(const int2& _Other)
	{
		return { X + _Other.X, Y + _Other.Y };
	}

	void operator+=(const int2& _Other)
	{
		X += _Other.X;
		Y += _Other.Y;
	}
};

const int2 Left = { -1, 0 };
const int2 Right = { 1, 0 };
const int2 Up = { 0, -1 };
const int2 Down = { 0, 1 };

// ���������� ������ ���þ���
// �̸��� ���� �ִٸ� �װ��� ����� �� �ִ�.
const int ScreenX = 20;
const int ScreenY = 12;
const int ScreenXHalf = ScreenX / 2;
const int ScreenYHalf = ScreenY / 2;

