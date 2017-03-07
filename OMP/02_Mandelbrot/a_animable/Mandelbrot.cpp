#include "Mandelbrot.h"
#include "MandelbrotMath.h"

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

Mandelbrot::Mandelbrot(uint w, uint h, float dt, const DomaineMath& domaineMath) :
	Animable_I<uchar4>(w, h, "Mandelbrot_OMP", domaineMath), variateurAnimation(Interval<float>(0, 120), dt)
    {
    //Input
    this->n = 0;

    // Tools
    this->t = 42;					// protected dans super classe Animable
    this->parallelPatern = ParallelPatern::OMP_MIXTE;   // protected dans super classe Animable

    // OMP
    cout << "\n[Mandelbrot] : OMP : nbThread = " << this->nbThread << endl; // protected dans super classe Animable

    }

Mandelbrot::~Mandelbrot()
    {
    //Rien
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
void Mandelbrot::animationStep()
    {
    this->n = variateurAnimation.varierAndGet();
    this->t = this->n; // Needed to show actual N in the window
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void Mandelbrot::processForAutoOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    MandelbrotMath mandelbrotMath(n);

#pragma omp parallel for
    for (int i=0; i<h; i++){
	for(int j=0; j<w; j++){
	    int s = IndiceTools::toS(w, i, j);

	    workPixel(&ptrTabPixels[s], i, j, domaineMath, &mandelbrotMath);
	}
    }
    }

void Mandelbrot::processEntrelacementOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    MandelbrotMath mandelbrotMath(n);
    const int WH = w * h;

#pragma omp parallel
	{
	const int NB_THREAD = OmpTools::getNbThread();
	const int TID = OmpTools::getTid();

	int i;
	int j;

	int s = TID;
	while (s < WH)
	    {
	    IndiceTools::toIJ(s, w, &i, &j);
	    workPixel(&ptrTabPixels[s], i, j, domaineMath, &mandelbrotMath);

	    s += NB_THREAD;
	    }
	}
    }

void Mandelbrot::workPixel(uchar4* ptrColorIJ, int i, int j, const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath)
    {
    double x;
    double y;

    domaineMath.toXY(i, j, &x, &y);

    ptrMandelbrotMath->colorXY(ptrColorIJ, x, y);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

