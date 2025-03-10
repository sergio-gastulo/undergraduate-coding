#include <iostream>
#include <string>
 
using namespace std;
 
int main()
{
//definimos la cadena y la dejamos sin contendio
string str1="Cesar";
string str2="Julio";
 
//mostramos sus contendios antes del intercambio con .swap()
cout<<"nstr1 = "<<str1<<endl<<endl;
cout<<"str2 = "<<str2<<endl<<endl;
 
//realizamos el intercambio
str1.swap(str2);
 
cout<<"ttdespues del intercambio.."<<endl<<endl;
 
//mostramos los nuevos contenidos
cout<<"nstr1 = "<<str1<<endl<<endl;
cout<<"str2 = "<<str2<<endl<<endl;
 
return 0;
}