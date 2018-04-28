#pragma once


class MyThread;
class MediaReader
{
public:
	MediaReader();
	~MediaReader();

	bool open(char* filepath);
public:
	AVFormatContext* pFormatCtx = nullptr;
	AVCodecContext* pCodecCtx = nullptr;

	MyThread* pVideoDecodeThread = nullptr;
	MyThread* pAudioDecodeThread = nullptr;
};

