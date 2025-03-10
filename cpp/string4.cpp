#include <iostream>
#include <string>
 
using namespace std;
 
int main()
{
//definimos e inicializamos ambas cadenas
string str1="Julio ", str2="Cesar";
 
//realizamos la concatenación de ambas variables
str1+=str2;
 
//mostramos el nuevo contendio de str1
cout<<"El nuevo contenido de str1 es: "<<str1<<endl;
return 0;
}