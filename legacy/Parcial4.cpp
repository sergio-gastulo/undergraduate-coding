#include<iostream>
using namespace std;
//Se realizara una clase sobre un museo
class Persona{
	protected:
		string nombre;
		long int dni;
	public:
		Persona(string name, long int dna): nombre(name), dni(dna) {}
		~Persona(){}
};
class Visitante : public Persona{
	protected:
		long int id; //id es el numero de ticket, es unico
	public:
		Visitante(string name, long int dna, long int id_): 
		Persona(name, dna), id(id_) {}
		~Visitante(){}
};
class Estudiante : public Visitante{
	private:
		long int codigo; //codigo UNI, algo por el estilo
	public:
		Estudiante(string name, long int dna, long int id_, long int code): 
		Visitante(name, dna, id_), codigo(code) {}
		~Estudiante(){}
};

class Empleado : public Persona{
	protected:
		long int ruc; //algo unico que identifica a cada empleado
		double salario;
	public:
		Empleado(string name, long int dna, long int ruc, double s): 
		Persona(name, dna), ruc(ruc), salario(s) {}
		void set_sal(Empleado E)	{	cin>>E.salario;	}
		friend double Sal(Empleado E){ 	return E.salario;	}
		void Calc_sal(int meses, int prima, Empleado E){
			cout<<"Su salario en " << meses << " meses sera de " << 
			Sal(E)*meses*+prima << " soles." << endl;
		}
		~Empleado(){}
	
};

class Gerente:  public Empleado{
	protected:
		string sede;
		int num_empleados; //la cantidad de empleados que administra
	public:
		Gerente(string name, long int dna, long int ruc,double s, string sed, int n): 
		Empleado(name, dna, ruc,s), sede(sed), num_empleados(n){}
		double Despedir(Empleado E){
			E.~Empleado();
		}
		~Gerente(){}
		double Promo(string o, long int dn, long int r, double t, string new_sede, int num){
			Gerente G(o,dn,r, t,new_sede, num);
		}
};

class Duenyo: public Gerente{
	private:
		string contrasenya;
	public:
		Duenyo(string name, long int dna, long int ruc, double s, string sed, int n, string c): 
		Gerente(name, dna,ruc, s, sed, n), contrasenya(c){}
		void Despedir(Gerente G){
			G.~Gerente();
		}
		~Duenyo(){}
};


int main() {return 0;}
