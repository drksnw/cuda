#pragma once

#include <math.h>
#include "MathTools.h"

#include "Calibreur_GPU.h"
#include "ColorTools_GPU.h"

using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {
    public:
	__device__
	MandelbrotMath(uint N) :
		calibreur(Interval<float>(1, N), Interval<float>(0, 1))
	    {
	    this->n = N;
	    }

	__device__
	virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:
	__device__
	void colorXY(uchar4* ptrColor, float x, float y)
	    {

	    int z = f(x, y, this->n);

	    if(z > this->n){
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
	    } else {
		float hue01 = (float)z;
		calibreur.calibrer(hue01);
		ColorTools::HSB_TO_RVB(hue01, ptrColor);
	    }

	    ptrColor->w = 255;

	    }

    private:
	__device__
	int f(float x, float y, uint N)
	    {
	    float a = 0;
	    float b = 0;
	    int k = 0;

	    while ((a * a + b * b) < 4 && k <= N)
		{
		float aCopy = a;
		a = ((a * a) - (b * b)) + x;
		b = (2 * aCopy * b) + y;
		k++;
		}
	    return k;
	    }

	Calibreur<float> calibreur;
	uint n;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
