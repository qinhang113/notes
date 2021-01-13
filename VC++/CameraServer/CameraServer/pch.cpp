// pch.cpp: 与预编译标头对应的源文件；编译成功所必需的

#include "pch.h"

// 一般情况下，忽略此文件，但如果你使用的是预编译标头，请保留它。

bool IsSocketClosed(SOCKET clientSocket)
{
	bool ret = false;
	HANDLE closeEvent = WSACreateEvent();
	WSAEventSelect(clientSocket, closeEvent, FD_CLOSE);

	DWORD dwRet = WaitForSingleObject(closeEvent, 0);

	if (dwRet == WSA_WAIT_EVENT_0)
		ret = true;
	else if (dwRet == WSA_WAIT_TIMEOUT)
		ret = false;

	WSACloseEvent(closeEvent);
	return ret;
}

bool GetAddressBySocket(SOCKET m_socket, SOCKADDR_IN& m_address)
{
	memset(&m_address, 0, sizeof(m_address));
	int nAddrLen = sizeof(m_address);

	if (::getpeername(m_socket, (SOCKADDR*)&m_address, &nAddrLen) != 0)
	{
		//printf("Get IP address by socket failed!\n");
		return false;
	}
	return true;
}