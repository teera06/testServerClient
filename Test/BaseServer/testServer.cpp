#include <WS2tcpip.h> //������ Window���� ������ ���� �־�� �Ѵ�.
#include <WinSock2.h> //������

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
	std::cout << "���� �Դϴ�." << "\n";

	WSAData WsaData; // �����쿡�� ���� ��� ��� �˸��� ��

	// WSAStartup�� ȣ���ϰ� �ش� ���� ������ ��ȯ�ϰ� ������ ���� �˻�.
	int Error = WSAStartup(MAKEWORD(2, 2), &WsaData);

	if (SOCKET_ERROR == Error)
	{
		assert(false);
	}
	//


	// ���� ����
	// SOCKET�� �����찡 ��ȣ�μ� ���
	// SOCK_STERAM TCP�� ����.
	SOCKET AcceptSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (INVALID_SOCKET == AcceptSocket)
	{
		assert(false);
	}
	//

	// ������ ������Ҹ� ���� ����ü ���� �� �� �Ҵ�
	int Port = 30000;

	SOCKADDR_IN Add = {};
	Add.sin_family = AF_INET; // // ip4�� ���

	Add.sin_port = htons(Port);

	// ���ڿ��� ��������(IPV4,IPV6 ��)�� �ش��ϴ� ��Ʈ��ũ������(�򿣵�� ����� ����������)�� ����
	// (inet_ntoa�� IPV4�� ����)
	// 00000000 00000000 00000000 00000001 // �򿡵��
	// 00000001 00000000 00000000 00000000 // ��Ʋ����� ����

	if (SOCKET_ERROR == inet_pton(AF_INET, ("0.0.0.0"), &Add.sin_addr))
	{
		assert(false);
	}
	//

	// �����͸� ������ �� �������� ������ ���� �ּҶ�
	// osi 7������ 4���������� �����͸� �ٿ��� ������ ������ݴϴ�.
	// �ּҰ��� ������ �����ϴ� �۾�
	// ���� AcceptSocket���� ������ �ϸ� Add�ּҶ� ����Ǽ� �����Ͱ� ����� �˴ϴ�.
	if (INVALID_SOCKET == bind(AcceptSocket, (const sockaddr*)&Add, sizeof(SOCKADDR_IN)))
	{
		assert(false);
	}
	//

	// ������ ��� ������
	int BackLog = 1;

	// ������ ����.
	// Ŭ���̾�Ʈ�� ������ �Ҽ� �ְ� ����� �Լ�
	if (SOCKET_ERROR == listen(AcceptSocket, BackLog))
	{
		assert(false);
	}
	//



	std::cout << "���� ����\n";

	std::string Buffer;
	Buffer.resize(100);

	
	int AddressLen = sizeof(SOCKADDR_IN);

	SOCKADDR_IN ClientAdd;

	memset(&ClientAdd, 0, sizeof(ClientAdd));

	//���Ͽ��� ������ ������ �����ϴ� �Լ� ȣ���Դϴ�.
	SOCKET ClientSocket = accept(AcceptSocket, (sockaddr*)&ClientAdd, &AddressLen);

	Buffer.clear();
	Buffer.resize(100);

	std::cout << "�̸��� �����ּ��� : ";
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
	// Windows ���� ������ ����� �����ϴ� �Լ� ȣ���Դϴ�.
	// �� �Լ��� Windows ���� ������ ���� �Ҵ�� ��� ���ҽ��� �����ϸ� ���ҽ��� ����� �����ǵ��� ���α׷��� ����Ǳ� ���� ȣ��Ǿ�� �մϴ�.
	WSACleanup();
}