// nvc++ -mp=gpu -acc -cuda test.cpp
#include <iostream>
#include <omp.h>
#include <openacc.h>

int main() {

    int N = 100000;
    int *x = new int[N];

    std::cout << "Number of devices : " << omp_get_num_devices() << std::endl;
    for (int i=0; i<N; ++i)
        x[i] = 1;

    #pragma acc data copy(x[0:N])
    {    
        #pragma omp target loop
        for (int i=0; i<N; ++i)
            x[i] = 2;
    }

    for (int i=0; i<N; ++i)
        std::cout << x[i] << " ";
    std::cout << std::endl;

    delete [] x;
    return 0;
}
