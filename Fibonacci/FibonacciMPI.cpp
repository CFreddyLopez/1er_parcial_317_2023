#include <iostream>
#include <mpi.h>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    int num_Elements, size, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        cout << "Ingrese la cantidad de elementos de la Serie Fibonacci a calcular: ";
        cin >> num_Elements;
    }


    MPI_Bcast(&num_Elements, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int chunk_size = ceil((double)num_Elements / size);
    int start = rank * chunk_size;
    int end = min(num_Elements, start + chunk_size);

    double phi = (1 + sqrt(5)) / 2;
    double psi = (1 - sqrt(5)) / 2;
    unsigned long long fib;

   unsigned long long* fib_array = new unsigned long long[end - start];

    for (int i = start; i < end; i++) {
        fib =(pow(phi, i) - pow(psi, i)) / sqrt(5);
        fib_array[i - start] = fib;
    }

    unsigned long long* result_array = NULL;

    if (rank == 0) {
        result_array = new unsigned long long[num_Elements];
    }

    MPI_Gather(fib_array, end - start, MPI_UNSIGNED_LONG_LONG, result_array, end - start, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Los primeros " << num_Elements << " elementos de la Serie Fibonacci son: ";
        for (int i = 0; i < num_Elements; i++) {
            cout << (unsigned long long)result_array[i] << endl;
        }
        cout << endl;
    }

    delete[] fib_array;
    delete[] result_array;

    MPI_Finalize();
    return 0;
}