#include <iostream> 

using std::cout; 

struct Polimorfismo { 
    virtual ~Polimorfismo() {} 
}; 

enum Binario { cero, uno }; 
enum Intensidad { negro = 0, brillo = 1000 }; 

int main(){ 
    cout<<"Tamanyo ..." << '\n'; 
    cout << "Booleano " << sizeof(bool) << '\n'; 
    
    cout << "Cadena de caracteres " << sizeof(char) << '\n'; 
    cout << "Cadena de caracteres con signo " << sizeof(signed char) << '\n'; 
    cout << "Cadena de caracteres sin signo " << sizeof(unsigned char) << '\n'; 
    cout << "Wide char " << sizeof(wchar_t) << '\n'; 
    // No hay variantes con signo / sin signo
    cout << "Corto con signo " << sizeof(signed short) << '\n'; 
    cout << "Corto sin signo " << sizeof(unsigned short) << '\n'; 
    cout << "Entero con signo " << sizeof(signed int) << '\n'; 
    cout << "Entero sin signo " << sizeof(unsigned int) << '\n'; 
    cout << "Largo con signo " << sizeof(signed long) << '\n'; 
    cout << "Largo sin signo " << sizeof(unsigned long) << '\n'; 
    // Tipos fundamentales de coma flotante: 
    cout << "Coma flotante " << sizeof(float) << '\n'; 
    cout << "Double " << sizeof(double) << '\n'; 
    cout << "Long Double " << sizeof(long double) << '\n'; 
    //Tipos de puntero
    cout << "Puntero entero " << sizeof(int*) << '\n'; 
    cout << "Puntero apuntando a una funcion de enteros " << sizeof(int (*)()) << '\n'; 
    // Lo anterior corresponde a un puntero a una funci??n.
    //El siguiente es un puntero a una funci??n miembro:
    cout << "Puntero apuntando a una funcion de Polimorfismo " << sizeof(void (Polimorfismo::*)()) << '\n'; 
    cout << "Puntero apuntando a una funcion void " << sizeof(void*) << '\n'; 
    // Enumeration types: 
    cout << "Enumerate " << sizeof(Binario) << '\n'; 
    cout << "Enumerate " << sizeof(Intensidad) << '\n'; 
	
	return 0; 
} 

//*********************************************************************//
//                   Respuesta  de 1.1                                 //
//*********************************************************************//
/*                                                                     

El código muestra el tamaño exacato de bytes de cada tipo de data que 
tiene el programa, además de hacerlo con punteros y estructuras.



*/


//*********************************************************************//
//                   Respuesta  de 1.2                                 //
//*********************************************************************//
/*                                                                     


Lo que mas me llamó la atención fue el tamaño de los punteros que 
prácticamente doblan el tamaño de lo que apuntan. Además, ver el 
tamaño de enum también es destacado.


*/
