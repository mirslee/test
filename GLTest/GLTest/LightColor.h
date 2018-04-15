#pragma once
#include "IPipeLine.h"
class LightColor :
	public IPipeLine
{
public:
	LightColor();
	~LightColor();

	void prepare();
	void flush();
	void release();

	void ProcessMouseMovement(float xoffset, float yoffset);
	void ProcessMouseScroll(float yoffset);
	void ProcessKeyboard(Camera_Movement key, float deltaTime);

private:


private:
	unsigned int cubeVAO;
	unsigned int cubeVBO;
	unsigned int cubeShaderProgram;

	unsigned int lampVAO;
	unsigned int lampVBO;
	unsigned int lampShaderProgram;

	unsigned int tempShaderProgram;
};

