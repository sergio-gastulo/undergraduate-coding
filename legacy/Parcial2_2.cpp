#include <iostream>                                              
#include <iomanip>              
using namespace std; 

class Ticket{ //Creamos la clase ticket formada por cantidad de niños, adultos, y adultos mayores
	private:
		int ninyos, mayores, adultos;
		double precio;
	public:
		Ticket(int n, int m, int a) : ninyos(n), mayores(m), adultos(a) {}
		friend int Ninhos(Ticket T){
			return T.ninyos; //Para poder retornar el numero de niños de un ticket
		}
		friend int Mayores(Ticket T){
			return T.mayores; //Para poder retornar el numero de adultos mayores de un ticket
		}
		friend int Adult(Ticket T){
			return T.adultos; //Para poder retornar el numero de adultos de un ticket
		}
		~Ticket(){}
};

int main () {                   
	
    double precio_basico;         // Se define el precio del ticket  
    int    num_tickets_adultos;    // numero de tickets para adultos
    int    num_tickets_ninhos;    // numero de tickets para niños
    int    num_tickets_personas_mayores;   // numero de tickets para personas mayores

    // Recogiendo datos
    cout << "\nIngrese el precio basico de un boleto: \n";                  
    cin >> precio_basico;                                              
	cout << '\n';
	cout<<"Ingrese la cantidad de ninyos con los que viene: \n";
	cin>> num_tickets_ninhos;
	cout<<"Ingrese la cantidad de adultos con los que viene (incluyase): \n";
	cin>> num_tickets_adultos;
	cout<<"Ingrese la cantidad de adultos mayores con los que viene: \n";
	cin>> num_tickets_personas_mayores;
	//Se crea el objeto Ticket con los datos obtenidos previamente
	Ticket T(num_tickets_ninhos,num_tickets_personas_mayores,num_tickets_adultos);
    
    // Solo tener 2 decimales
    cout << fixed << setprecision (2);                              

    // Presentación                                         
    cout << "\n\nVenta de entradas en taquilla de XYZ\n\n";                     

    // Imprimiendo datos
    cout << endl;                                                   
    cout << "Numero de entradas para adultos:         "    << setw(4) << Adult(T) << " = $"    << setw (6) << Adult(T)*precio_basico << endl;                          
    cout << "Numero de entradas para ninhos:          "    << setw(4) << Ninhos(T) << " = $"    << setw (6) << Ninhos(T)*precio_basico*0.25 << endl;                          
    cout << "Numero de boletos de la tercera edad:    "    << setw(4) << Mayores(T) << " = $"   << setw (6) << Mayores(T)*precio_basico*0.5 << endl;                         
    cout << "Precio total de compra:                          $"    << setw (5) << Adult(T)*precio_basico + Ninhos(T)*precio_basico*0.25 + Mayores(T)*precio_basico*0.5  << endl;                                                                 
    return 0; 
}
