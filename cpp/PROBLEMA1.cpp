#include<iostream>0
using namespace std;

void Costo(int tele, int DVD, int r){
	int tot = 1400*tele+220*DVD+35.20*r;
	cout<<"Subtotal: "<<tot<<"."<<endl;
	cout<<"Total con un impuesto del 8.25 por ciento: "<<1.0825*tot<<" ."<<endl;
}

int main(){
	
	int a,b,c;
	cout<<"Coloque la cantidad de televisores que desea llevar: ";cin>>a;
	cout<<"Coloque la cantidad de DVD's' que desea llevar: ";cin>>b;
	cout<<"Coloque la cantidad de controles remotos que desea llevar: ";cin>>c;
	Costo(a,b,c);
	
	return 0;
}