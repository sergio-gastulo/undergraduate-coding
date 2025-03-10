#include<iostream>
using namespace std;

class rect { 
   
   private: 
      int l, h;
	  
   public:
   	  rect();
      rect(int largo=0, int altura=0) : l(largo), h(altura) {} 
      rect(const rect &p);
      
      void d(){
      	cout<<"Dimensiones: Base = "<<l<<"cm, Altura = "<<h<<endl;
	  }
      void p(){
      	cout<<"Perimetro = "<<2*h+2*l<<"cm."<<endl;
	  } 
      void A(){
      	cout<<"Area = "<<l*h<<"cm al cuadrado."<<endl;
	  }   
	  
	~rect(){}
};

rect::rect(const rect &p) : l(p.l), h(p.h) {} 

int main(){
	float a,b;
	cout<<"Coloque longitud: ";cin>>a;
	cout<<"Coloque altura: ";cin>>b;	
	cout<<"Rectangulo 1:"<<endl;
	rect r1(a,b); r1.d(); r1.A();r1.p();
	cout<<"Rectangulo 2 (copia)"<<endl;
	rect r2(r1); r2.d(); r2.A(); r2.p();
	return 0;
}
