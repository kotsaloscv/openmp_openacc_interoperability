#include <iostream>
#include <omp.h>
#include <cmath>

int main(){

    int N = 100;
    double *x = new double[N];

    std::cout << "Number of devices : " << omp_get_num_devices() << std::endl;
    for (int i=0; i<N; ++i)
        x[i] = i;

    #pragma acc enter data copyin(x[0:N])
    
    #pragma acc parallel loop present(x)
    for (int i=0; i<N; ++i) {
        //x[i] *= std::exp(i*1e-4) + (i + std::pow(i, 3) * i)*1e-5;
        x[i] = std::exp((i+1)*1e-2);
        x[i] += std::pow((i+1)*1e-3, 3);
    }
    #pragma acc compare(x[0:N])
    
    #pragma acc exit data copyout(x[0:N])

    for (int i=0; i<N; ++i)
        std::cout << x[i] << " ";
    std::cout << std::endl;

    delete [] x;
    return 0;
}
