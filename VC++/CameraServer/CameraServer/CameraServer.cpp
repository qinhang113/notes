// CameraServer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include "opencv.hpp"
#include "ConfigServer.h"
//#define MAXSENDSIZE 3147274	//1366*768*3 + 10

cv::Mat FrameData;
SOCKET Slisten;
vector<SOCKET> ClientVector1, ClientVector2, ClientVector3, ClientVector4;
mutex mtx;
int index = 0;

void ConnectThreadFun()
{
	while (Slisten)
	{
		SOCKET sClient;
		sockaddr_in remoteAddr;
		int nAddrlen = sizeof(remoteAddr);
		do
		{
			sClient = accept(Slisten, (SOCKADDR*)&remoteAddr, &nAddrlen);
		} while (sClient == INVALID_SOCKET);
		printf("接受到一个连接：%s \r\n", inet_ntoa(remoteAddr.sin_addr));
		mtx.lock();
		switch (index)
		{
		case 1:
			ClientVector2.push_back(sClient);
			break;
		case 2:
			ClientVector3.push_back(sClient);
			break;
		case 3:
			ClientVector4.push_back(sClient);
			break;
		default:
			ClientVector1.push_back(sClient);
			index = 1;
			break;
		}
		mtx.unlock();
		index++;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void SendDataThreadFun(vector<SOCKET> *v)
{
	while (Slisten)
	{
		if (FrameData.empty()|| !(*v).size())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue;
		}
		int heigth = FrameData.rows;
		int width = FrameData.cols;
		//char sendData[MAXSENDSIZE] = "";
		char *sendData = new char[heigth * width * 3 + 4];
		mtx.lock();
		for (auto it = (*v).begin(); it != (*v).end();)
		{
			if (IsSocketClosed(*it))
			{
				sockaddr_in remoteAddr;
				GetAddressBySocket(*it, remoteAddr);
				printf("客户端已断(%s:%d)开连接!\n", inet_ntoa(remoteAddr.sin_addr), ntohs(remoteAddr.sin_port));
				it = (*v).erase(it);
				continue;
			}
			char headData[4] = "";
			headData[0] = heigth / 256;
			headData[1] = heigth % 256;
			headData[2] = width / 256;
			headData[3] = width % 256;

			memcpy(sendData, headData, 4);
			memcpy(sendData + 4, FrameData.data, heigth * width * 3);
			send(*it, sendData, heigth * width * 3 + 4, 0);		
			it++;
		}
		delete[] sendData;
		mtx.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}


int main()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}
	//创建套接字
	Slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}
	//绑定IP和端口
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);//端口8888
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (::bind(Slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}

	//开始监听
	if (listen(Slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}

	printf("等待连接...\n");

	thread listen = thread(ConnectThreadFun);
	listen.detach();
		
	cv::VideoCapture cap;
	while (true)
	{
		if (cap.open(0))
			break;
		else
			printf("Camera未连接!等待Camera连接 !\n");
		this_thread::sleep_for(chrono::milliseconds(1000));
	}

	thread send1 = thread(SendDataThreadFun, &ClientVector1);
	send1.detach();
	thread send2 = thread(SendDataThreadFun, &ClientVector2);
	send2.detach();
	thread send3 = thread(SendDataThreadFun, &ClientVector3);
	send3.detach();
	thread send4 = thread(SendDataThreadFun, &ClientVector4);
	send4.detach();

	while (1)
	{
		cap >> FrameData;//等价于cap.read(frame);
		if (FrameData.empty())
			break;
		//不使用imshow来显示图像,waitkey好像不生效
		if (cv::waitKey(20) == 0x1B)
			break;
	}
	printf("发送被终止!\n");
	cap.release();

	closesocket(Slisten);
	WSACleanup();
	system("pause");
	return 0;
}

