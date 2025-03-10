#include <iostream>
#include <vector>
 
using namespace std;
 
int main()
{
//vector de 20 elementos int iniclizados a 9
vector<int> A(20,9);
//declaramos un entero para almacenar el tamaño
int num_elementos;
//usamos el mtodo .size() que nos retornará la
//cantidad de elementos en A, que es 20
num_elementos=A.size();
//mostramos el numero que nos retornó el método .size()
// el valor que mostrará es 20
cout<<num_elementos<<endl;
 
return 0;
}