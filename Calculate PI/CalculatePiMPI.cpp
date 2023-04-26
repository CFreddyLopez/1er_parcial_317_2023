#include <math.h> 
#include <mpi.h>   // Biblioteca de MPI
#include <cstdlib> // Incluido para el uso de atoi
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{

#pragma region Variables
	int num_Interactions, 
		rank, 
		size; 
	double aproximate_Pi = 3.141592653589793238462643;
	double local_Pi, 
		global_Pi,   
		sum;  
#pragma endregion

#pragma region Inicialice MPI
	MPI_Init(&argc, &argv); 
	MPI_Comm_size(MPI_COMM_WORLD, &size); 
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
#pragma endregion

#pragma region Enter and Send Precision
	if (rank == 0)
	{
		cout << "Introduce la precision del calculo : ";
		cin >> num_Interactions;
	}
	MPI_Bcast(&num_Interactions, 1, MPI_INT, 0, MPI_COMM_WORLD);
#pragma endregion


	if (num_Interactions <= 0)
	{
		cout << "Imposible calcular PI con una precision inferior a 1... ";
		MPI_Finalize();
		exit(0);
	}
	else {
		// Calculo de PI
		sum = 0.0000000000000;
		for (int i = rank ; i <= num_Interactions; i += size) {
#pragma region PI_Leibniz
			sum += pow(-1, i) / (2 * i + 1);
#pragma endregion

			
		}
		local_Pi = sum;
		
		MPI_Reduce(&local_Pi, &global_Pi, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		if (rank == 0)
		{
			cout << "El valor aproximado de PI es: " << global_Pi * (double)4 << endl;
			cout << "Precision de: " << num_Interactions << " Sumas Interactivas" << endl;
			cout << "Con un error de " << fabs(global_Pi * (double)4 - aproximate_Pi) << endl;
		}
	}
	MPI_Finalize();
	return 0;
}