#include<iostream>
using namespace std;

int scan(int inf, int sup, int x, int p, int t, int i, int u, int primos[1]);
int imprimir(int i, int primos[1], int t);
	
int main(){
	int inf, sup, x, p=0, t, i, u; 
	cout<<"coloque limite inferior: ";cin>>inf;cout<<"coloque limite superior: ";cin>>sup;
	int primos[sup-inf];
	scan(inf, sup, x, p, t, i, u, primos);
	imprimir(i, primos, t);
return 0;}

int scan(int inf, int sup, int x, int p, int t, int i, int u, int primos[1]){t=0;
	for(i=inf;i<=sup;i++){
		for(int u=1;u<=i;u++){
			x=i%u;
			if(x==0){p++;
				if(p==2 and u==i){t++;p=0;primos[t-1]=i;cout<<t<<" "<<primos[t-1]<<" ";}
				else if(u==i){p=0;}}}}cout<<t<<endl;return t;}	
			
int imprimir(int i, int primos[1], int t){
	cout<<t<<endl;
	for(i=0;i<t;i++){
		cout<<primos[i]<<" ";}
	cout<<endl;
return 0;}
