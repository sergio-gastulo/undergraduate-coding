#include <iostream>
#include <string>
 
using namespace std;
 
int main()
{
//definimos los objetos string que vamos a usar
string str1="Hola Mundo";
string str2;
 
//asignamos a str2 la subcadena que está desde la posición 5 "M" y un tope maximo de 5 caracteres a obtener
str2=str1.substr(5,5); //"Mundo"
 
//mostramos los contenidos
cout<<"El contenido de str1 es: "<<str1<<endl;
cout<<"El contenido de str2 es: "<<str2<<endl;
return 0;
}