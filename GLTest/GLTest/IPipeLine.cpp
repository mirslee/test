#include "stdafx.h"
#include "IPipeLine.h"
#include "HelloTriangles.h"
#include "GlslTest.h"
#include "TextureTest.h"


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
	default:
		return nullptr;
	}
}