#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_GPU.h"
#include "Sphere.h"

using namespace gpu;

class RaytracingMath
    {
    public:
	__device__ RaytracingMath(Sphere* ptrDevTabSpheres, uint nbSpheres)
	    {
	    this->ptrDevTabSphere = ptrDevTabSpheres;
	    this->nbSpheres = nbSpheres;
	    }
	__device__ ~RaytracingMath()
	    {

	    }

	__device__ void colorXY(uchar4* ptrColor, float x, float y, float t)
	    {

	    float2 xySol;
	    xySol.x = x;
	    xySol.y = y;
	    Sphere* topSphere = getSphereUnder(xySol);
	    if(topSphere == nullptr)
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}
	    else
		{
		float hcarre = topSphere->hCarre(xySol);
		float hue = topSphere->getHueStart();

		float dz = topSphere->dz(hcarre);
		float distance = topSphere->distance(dz);
		float brightness = topSphere->brightness(dz);
		float3 hsb;
		hsb.x = hue;
		hsb.y = distance;
		hsb.z = brightness;
		ColorTools::HSB_TO_RVB(hsb, ptrColor);
		}
	    ptrColor->w = 255;


	    }

	__device__ Sphere* getSphereUnder(float2 xySol)
	    {
	    int s = 0;
	    while (s < this->nbSpheres)
		{
		float hcarre = ptrDevTabSphere[s].hCarre(xySol);
		if(ptrDevTabSphere[s].isEnDessous(hcarre))
		    {
		    return &ptrDevTabSphere[s];
		    }
		s++;
		}
	    return nullptr;
	    }

    private:
	Sphere* ptrDevTabSphere;
	uint nbSpheres;
    };
