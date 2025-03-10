#include <iostream>
#include <string>
 
using namespace std;
 
int main()
{
//forma #1 de inicialización
//aunque prácticamente no se usa
string cad_1("Hola mundo");
cout<< cad_1<<endl;
//forma #2 de inicializar y asignar una cadena
string cad_2 = "Segunda forma";
cout<< cad_2<<endl;

//asignar/copiar cad_1 en cad_2
cad_2 = cad_1;
cout<<cad_2<<endl;
//asiganr un solo caracter a un tipo string
cad_1 = 'P';
cout<< cad_1<<endl;
return 0;
}