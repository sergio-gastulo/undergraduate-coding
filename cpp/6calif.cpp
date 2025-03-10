#include<iostream>
#include<string.h>
using namespace std;

class Overview{
	private: 
		string marca; string disenyador; 
	public: 
		Overview(string m, string d) : marca(m), disenyador(d){}
		~Overview(){}
};

class Body{
	private:
		string clase; string estilo; string disenyo;
	public:	
		Body(string c, string e, string d): clase(c), estilo(e), disenyo(d){}
		~Body(){}
};

class Power{
	private:
		double hp, cilindrada, litros;
		string transmision;
	public:
		Power(double h, double c, double l, string t) : hp(h), cilindrada(c), litros(l), transmision(t){}
		~Power(){}
};

class Dimension{
	private:
		double largo, alto, ancho;
	public:
		Dimension(double l, double a, double an) : largo(l), alto(a), ancho(an){}
};

class Auto: public Overview, public Body, public Power, public Dimension {
	private: 
		string name; //nombre acunyado al carro 
		long int ID; //DNI para carros
	public:
		Auto(string m, string d, string c, string e, string nyo, double h, double cili, double l,string t, double _l, double _a, double _an, string neim, long int dni) : Overview(m,d), Body(c,e,nyo), Power(h, cili, l,t), Dimension(_l, _a, _an), name(neim), ID(dni){}
		~Auto(){}
};

class Expe: public Auto{
	private:
		int comodidad, interaccion;
		//del 1 al 10, que tan comodo e interactivo es el auto con el usuario 
	public:
		 Expe(string m, string d, string c, string e, string nyo, double h, double cili, double l,string t, double _l, double _a, double _an, string neim, long int dni, int _como, int _inte) : Auto(m,d,c,e,nyo,h,cili,l,t,_l,_a,_an,neim,dni){
		 	comodidad=_como; interaccion=_inte;
		 }
};

class Veloci: public Auto{
	private:
		long double maxspeed, maxceleridad;
	public:
		Veloci(string m, string d, string c, string e, string nyo, double h, double cili, double l,string t, double _l, double _a, double _an, string neim, long int dni, int v, int a) : Auto(m,d,c,e,nyo,h,cili,l,t,_l,_a,_an,neim,dni), maxspeed(v), maxceleridad(a){}
};

class Cantidad : public Auto{
	private:
		long double sold; //unidades vendidas a lo largo de la historia
	public:
		Cantidad(string m, string d, string c, string e, string nyo, double h, double cili, double l,string t, double _l, double _a, double _an, string neim, long int dni, long double _s) : Auto(m,d,c,e,nyo,h,cili,l,t,_l,_a,_an,neim,dni), sold(_s){}
};

int main(){
	
	return 0;
}


