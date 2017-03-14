#pragma once

#include <math.h>
#include "MathTools.h"

#include "ColorTools_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ RipplingMath(int w, int h)
	    {
	    this->dim2 = w / 2;
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	__device__
	     virtual ~RipplingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColor, int i, int j, float t)
	    {
	    uchar levelGris;

	    f(&levelGris, i, j, t); // update levelGris

	    ptrColor->x = levelGris;
	    ptrColor->y = levelGris;
	    ptrColor->z = levelGris;

	    ptrColor->w = 255; // opaque
	    }

    private:

	__device__
	void f(uchar* ptrLevelGris, float i, float j, float t)
	    {
	    float ptrDIJ;
	    dij(i, j, &ptrDIJ);
	    float dij10 = ptrDIJ / 10;
	    float numerateur = cosf(dij10 - t / (float)7);
	    float denominateur = dij10 + (float)1;
	    *ptrLevelGris = (float)128 + (float)127 * (numerateur / denominateur);
	    }

	__device__
	void dij(float i, float j, float* ptrResult)
	    {
	    float fi = i - dim2;
	    float fj = j - dim2;
	    *ptrResult = sqrtf(fi * fi + fj * fj);
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	float dim2;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
