#include <iostream>
using namespace std;
const int DIM = 100;

void leerArray(double [], int&);
void imprimirArray (const double [], const int);

int main(){
    double a[DIM];
    int n;
    leerArray(a, n);
    cout << "El array tiene " << n << " elementos\n son:\n";
    imprimirArray(a, n);
    return 0;
}

void leerArray(double a[], int& n){
    n = 0;
    cout << "Introduzca datos. Para terminar pulsar 0:\n";
    for (n = 0; n < DIM; n++){
         cout << n << " : ";
         cin >> a[n];
         if (a[n] == 0) break;
    }
}

void imprimirArray(const double a[], const int n){
    for (int i = 0; i < n; i++)
         cout << "\t" << i << " : " << a[i] << endl;
}




