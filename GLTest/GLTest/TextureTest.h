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
	unsigned int shaderProgram; //�������
	unsigned int VAO;//��������id
	unsigned int VBO; //������id
	unsigned int EBO; //������id
	unsigned int texture; //����id
	Shader* pShader;
};

