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
void Busq(int *puntero, int dim, int elemento){
	int inf=0, sup=dim-1;
    int half=(inf+sup)/2;
    while (inf<=sup){
        if ( *(puntero+half) < elemento){inf=half+1;} 
		else if (*(puntero+half)==elemento){
    		cout<<"Su elemento se encontro en la posicion ";
            cout<<half+1<<endl;
            break;
        }
        else{sup=half-1;}
		half=(inf+sup)/2;
    }
	if (inf>sup){cout<<"Su elemento no ha sido encontrado."<<endl;}
}

int main(){
	
	int n;cout<<"Coloque la dimension de su arreglo: ";cin>>n; int *p= new int [n]; Full(p,n);
	Ord(p,n);cout<<"El arreglo ordenado es: "<<endl;Pri(p,n);
	int find;cout<<"Elija que numero desea buscar: ";cin>>find;
	Busq(p,n,find);
	
	delete[] p;
	return 0;
}

