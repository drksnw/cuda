#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "MathTools.h"

#include "IndiceTools_GPU.h"
#include "DomaineMath_GPU.h"

#include "MandelbrotMath.h"
using namespace gpu;

// Attention : 	Choix du nom est impotant!
//		VagueDevice.cu et non Vague.cu
// 		Dans ce dernier cas, probl�me de linkage, car le nom du .cu est le meme que le nom d'un .cpp (host)
//		On a donc ajouter Device (ou n'importequoi) pour que les noms soient diff�rents!

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, float t, DomaineMath domaineMath);
__device__ void workPixel(uchar4* ptrColorIJ, int i, int j, const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void mandelbrot(uchar4* ptrDevPixels, uint w, uint h, float t, DomaineMath domaineMath)
    {
    MandelbrotMath mandelbrotMath(t);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();
    const int WH = w * h;

    int s = TID;
    int i;
    int j;

    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &i, &j);

	workPixel(&ptrDevPixels[s], i, j, domaineMath, &mandelbrotMath);

	s += NB_THREAD;
	}
    }

__device__ void workPixel(uchar4* ptrColorIJ, int i, int j, const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath)
    {
    double x;
    double y;

    domaineMath.toXY(i, j, &x, &y);

    ptrMandelbrotMath->colorXY(ptrColorIJ, x, y);
    }


/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
