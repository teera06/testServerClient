#pragma once
#include "Math.h"

class ConsoleScreen
{
public:
	// 생성자를 만든다는것은
	// 내가 만든 생성자 형식으로만 생성해라.
	ConsoleScreen(char _BaseChar); // 생성자
	
	void PrintScreen(); // 화면 보여주기
	

	void ClearScreen(); // 콘솔창 한번 지우고 다시 채우기 ex) '*'

	// 오버로딩 -> 이것도 하면 좋다. 실무에서 같은 환경일 수도 있다.
	void SetPixel(const int2& _Position, char _Char); // Player의 좌표값과 랜더링 값 받기

	void SetPixel(int _X, int _Y, char _Char); // 해당 좌표값에 Player 랜더링 값 넣어주기
	

protected:

private:
	char Arr[ScreenY][ScreenX] = { 0, }; // 맴버변수 초기화
	char BaseCh = ' '; // 맴버변수 초기화
	// [0][0][0][0][0][0]
	// [0][0][0][0][0][0]
	// [0][0][0][0][0][0]
	// [0][0][0][0][0][0]
	// [0][0][0][0][0][0]
};

