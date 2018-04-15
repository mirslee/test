#include "stdafx.h"
#include "IPipeLine.h"
#include "HelloTriangles.h"
#include "GlslTest.h"
#include "TextureTest.h"
#include "LightColor.h"


IPipeLine* IPipeLine::createPipeLine(PipeLineType type)
{
	switch (type)
	{
	case PipeLine_HelloTriangles:
		return new HelloTriangles();
	case PipeLine_GlslTest:
		return new GlslTest();
	case PipeLine_TextureTest:
		return new TextureTest();
	case PipeLine_Light_Color:
		return new LightColor();
	default:
		return nullptr;
	}
}