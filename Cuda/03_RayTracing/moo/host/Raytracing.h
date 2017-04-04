#pragma once

#include "cudaTools.h"
#include "MathTools.h"

#include "Sphere.h"
#include "SphereCreator.h"

#include "Animable_I_GPU.h"
using namespace gpu;

class Raytracing: public Animable_I<uchar4>
    {
    public:
	Raytracing(const Grid& grid, uint w, uint h, float dt, int nbSpheres);
	virtual ~Raytracing(void);

	virtual void process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domainMath);
	virtual void animationStep();

    private:

	//Inputs
	int nbSpheres;
	float dt;

	size_t sizeOctet;

	Sphere* ptrDevTabSphere;

    };
