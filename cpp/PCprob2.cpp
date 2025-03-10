#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

void inter(int *p, int *q){
	int x;
	x=*p;*p=*q;*q=x;
}
void Full(int *puntero,int dim){
	srand(time(NULL));
	for(int i=0;i<dim;i++){
		*(puntero+i)=1 + rand() % (1000);
	}
}
void Pri(int *puntero, int dim){
	for(int i=0;i<dim;i++){
		cout<<*(puntero+i)<<" ";
	}cout<<endl;
}


int main(){
	
	int n;cout<<"Coloque la dimension de su primer vector: ";cin>>n;int *a = new int [n]; 
	Full(a,n);cout<<"El vector original es: "<<endl;Pri(a,n);
	
	cout<<"El vector arreglado es: "<<endl;
	
	if(n%2==1){for(int i=0;i<n;i++){inter(&a[n/2-i],&a[n/2+i]);}}
	else{for(int i=0;i<n;i++){inter(&a[n/2-i-1],&a[n/2+i]);}}
	
	Pri(a,n);
	
	delete[] a;
	return 0;
}


