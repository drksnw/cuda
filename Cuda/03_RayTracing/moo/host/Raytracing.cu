#include "Device.h"
#include "Raytracing.h"

extern __global__ void raytracing(uchar4* ptrDevPixels, Sphere* ptrDevTabSphere, uint w, uint h, uint nbSphere, float t); //CUDA Kernel

Raytracing::Raytracing(const Grid& grid, uint w, uint h, float dt, int nbSpheres) :
		Animable_I<uchar4>(grid, w, h, "Raytracing_Cuda_RGBA_uchar4")
    {
    this->dt = dt;
    this->nbSpheres = nbSpheres;
    this->sizeOctet = nbSpheres * sizeof(Sphere);

    this->t = 0;

    SphereCreator sphereCreator(nbSpheres, w, h);
    Sphere* ptrTabSphere = sphereCreator.getTabSphere();

    //TODO: Transfer tab to GM
    Device::malloc(&ptrDevTabSphere, sizeOctet);
    Device::memclear(ptrDevTabSphere, sizeOctet);
    Device::memcpyHToD(ptrDevTabSphere, ptrTabSphere, sizeOctet);

    }

Raytracing::~Raytracing()
    {
    Device::free(ptrDevTabSphere);
    }

void Raytracing::animationStep()
    {
    t += dt;
    }

void Raytracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Device::lastCudaError("raytracing before");
    raytracing<<<dg, db>>>(ptrDevPixels, ptrDevTabSphere, w, h, this->nbSpheres, t);
    Device::lastCudaError("raytracing after");
    }
