// -mp=gpu -> Enable OpenMP targeting GPU and Multicore
// nvc++ -mp=gpu -acc openmp_to_cuda.cu
// nvprof --print-gpu-trace ./a.out
#include <iostream>
#include <omp.h>
#include <openacc.h>
#include <stdio.h>

__global__ void init(int*x) {
    int tid = threadIdx.x;
    x[tid] = 2;
}

int main() {

    int N = 10;
    int *x = new int[N];

    std::cout << "Number of devices : " << omp_get_num_devices() << std::endl;

    #pragma omp target data map(tofrom:x[0:N])
    {

        #pragma omp target data use_device_ptr(x)
        init<<<1,N>>>(x);

    }

    for (int i=0; i<N; ++i)
        std::cout << x[i] << " ";
    std::cout << std::endl;

    delete [] x;
    return 0;
}
