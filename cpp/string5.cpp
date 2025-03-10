#include <iostream>
#include <string>
 
using namespace std;
 
int main()
{
string str = "abcdefgh";
 
//a continuación buscamos la subcadena "wkf" entre str, si no está presente, retorna la constante npos
//que es equivalente a NULL en el tipo string, en este código se mostrará que la cadena no fue encontrada
//el método find() nos retorna la posición del primer caracter del argumento que aparece en la cadena str.
if(str.find("wkf")==string::npos)
    cout<<"cadena no encontrada"<<endl;
else
    cout<<"cadena encontrada.."<<endl;
 
cout<<str.find_first_of("cde")<<endl; //retorna la posición del caracter que aparezca primero de esos 3
 
cout<<str.find_last_of("cde")<<endl; //retorna la posición del caracter que aparezca de último entre esos 3
 
cout<<str.find_first_not_of("cde")<<endl;//retorna la posición del primer caracter en str que sea diferente a todos los del argumento
 
cout<<str.find_last_not_of("cde")<<endl; // retorna la posición del ultimo caracter en str que sea diferente de todos los del argumento
 
return 0;
}