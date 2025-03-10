/*Realice un programa en el cual se permita controlar el tránsito de usuarios de una plataforma de videojuegos. */
#include<iostream>
#include<string.h>
using namespace std;
int main()
{
	int c;
	string d;
	cout << "Bienvenido a GAMEUNI, ¿desea jugar algún juego? Coloque sí (1) o no (0). ";
	cin >> c;
	if (c==1){
	while (c==1)
	{
		cout << "Coloque el juego que desea jugar. Recuerde, sólo las iniciales del juego por favor." << endl;
		cin >> d;
		cout << "Disfrute " << d << ". ¿Desea agregar algo más (0;1)?" << endl;
		cin >> c;
	}
	cout << "Disfrute sus juegos elegidos, será atendido en unos minutos. Gracias por visitar GAMEUNI."<< endl;}
	else if (c==0){
	cout << "Debes estar ocupado, sigue estudiando y nos vemos más tarde." << endl;}
	else 
	{cout << "ERROR." << endl;} 
return 0;
}

/*En el presente programa se ha usado 'while', no 'do while' ni 'for'. Esto se debe a que si usáramos el 'do while', podría suceder que el usuario coloque 'no (0)' en la primera vez, y como usamos el do while, el código se realizaría al menos una vez, y por consiguiente, a pesar de negar al código este se ejecutaría. Además, si usáramos el 'for', necesitaríamos un contador y dado que no se conoce -y no hay manera de determinarlo- cuantos juegos desee el usuario -aunque se podría restringir la cantidad de juegos, pero no es el punto-, no podemos agregar un contador; por lo que el 'for' quedaría obsoleto. */
