#pragma once
#include "IPipeLine.h"

class Shader;
class TextureTest :
	public IPipeLine
{
public:
	TextureTest();
	~TextureTest();

	void prepare();
	void flush();
	void release();

private:
	unsigned int shaderProgram; //程序对象
	unsigned int VAO;//顶点数组id
	unsigned int VBO; //缓冲区id
	unsigned int EBO; //缓冲区id
	unsigned int texture; //纹理id
	Shader* pShader;
};

