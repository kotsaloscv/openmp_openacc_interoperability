// nvc++ -mp=gpu -acc -cuda test.cpp
#include <iostream>
#include <omp.h>
#include <openacc.h>

int main() {

    int N = 10;
    int *x = new int[N];

    std::cout << "Number of devices : " << omp_get_num_devices() << std::endl;

    #pragma omp target enter data map(to:x[0:N])
    
    #pragma acc parallel loop present(x)
    for (int i=0; i<N; ++i)
        x[i] = 2;
    
    #pragma omp target exit data map(from:x[0:N])

    for (int i=0; i<N; ++i)
        std::cout << x[i] << " ";
    std::cout << std::endl;

    delete [] x;
    return 0;
}
