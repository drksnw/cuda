#include "RipplingMath.h"
#include "Rippling.h"

#include <iostream>
#include <omp.h>
#include "OmpTools.h"

#include "IndiceTools_CPU.h"
using cpu::IndiceTools;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

Rippling::Rippling(uint w, uint h, float dt) :
	Animable_I<uchar4>(w, h, "Rippling_OMP_rgba_uchar4")
    {
    // Input
    this->dt = dt;  // animation

    // Tools
    this->t = 0;					// protected dans super classe Animable
    this->parallelPatern = ParallelPatern::OMP_MIXTE;   // protected dans super classe Animable

    // OMP
    cout << "\n[Rippling] : OMP : nbThread = " << this->nbThread << endl; // protected dans super classe Animable
    }

Rippling::~Rippling(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
void Rippling::animationStep()
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Override (code naturel omp)
 * Image non zoomable : domaineMath pas use ici
 */
void Rippling::processForAutoOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    RipplingMath ripplingMath(w);

#pragma omp parallel for
    for (int i = 0; i < h; i++)
	{
	for (int j = 0; j < w; j++)
	    {
	    int s = IndiceTools::toS(w, i, j);
	    ripplingMath.colorIJ(&ptrTabPixels[s], i, j, t);
	    }
	}

    }

/**
 * Override (code entrainement cuda)
 * Image non zoomable : domaineMath pas use ici
 */
void Rippling::processEntrelacementOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    RipplingMath ripplingMath(w);
    const int WH = w * h;

#pragma omp parallel
	{
	const int NB_THREADS = OmpTools::getNbThread();
	const int TID = OmpTools::getTid();
	int s = TID;
	int i;
	int j;

	while (s < WH)
	    {
	    IndiceTools::toIJ(s, w, &i, &j);

	    ripplingMath.colorIJ(&ptrTabPixels[s], i, j, t);

	    s += NB_THREADS;
	    }
	}

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

