#include <WS2tcpip.h> //서버용 Window보다 무조건 위에 있어야 한다.
#include <WinSock2.h> //서버용

#include <string>
#include <iostream>
#include <vector>
#include <assert.h>
#include <thread>
#include <functional>

#pragma comment(lib, "ws2_32")


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
		int RecvSize = recv(_Socket, &Text[0], Text.size(),0);
		SendPack = Name + " : " + Text;

		std::cout << SendPack << "\n";

		Text.clear();
		Text.resize(100);
	}

}



int main()
{
	std::cout << "서버 입니다." << "\n";

	WSAData WsaData; // 윈도우에게 서버 기능 사용 알리기 용

	// WSAStartup을 호출하고 해당 값을 정수로 반환하고 오류에 대해 검사.
	int Error = WSAStartup(MAKEWORD(2, 2), &WsaData);

	if (SOCKET_ERROR == Error)
	{
		assert(false);
	}
	//


	// 소켓 생성
	// SOCKET은 윈도우가 번호로서 기억
	// SOCK_STERAM TCP로 연다.
	SOCKET AcceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == AcceptSocket)
	{
		assert(false);
	}
	//

	// 소켓의 구성요소를 담을 구조체 생성 및 값 할당
	int Port = 30000;

	SOCKADDR_IN Add = {};
	Add.sin_family = AF_INET; // // ip4를 사용

	Add.sin_port = htons(Port);

	// 문자열을 프로토콜(IPV4,IPV6 등)에 해당하는 네트워크데이터(빅엔디언 방식의 이진데이터)로 변경
	// (inet_ntoa는 IPV4만 지원)
	// 00000000 00000000 00000000 00000001 // 빅에디안
	// 00000001 00000000 00000000 00000000 // 리틀에디안 인텔

	if (SOCKET_ERROR == inet_pton(AF_INET, ("0.0.0.0"), &Add.sin_addr))
	{
		assert(false);
	}
	//

	// 데이터를 보낼때 이 소켓으로 보내면 이제 주소랑
	// osi 7계층의 4계층까지가 데이터를 붙여서 보내게 만들어줍니다.
	// 주소값과 소켓을 연결하는 작업
	// 이제 AcceptSocket으로 뭔가를 하면 Add주소랑 연결되서 데이터가 입출력 됩니다.
	if (INVALID_SOCKET == bind(AcceptSocket, (const sockaddr*)&Add, sizeof(SOCKADDR_IN)))
	{
		assert(false);
	}
	//

	// 접속자 몇명 받을지
	int BackLog = 1;

	// 서버를 연다.
	// 클라이언트의 접속을 할수 있게 만드는 함수
	if (SOCKET_ERROR == listen(AcceptSocket, BackLog))
	{
		assert(false);
	}
	//



	std::cout << "접속 시작\n";

	std::string Buffer;
	Buffer.resize(100);

	
	int AddressLen = sizeof(SOCKADDR_IN);

	SOCKADDR_IN ClientAdd;

	memset(&ClientAdd, 0, sizeof(ClientAdd));

	//소켓에서 들어오는 연결을 수락하는 함수 호출입니다.
	SOCKET ClientSocket = accept(AcceptSocket, (sockaddr*)&ClientAdd, &AddressLen);

	Buffer.clear();
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
	// Windows 소켓 구현의 사용을 종료하는 함수 호출입니다.
	// 이 함수는 Windows 소켓 구현에 의해 할당된 모든 리소스를 해제하며 리소스가 제대로 해제되도록 프로그램이 종료되기 전에 호출되어야 합니다.
	WSACleanup();
}