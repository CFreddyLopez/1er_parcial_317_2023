#include <iostream>
#include <string>
#include <mpi.h>

using namespace std;

bool is_Palindrome(string str) {
    int len = str.length();
    for (int i = 0; i < len / 2; i++) {
        if (str[i] != str[len - i - 1]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    int id, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    string input_str;
    bool local_result;
    bool global_result;
    if (id == 0) {
        cout << "Introduce una palabra: ";
        cin >> input_str;
        MPI_Bcast(&input_str, input_str.length() + 1, MPI_CHAR, 0, MPI_COMM_WORLD);
        
    }
    local_result = is_Palindrome(input_str);
    
    MPI_Reduce(&local_result, &global_result, 1, MPI_C_BOOL, MPI_LAND, 0, MPI_COMM_WORLD);
    if (id == 0) {
        if (global_result) {
            cout << "La palabra " << input_str << " es un palindromo" << endl;
        }
        else {
            cout << "La palabra " << input_str << " no es un palindromo" << endl;
        }
    }
    MPI_Finalize();
    return 0;
}