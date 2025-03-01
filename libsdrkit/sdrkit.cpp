#include "sdrkit.h"

#ifdef USE_CUDA
#include <cuda_runtime_api.h>
#endif

sdrkit::sdrkit()
{

}

sdrkit::~sdrkit()
{

}

void sdrkit::Initialize()
{
#ifdef USE_CUDA
    int numcudadevices = 0;
    cudaGetDeviceCount (&numcudadevices);
    if(numcudadevices >= 0 )
    {
        has_cuda = true;
    }
#endif
}
