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
	unsigned int shaderProgram; //�������
	unsigned int VAO;//��������id
	unsigned int VBO; //������id
};

