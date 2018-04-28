#include "stdafx.h"
#include "MyThread.h"
#include "SDL_Thread.h"


static int MyThreadFun(void *data) {
    ((MyThread*)data)->run();
	return 1;
}

MyThread::MyThread()
{
	
}


MyThread::~MyThread()
{
	if (thread)
	{
		delete thread;
	}
}

void MyThread::start()
{
	thread = new std::thread(MyThreadFun, this);
	thread->detach();
}

void MyThread::run()
{

}