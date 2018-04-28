#include "stdafx.h"
#include "MediaReader.h"


MediaReader::MediaReader()
{

}


MediaReader::~MediaReader()
{
	if (pCodecCtx)
	{
		avcodec_free_context(&pCodecCtx);
		pCodecCtx = nullptr;
	}

	if (pFormatCtx)
	{
		avformat_free_context(pFormatCtx);
		pFormatCtx = nullptr;
	}
}

bool MediaReader::open(char* filepath)
{
	try
	{
		pFormatCtx = avformat_alloc_context();
		if (0 != avformat_open_input(&pFormatCtx, filepath, nullptr, nullptr))
			throw;

		int videoStream = -1;
		for (int i = 0; i < pFormatCtx->nb_streams; i++) {
			if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
				videoStream = i;
				throw;
			}
		}

		if (-1 == videoStream)
			throw;
	}
	catch (...)
	{
		if (pCodecCtx)
		{
			avcodec_free_context(&pCodecCtx);
			pCodecCtx = nullptr;
		}

		if (pFormatCtx)
		{
			avformat_free_context(pFormatCtx);
			pFormatCtx = nullptr;
		}

		return false;
	}

	return true;
}