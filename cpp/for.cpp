#include<iostream>
#include<stdio.h>
using namespace std;
int main(){
	int u,s=0,f,d;
	cout << "Hola, aquí sabrás cuán fan de Drake eres." << endl;
	cout << "Numero\tCancion" << endl;
	cout << "1\tFake Love" << endl;
	cout << "2\tToo God" << endl;
	cout << "3\tOne dance" << endl;
	cout << "4\tGyalchester" << endl;
	cout << "5\tU with me" << endl;
	cout << "6\tLegend" << endl;
	cout << "7\tGod's Plan" << endl;
	cout << "8\tMia" << endl;
	cout << "9\tHotline Bling" << endl; 
	cout << "10\tHype" << endl;	
	cout << "Presione 1 para SI y cualquier otro NUMERO para NO" << endl; 
	int t[]= { 1,2,3,4,5,6,7,8,9,10 };
	for (u=0;u<10;u++){
	cout << "¿Es usted fan de la canción " << t[u] << "?" << endl;
	cin >> d; if (d==1){s=d+s;}
	}
	f=s*10;
	cout << "Usted es " << f << "%"" fan de Drake" << endl; 
return 0;
}


