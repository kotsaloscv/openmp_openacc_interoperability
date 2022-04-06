// nvc++ -mp=gpu -acc mix_openmp_openacc.cpp
// nvprof --print-gpu-trace ./a.out
#include <iostream>
#include <omp.h>
#include <openacc.h>

int main() {

    int N = 10;
    int *x = new int[N];

    std::cout << "Number of devices : " << omp_get_num_devices() << std::endl;

    int *x_dev = (int *)acc_malloc(N*sizeof(int));
    omp_target_associate_ptr(x, x_dev, N*sizeof(int), 0, 0);
    
    #pragma omp target loop is_device_ptr(x_dev)
    for (int i=0; i<N; ++i)
        x[i] = 2; //x_dev[i] = 2;
    
    #pragma acc exit data copyout(x[0:N])

    for (int i=0; i<N; ++i)
        std::cout << x[i] << " ";
    std::cout << std::endl;

    delete [] x;
    return 0;
}
