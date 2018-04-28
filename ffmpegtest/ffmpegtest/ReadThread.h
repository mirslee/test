#pragma once

#include "MyThread.h"


class ReadThread : public MyThread
{
public:
	ReadThread();
	~ReadThread();

	void run();
private:
	AVFormatContext* pFormatCtx;
	AVCodecContext* pCodecCtx;
	AVCodec* pCodec;
};

