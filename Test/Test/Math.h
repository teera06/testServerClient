#pragma once
#include <iostream>
#include <conio.h>

// 이런느낌의 클래스만 선언과 구현을 분리하지 않습니다.
// 모두는 나를 사용해야 한다.
// 나는 모두를 사용하지 않는다.

// 몬스터나 플레이어나 
// 선언과 구현을 분리하지도 않는다.
// 위쪽에 내가 만든 클래스를 절대로 추가하지 않는 클래스가 들어있?는 헤더다.

class int2
{
	// 보통 이런 수학적 클래스는
	// public으로 맴버변수를 두는 편입니다.
public:
	int X = 0;
	int Y = 0;

	// 디폴트 대입연산자.
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

// 전역변수는 영역과 관련없이
// 이름이 위에 있다면 그것을 사용할 수 있다.
const int ScreenX = 20;
const int ScreenY = 12;
const int ScreenXHalf = ScreenX / 2;
const int ScreenYHalf = ScreenY / 2;

