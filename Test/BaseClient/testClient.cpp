#include <WS2tcpip.h> //서버용 Window보다 무조건 위에 있어야 한다.
#include <WinSock2.h> //서버용
#include <iostream>
#include <assert.h>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <thread>
#include <functional>

#pragma comment (lib, "ws2_32") // <= 윈도우 서버 사용을 위한 라이브러리

void ClientRecvThread(SOCKET _Socket)
{
	
	std::string Text;
	Text.resize(100);

	int RecvSize = recv(_Socket, &Text[0], Text.size(), 0);

	std::string Name = Text;

	Text.clear();
	Text.resize(100);

	std::string SendPack;
	SendPack.clear();

	while (true)
	{
		int RecvSize = recv(_Socket, &Text[0], Text.size(), 0);
		SendPack = Name + " : " + Text;

		std::cout << SendPack << "\n";

		Text.clear();
		Text.resize(100);
	}


	//Text.clear();
	//Text.resize(100);
}


int main()
{
	std::cout << "클라 입니다.\n";

	WSAData WsaData;

	int Error = WSAStartup(MAKEWORD(2, 2), &WsaData);

	if (SOCKET_ERROR == Error)
	{
		assert(false);
	}
	//

	SOCKET ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == ClientSocket)
	{
		assert(false);
	}
	//
	int Port = 30000;


	SOCKADDR_IN ClientAdd = {};

	ClientAdd.sin_family = AF_INET;
	ClientAdd.sin_port = htons(Port);

	std::string IP = "14.42.55.46";

	if (SOCKET_ERROR == inet_pton(AF_INET, IP.c_str(), &ClientAdd.sin_addr))
	{
		assert(false);
	}
	//

	_getch();

	// 내부에서 Bind를 시켜줘서 ClientSocket <=Bind=> ClientAdd
	if (SOCKET_ERROR == connect(ClientSocket, (const sockaddr*)&ClientAdd, sizeof(SOCKADDR_IN)))
	{
		std::cout << "접속 실패\n";
		assert(false);
	}

	Sleep(10000);

	std::cout << "접속 성공\n";

	std::string Buffer;
	Buffer.resize(100);

	std::cout << "이름을 정해주세요 : ";
	std::cin >> Buffer;

	int SendSize = send(ClientSocket, &Buffer[0], Buffer.size(), 0);

	std::thread RecvThread = std::thread(std::bind(ClientRecvThread, ClientSocket));


	while (true)
	{
		

		std::cin >> Buffer;
		send(ClientSocket, &Buffer[0], Buffer.size(), 0);

		Buffer.clear();
		Buffer.resize(100);
	}

	WSACleanup();
}