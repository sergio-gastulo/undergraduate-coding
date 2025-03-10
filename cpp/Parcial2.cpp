#include <iostream>                                              
#include <iomanip>                                               

using namespace std; 

int main () {                                                    
    const double tasa_ninho = .25;  // Se define la tarifa de un niño de 12 años, 1/4 de lo normal.
    const double tasa_adulto = .5;  // Lo mismo con el adulto mayor, la mitad de la normal
	//la tasa es definida como cosntante para que no sea manipulada por el usuario
	
    double precios_basicos;         // Se define el precio del ticket  
    int    num_tickets_adultos;    // numero de tickets para adultos
    int    num_tickets_ninhos;    // numero de tickets para niños
    int    num_tickets_personas_mayores;   // numero de tickets para personas mayores

    double costAdult;    //  Coste subtotal debido a la cantidad de adultos
    double costNinh;    // Coste subtotal debido a la cantidad de niños
    double costPersonMayor;   // Coste subtotal debido a la cantidad de adultos mayores
    double costTotal;   // Coste total debido a adultos, niños y adultos mayores

    // Solo se admiten 2 decimales
    cout << fixed << setprecision (2);                              

    // Presentación                                
    cout << "Venta de entradas en taquilla de XYZ\n\n";                     

    // Se reciben los datos por parte del usuario
    cout << "Ingrese el precio basico de un boleto: ";                  
    cin >> precios_basicos;                                              
    cout << "........................................  ";       
    cin >> num_tickets_adultos;                                         
    cout << "........................................  ";       
    cin >> num_tickets_ninhos;                                         
    cout << "........................................ ";       
    cin >> num_tickets_personas_mayores;                                        

    // Operaciones para calcular los subtotales
    costAdult = num_tickets_adultos * precios_basicos;                       
    costNinh = num_tickets_ninhos * precios_basicos  * tasa_ninho;           
    costPersonMayor = num_tickets_personas_mayores * precios_basicos * tasa_adulto; 
    // Costo total a pagar
    costTotal = costAdult + costNinh + costPersonMayor;                

    // Imprimiendo los costos subtotales
    cout << endl;                                                   
    cout << "Numero de entradas para adultos:         "    << setw(4) << num_tickets_adultos << " = $"    << setw (6) << costAdult << endl;                          
    cout << "Numero de entradas para ninhos:          "    << setw(4) << num_tickets_ninhos << " = $"    << setw (6) << costNinh << endl;                          
    cout << "Numero de boletos de la tercera edad:    "    << setw(4) << num_tickets_personas_mayores << " = $"   << setw (6) << costPersonMayor << endl;                         
    cout << "Precio total de compra:                          $"    << setw (6) << costTotal << endl;                                                                 
    return 0; 
}
