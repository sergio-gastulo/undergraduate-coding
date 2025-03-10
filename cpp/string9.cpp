#include <iostream>
#include <string>
 
using namespace std;
 
int main(){
//definimos la cadena y la dejamos sin contendio
    string lectura1, lectura2;
 
//se pide el ingreso de la cadena
//dos veces para hacer dos lecturas
    cout<<"nIngrese la palabra: ";
    cin>>lectura1;
//limpiamos el buffer antes de la siguiente lectura
    cin.ignore(256,'\n');
    cout<<"nIngrese nuevamente la palabra: ";
    getline(cin,lectura2);
 
//imprimendo el resultado de las lecturas
    cout<<"nCapturando con cin>>lectura1 se obtuvo:        "<<lectura1<<endl<<endl;
    cout<<"Capturando con getline(cin,lectura2) se obtuvo: "<<lectura2<<endl<<endl;
    return 0;
}