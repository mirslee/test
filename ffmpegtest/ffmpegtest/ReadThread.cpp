#include "stdafx.h"
#include "ReadThread.h"


static int decoder_reorder_pts = -1;
int decoder_decode_video(AVFormatContext *formatCtx, AVCodecContext *avctx, AVFrame *frame)
{
	int ret = AVERROR(EAGAIN);
	if (AVMEDIA_TYPE_VIDEO == avctx->codec_type)
	{
		ret = avcodec_receive_frame(avctx, frame);
		if (ret >= 0) {
			if (decoder_reorder_pts == -1) {
				frame->pts = frame->best_effort_timestamp;
			}
			else if (!decoder_reorder_pts) {
				frame->pts = frame->pkt_dts;
			}
		}

		if (ret == AVERROR_EOF) {
			avcodec_flush_buffers(avctx);
			return 0;
		}
		if (ret >= 0)
			return 1;
	}

	return -1;
}

ReadThread::ReadThread()
:MyThread()
{
	pFormatCtx = nullptr; 
	pCodecCtx = nullptr;
	pCodec = nullptr;
}


ReadThread::~ReadThread()
{
	if (pFormatCtx)
	{
		avformat_free_context(pFormatCtx);
		pFormatCtx = nullptr;
	}
}

void ReadThread::run()
{
	pFormatCtx = avformat_alloc_context();
	if (0 != avformat_open_input(&pFormatCtx, "F:\\Rambo.III.1988.BDRip.1080p.x264.DTSHD.Audio-CHD.Sample.avi", nullptr, nullptr))
		return;

	int videoStream = -1;
	for (int i = 0; i < pFormatCtx->nb_streams; i++) {
		if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoStream = i;
			break;
		}
	}

	if (-1 == videoStream)
		return;

	AVCodecContext* pCodecCtx = avcodec_alloc_context3(NULL);
	AVCodecParameters *codecpar = pFormatCtx->streams[videoStream]->codecpar;
	int ret = avcodec_parameters_to_context(pCodecCtx, codecpar);
	AVCodec* pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

	if (pCodec) {
		if (avcodec_open2(pCodecCtx, pCodec, NULL) == 0) {
			int y_size = pCodecCtx->width * pCodecCtx->height;
			/*SwsContext* swsCtx = sws_getContext(pCodecCtx->width,
				pCodecCtx->height,
				(AVPixelFormat)codecpar->format,
				pCodecCtx->width,
				pCodecCtx->height,
				AV_PIX_FMT_BGRA,
				SWS_BICUBIC,
				NULL, NULL, NULL);*/
			Uint8* pimgData = new Uint8[pCodecCtx->width * pCodecCtx->height * 4];

			AVPacket* packet = new AVPacket;
			av_new_packet(packet, y_size);

			AVFrame *frame = av_frame_alloc();
			while (av_read_frame(pFormatCtx, packet) >= 0) {

				if (packet->stream_index != videoStream)
					continue;

				avcodec_send_packet(pCodecCtx, packet);
				if (avcodec_receive_frame(pCodecCtx, frame) != 0)
					continue;

				int stride = pCodecCtx->width * 4;
				/*sws_scale(swsCtx,
					frame->data,
					frame->linesize,
					0,
					pCodecCtx->height,
					&pimgData,
					&stride);*/
			}
		}
	}
}