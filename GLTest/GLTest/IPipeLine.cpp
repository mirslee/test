#include "stdafx.h"
#include "IPipeLine.h"
#include "HelloTriangles.h"


IPipeLine* IPipeLine::createPipeLine(PipeLineType type)
{
	switch (type)
	{
	case PipeLine_HelloTriangles:
		return new HelloTriangles();
	default:
		return nullptr;
	}
}