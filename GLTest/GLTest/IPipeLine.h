#pragma once

#include "Camera.h"
enum PipeLineType {
	PipeLine_HelloTriangles,
	PipeLine_GlslTest,
	PipeLine_TextureTest,
	PipeLine_Light_Color,
};

class IPipeLine
{
public:
	virtual void prepare() = 0;
	virtual void flush() = 0;
	virtual void release() = 0;

	virtual void ProcessMouseMovement(float xoffset, float yoffset) {}
	virtual void ProcessMouseScroll(float yoffset){}
	virtual void ProcessKeyboard(Camera_Movement key,float deltaTime) {}

	static IPipeLine* createPipeLine(PipeLineType type);
};