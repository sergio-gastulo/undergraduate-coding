#include <iostream>
#include <string>
 
using namespace std;
 
int main()
{
//definimos la cadena y la inicializamos
string str="Hola!";
 
//mostramos el tamaño antes de usar resize()
cout<<"nLa longitud antes de usar resize() es: "<<str.length()<<endl<<endl;
 
//aplicamos el .resize() para el doble de la longitud
str.resize(str.length()*2);
 
//mostramos la nueva longitud
cout<<"La nueva longitud de la cadena str es: "<<str.length()<<endl<<endl;
 
//la cadena permanece inalterada
cout<<"La cadena continua siendo: "<<str<<endl<<endl;
 
return 0;
}