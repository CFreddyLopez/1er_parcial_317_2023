#include <iostream>
#include <omp.h>
#include <cmath>

using namespace std;

int main() {
    int num_Interactions;
    double  pi = 0.0,
            sum=0.0;

    double aproximate_Pi = 3.141592653589793238462643;
    cout << "Ingrese la Precision del calculo: ";
    cin >> num_Interactions;

#pragma omp parallel for reduction(+:pi)
    for (int i = 0; i < num_Interactions; i++) {
        sum += pow(-1, i) / (2 * i + 1);
    }

    pi = sum * 4;
    cout << "El valor aproximado de PI es: " << pi << endl;
    cout << "Precision de: " << num_Interactions << " Sumas Interactivas" << endl;
    cout << "Con un error de " << fabs(pi - aproximate_Pi) << endl;
    cin >> num_Interactions;
    cout << "";
    return 0;
}
