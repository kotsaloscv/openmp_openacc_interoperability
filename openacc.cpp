// -mp=gpu -> Enable OpenMP targeting GPU and Multicore
// nvc++ -mp=gpu -acc openacc.cpp
// nvprof --print-gpu-trace ./a.out
#include <iostream>
#include <omp.h>

int main(){

    int N = 10;
    int *x = new int[N];

    std::cout << "Number of devices : " << omp_get_num_devices() << std::endl;

    #pragma acc enter data copyin(x[0:N])
    
    #pragma acc parallel loop present(x)
    for (int i=0; i<N; ++i)
        x[i] = 2;
    
    #pragma acc exit data copyout(x[0:N])

    for (int i=0; i<N; ++i)
        std::cout << x[i] << " ";
    std::cout << std::endl;

    delete [] x;
    return 0;
}
