#include<iostream>
#include<string>
#include<cstring>
#include<string.h>
#include<stdlib.h>
using namespace std;

class Persona{
	private:
		string nombre; string direccion;string sexo;
		int nacim;
	public:
		Persona(string neim, string place, string sx, int date) : nacim(date), nombre(neim), direccion(place), sexo(sx){}
		void M(){
			cout<<"Nombre: "<<nombre<<endl;
			cout<<"Lugar de Nacimiento: "<<direccion<<endl;
			cout<<"Sexo: "<<sexo<<endl;
			cout<<"Fecha de nacimiento: "<<nacim<<endl;
		}
		friend string saca(Persona X){
			return X.nombre;
		}
		~Persona(){}
};

class Estudiante: public Persona{
	private:
		double promedio;
		string u;
	public:
		Estudiante(string neim, string place, string sx, int date, double prom, string uni) : Persona(neim, place,sx,date), promedio(prom), u(uni){}
		void Mo(){
			cout<<"Universidad: "<<u<<endl;
			cout<<"Promedio: "<<promedio<<endl;
		}
		~Estudiante(){}
};

class Empleado: public Persona{
	private: 
		double salario;
	public:
		Empleado(string neim, string place, string sx, int date, double sal) : Persona(neim, place,sx,date), salario(sal){}
		void Mos(){
			cout<<"Salario: "<<salario<<endl;
		}
		~Empleado(){}
};

//empleado_estudiante
class Es_Em: public Estudiante, public Empleado{
	public: 
		Es_Em(string neim, string place, string sx, int date, double prom, string uni, double sal) : Estudiante(neim, place,sx,date,prom,uni), Empleado(neim, place,sx,date,sal){} 
		~Es_Em(){}
};


int main(){
	
	Persona a("Velez Beatriz","Ica", "F", 19961121);a.M();
	Persona b("Juarez Mia", "Rio", "no precisa", 19900221);b.M();
	Estudiante c("Perez Jorge", "Piedra", "no precisa", 19990516, 18.25, "UNI");c.Mo();
	Estudiante d("Lovren Iker", "Mexico", "M", 20031003, 5.6,"UNALM");d.Mo();
	Empleado e("Parra Diego", "Ica", "Trans", 19651225, 100.50);e.Mos();
	Es_Em f("Valdez Cris", "Juan", "M", 20000101,19.99,"SM", 950.20);f.Mos();
	
	
	string A[5]; 
	A[0] = saca(a);
	A[1] = saca(b);
	A[2] = saca(c);
	A[3] = saca(d);
	A[4] = saca(e);
	//A[5] = saca(f);
	
	char t;
	
	for ( int i = 0; i < 5; i++ ){
        for ( int j = i + 1; j < 5; j++ ){
            if((strcoll(A[i].c_str(), A[j].c_str())>0){
                strcpy ( t, A[i].c_str() );
                strcpy ( A[i].c_str(), A[j].c_str() );
                strcpy ( A[j].c_str(), t);
            }
        }
    }
 
    cout << "Mostrando nombres ordenados";
    for ( int i = 0; i < 5; i++ ){
        cout << A[i] << "\n"<< endl;
    }
	
	
	
	
	return 0;
}

