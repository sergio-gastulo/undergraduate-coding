#include <iostream>
#include <string>
 
using namespace std;
 
int main()
{
//definimos la cadena y la inicializamos
string str="Hola!";
 
//mostramos los valores con diferentes métodos
cout<<"Longitud con el método .length(): "<<str.length()<<endl;
cout<<"Longitud con el método .size(): "<<str.size()<<endl;
 
return 0;
}