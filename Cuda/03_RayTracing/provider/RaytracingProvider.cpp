#include "RaytracingProvider.h"
#include "Raytracing.h"

#include "MathTools.h"
#include "Grid.h"

Animable_I<uchar4>* RaytracingProvider::createAnimable()
    {
    float dt = 0.01;

    int dw = 16*60;
    int dh = 16*60;

    int mp = Device::getMPCount();
    int coreMP = Device::getCoreCountMP();

    dim3 dg(mp, 2, 1);
    dim3 db(coreMP, 2, 1);

    Grid grid(dg, db);

    return new Raytracing(grid, dw, dh, dt, 50);
    }

Image_I* RaytracingProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0,1,0);
    return new ImageAnimable_RGBA_uchar4(createAnimable(),colorTexte);
    }
