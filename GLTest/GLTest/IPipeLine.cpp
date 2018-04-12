#include "stdafx.h"
#include "IPipeLine.h"
#include "HelloTriangles.h"
#include "GlslTest.h"


IPipeLine* IPipeLine::createPipeLine(PipeLineType type)
{
	switch (type)
	{
	case PipeLine_HelloTriangles:
		return new HelloTriangles();
	case PipeLine_GlslTest:
		return new GlslTest();
	default:
		return nullptr;
	}
}