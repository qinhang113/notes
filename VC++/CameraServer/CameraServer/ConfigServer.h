#pragma once
#include <iostream>
#include <WINSOCK2.H>
#include <stdio.h>
#include <vector>
#include <thread>
#include <mutex>
#include <map>
using namespace std;
#pragma  comment(lib,"ws2_32.lib")
class ConfigServer
{
	vector<SOCKET> m_ClientVector1, m_ClientVector2, m_ClientVector3, m_ClientVector4;
	map<string, bool> m_ClientInfo;
	SOCKET m_Listen;
	static mutex m_Mutex;
	int index{ 0 };
public:
	bool InitSocket(string ip, int port);
	void StartLoopForConnect();
	static void LoopForConnect(LPVOID lp);
	void StartLoopForRecvSend();
	static void RecvAndSend(LPVOID lp, vector<SOCKET>* v);
	void CloseSocket();
private:
	void Communication(SOCKET s);
	bool Verify(string name, string pw);
};

