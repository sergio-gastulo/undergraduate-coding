#include<iostream>
using namespace std;
int main(){
	int D;
	cout << "Coloque el día en el que se encuentra para mostrar horario, recuerde que lunes es 1 y domingo es 7: ";
	cin >> D;
	switch (D){ 
		case 1:
			cout << "Hoy toca práctica de cálculo, química y física." << endl;
			break;
		case 2:
			cout << "Hoy toca álgebra lineal y cálculo." << endl;
			break;
		case 3:
			cout << "Hoy toca práctica de álgebra lineal, química y física." << endl;
			break;
		case 4:
			cout << "Hoy toca álgebra lineal y cálculo." << endl;
			break;
		case 5:
			cout << "Hoy toca laboratorio de física y química." << endl;
			break;
		case 6:
			cout << "Hoy toca introducción a la ciencia de la computación y tambien trabajar." << endl;
			break;
		case 7:
			cout << "Revisa si tienes tarea por hacer y alista la mochila, sino descansa todo el día :)." << endl;
			break;
		default:
			cout << "Revise su número correctamente." << endl;
		}
return 0;
}
