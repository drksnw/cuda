#pragma once

#include "cudaTools.h"

#include "Provider_I_GPU.h"
using namespace gpu;

class RaytracingProvider: public Provider_I<uchar4>
    {
    public:
	virtual Animable_I<uchar4>* createAnimable(void);
	virtual Image_I* createImageGL(void);
    };
