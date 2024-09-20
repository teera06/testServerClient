#include "ConsoleScreen.h"

// 생성자를 만든다는것은
	// 내가 만든 생성자 형식으로만 생성해라.
ConsoleScreen::ConsoleScreen(char _BaseChar) // 생성자
{
	// [*][*][*][*][*][0]
	// [*][*][*][*][*][0]
	// [*][*][*][*][*][0]
	// [*][*][*][*][*][0]
	// [*][*][*][*][*][0]

	BaseCh = _BaseChar;

}

void ConsoleScreen::PrintScreen() // 화면 보여주기
{
	for (int y = 0; y < ScreenY; y++)
	{
		char* Ptr = Arr[y];
		printf_s(Ptr);
		printf_s("\n");
	}
}

void ConsoleScreen::ClearScreen() // 콘솔창 한번 지우고 다시 채우기 ex) '*'
{
	system("cls");

	for (int y = 0; y < ScreenY; y++)
	{
		for (int x = 0; x < ScreenX - 1; x++)
		{
			Arr[y][x] = BaseCh;
		}
	}
}

// 오버로딩 -> 이것도 하면 좋다. 실무에서 같은 환경일 수도 있다.
void ConsoleScreen::SetPixel(const int2& _Position, char _Char) // Player의 좌표값과 랜더링 값 받기
{
	SetPixel(_Position.X, _Position.Y, _Char);
}

void ConsoleScreen::SetPixel(int _X, int _Y, char _Char) // 해당 좌표값에 Player 랜더링 값 넣어주기
{
	Arr[_Y][_X] = _Char;
}