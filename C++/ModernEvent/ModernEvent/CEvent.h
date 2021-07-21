#pragma once

#include <functional>
#include <queue>
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
using pFun = function<void(void)>;
class CEvent
{
	thread* m_pThread;
	condition_variable m_cv;
	mutex m_Mutex;
	bool m_bThreadClosed, m_bThreadAlive;
public:
	CEvent();
	virtual ~CEvent();
	void Register(int _event, pFun f)
	{
		m_Map[_event] = f;
	}
	void Trigger(int _event);
	void Start();
protected:
	void ThreadFun();
	map<int, pFun> m_Map;
	queue<int> m_Que;
};

