#pragma once
#include "IPipeLine.h"
class GlslTest :
	public IPipeLine
{
public:
	GlslTest();
	~GlslTest();

	void prepare();
	void flush();
	void release();

private:
	unsigned int shaderProgram; //程序对象
	unsigned int VAO;//顶点数组id
	unsigned int VBO; //缓冲区id
};

