#pragma once

#include "MandelbrotMath.h"

#include "cudaType_CPU.h"
#include "Variateur_CPU.h"
#include "Animable_I_CPU.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class Mandelbrot: public Animable_I<uchar4>
    {
    public:
	Mandelbrot(uint w, uint h, float dt, const DomaineMath& domaineMath);

	virtual ~Mandelbrot(void);

    public:

	/*-------------------------*\
		|*   Override Animable_I   *|
	 \*------------------------*/

	/**
	 * Call periodicly by the api
	 */
	virtual void processEntrelacementOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath);

	/**
	 * Call periodicly by the api
	 */
	virtual void processForAutoOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath);

	/**
	 * Call periodicly by the api
	 */
	virtual void animationStep();

    private:
	void workPixel(uchar4* ptrColorIJ, int i, int j, const DomaineMath& domaineMath, MandelbrotMath* ptrMandelbrotMath);

    private:

	//Inputs
	uint n;

	//Tools
	Variateur<float> variateurAnimation;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
