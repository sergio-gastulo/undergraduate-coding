#include<iostream>
using namespace std;
int main(){
	int D;
	cout << "Coloque el d�a en el que se encuentra para mostrar horario, recuerde que lunes es 1 y domingo es 7: ";
	cin >> D;
	switch (D){ 
		case 1:
			cout << "Hoy toca pr�ctica de c�lculo, qu�mica y f�sica." << endl;
			break;
		case 2:
			cout << "Hoy toca �lgebra lineal y c�lculo." << endl;
			break;
		case 3:
			cout << "Hoy toca pr�ctica de �lgebra lineal, qu�mica y f�sica." << endl;
			break;
		case 4:
			cout << "Hoy toca �lgebra lineal y c�lculo." << endl;
			break;
		case 5:
			cout << "Hoy toca laboratorio de f�sica y qu�mica." << endl;
			break;
		case 6:
			cout << "Hoy toca introducci�n a la ciencia de la computaci�n y tambien trabajar." << endl;
			break;
		case 7:
			cout << "Revisa si tienes tarea por hacer y alista la mochila, sino descansa todo el d�a :)." << endl;
			break;
		default:
			cout << "Revise su n�mero correctamente." << endl;
		}
return 0;
}
