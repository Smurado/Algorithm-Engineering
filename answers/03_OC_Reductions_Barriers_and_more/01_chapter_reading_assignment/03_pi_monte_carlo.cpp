#include <iostream>
#include <omp.h>

using namespace std;

double rnd(unsigned int *seed) {
    *seed = (1140671485 * (*seed) + 12820163) % (1 << 24);
    return ((double)(*seed)) / (1 << 24);
}

int main() {

    // instead of using the for loop gets hardcoded
    unsigned int seeds[8] = {0,1,2,3,4,5,6,7};

    int n = 1e8; // number of points to generate
    int counter = 0; // counter for points lying in the first quadrant of a unit circle
    auto start_time = omp_get_wtime(); // omp_get_wtime() is an OpenMP library routine

    int num_threads = 8;

#pragma omp parallel for reduction(+:counter) num_threads(num_threads)

    // compute n points and test if they lie within the first quadrant of a unit circle
    for (int i = 0; i < n; ++i)
    {

        // implementation of the rnd function
        auto x = rnd(&seeds[omp_get_thread_num()]);
        auto y = rnd(&seeds[omp_get_thread_num()]);

        // if the point lies in the first quadrant of a unit circle
        if (x * x + y * y <= 1.0) ++counter;
    }


    auto run_time = omp_get_wtime() - start_time;
    auto pi = 4 * (double(counter) / n);

    cout << "Threads: " << num_threads << endl;
    cout << "pi: " << pi << endl;
    cout << "run_time: " << run_time << " s" << endl;
    cout << "n: " << n << endl;
}