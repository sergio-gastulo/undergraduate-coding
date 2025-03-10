#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

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
void Ord(int *puntero, int dim){
	int x;
	for(int i=0;i<dim;i++){
		for(int j=0;j<dim-1;j++){
			if(*(puntero+j)>*(puntero+j+1)){
				x=*(puntero+j);
				*(puntero+j)=*(puntero+j+1);
				*(puntero+j+1)=x;
			}
		}
	}
}

int main(){
	
	int n;cout<<"Coloque la dimension de su primer vector: ";cin>>n; int *p = new int [n];
	Full(p,n);cout<<"El vector original 1 es: "<<endl;Pri(p,n);
	int m;cout<<"Coloque la dimension de su segundo vector: ";cin>>m; int *q = new int [m];
	Full(q,m);cout<<"El vector original 2 es: "<<endl;Pri(q,m);
	int *pq = new int [n+m];
	
	for(int i=0;i<n;i++){*(pq+i)=*(p+i);}
	for(int i=0;i<m;i++){*(pq+i+n)=*(q+i);}
	cout<<endl;
	cout<<"**"<<endl;
	cout<<endl;
	Ord(pq,n+m);
	cout<<"Combinacion de vector 1 y 2 en uno solo ordenadamente: "<<endl; Pri(pq,n+m);
	
	delete[] p; delete[] q; delete[] pq;
	return 0;
}
