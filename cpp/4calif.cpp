#include<iostream>
using namespace std;

class Hora{
	private:
		int segundos, minutos, hora;
	public:
		Hora(int s, int m, int h): segundos(s), minutos(m), hora(h) {}
		void imprimir(Hora f){
			cout<<"Hora: "<<f.hora<<endl;
			cout<<"Minutos: "<<f.minutos<<endl;
			cout<<"Segundos: "<<f.segundos<<endl;
		}
		void adelantar(int, int, int, Hora); 
		void reiniciar(Hora g){
			g.segundos=0;
			g.minutos=0; 
			g.hora=0;
			imprimir(g);
		}
		~Hora(){}
};

void Hora::adelantar(int s, int m, int h, Hora p){
	p.segundos+=s;
	while(p.segundos>=60){
		p.segundos=p.segundos/60;
		m++;
	}
	p.minutos+=m;
	while(p.minutos>=60){
		p.minutos=(p.minutos-(p.minutos%60))/60;
		h++;
	}
	p.hora+=h;	
	cout<<"Hora adelantada: "<<endl;imprimir(p);
	}

int main(){
	//acceso
	int seg,min,hr;
	do{
		cout<<"Coloque segundos correctamente: ";cin>>seg;	
	}while(seg>=60);
	do{
		cout<<"Coloque minutos correctamente: ";cin>>min;	
	}while(min>=60);
	do{
		cout<<"Coloque hora correctamente: ";cin>>hr;	
	}while(hr>=24);
	Hora reloj(seg, min, hr); reloj.imprimir(reloj);
	
	cout <<"Hora de adelantar el reloj."<<endl;
	cout<<"Coloque segundos, cualquier natural: ";cin>>seg;
	cout<<"Coloque minutos, cualquier natural: ";cin>>min;
	cout<<"Coloque hora, cualquier natural: ";cin>>hr;
	reloj.adelantar(seg,min,hr,reloj);
	cout<<"Hora de reiniciar."<<endl;
	reloj.reiniciar(reloj);
	return 0;
}
