#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "IndiceTools_GPU.h"

#include "RaytracingMath.h"
using namespace gpu;

__global__ void raytracing(uchar4* ptrDevPixels, Sphere* ptrDevTabSphere, uint w, uint h, uint nbSphere, float t);

__global__ void raytracing(uchar4* ptrDevPixels, Sphere* ptrDevTabSphere, uint w, uint h, uint nbSphere, float t)
    {
    RaytracingMath raytracingMath(ptrDevTabSphere, nbSphere);
    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();
    const int WH = w * h;

    int s = TID;
    int i;
    int j;

    while(s < WH)
	{
	IndiceTools::toIJ(s, w, &i, &j);
	raytracingMath.colorXY(&ptrDevPixels[s], i, j, t);
	s += NB_THREAD;
	}
    }
