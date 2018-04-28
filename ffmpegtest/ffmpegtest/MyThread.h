#pragma once


class MyThread
{
public:
	MyThread();
	virtual ~MyThread();

public:
	void start();
	virtual void run();

private:
	std::thread* thread;
};

