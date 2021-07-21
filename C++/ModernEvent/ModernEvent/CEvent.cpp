#include "CEvent.h"

CEvent::CEvent()
{
	m_pThread = nullptr;
	m_bThreadClosed = false;
	m_bThreadAlive = false;
}

CEvent::~CEvent()
{
	m_bThreadClosed = true;
	m_cv.notify_all();
	while (m_bThreadAlive)
	{
		this_thread::yield();
	}
}

void CEvent::Trigger(int _event)
{
	unique_lock<mutex> lock(m_Mutex);
	m_Que.push(_event);
	m_cv.notify_all();
}

void CEvent::Start()
{
	if (!m_pThread)
	{
		m_pThread = new thread(&CEvent::ThreadFun, this);
	}
}

void CEvent::ThreadFun()
{
	m_bThreadAlive = true;
	while (true)
	{
		this_thread::yield();
		unique_lock<mutex> lock(m_Mutex);
		m_cv.wait(lock, [&] {return (m_Que.size()) || m_bThreadClosed; });
		if (m_bThreadClosed)
		{
			break;
		}
		int event = m_Que.front();
		m_Que.pop();
		auto f = m_Map.find(event);
		if (f != m_Map.end())
		{
			pFun pf = f->second;
			pf();
		}
	}
	m_bThreadAlive = false;
}
