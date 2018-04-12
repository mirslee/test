#pragma once


enum PipeLineType {
	PipeLine_HelloTriangles,
};

class IPipeLine
{
public:
	virtual void prepare() = 0;
	virtual void flush() = 0;
	virtual void release() = 0;

	static IPipeLine* createPipeLine(PipeLineType type);
};