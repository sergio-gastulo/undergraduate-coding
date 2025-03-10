#include<iostream>
#include<math.h>
using namespace std;
void Crear(int arr[50]){
	for(int i=0;i<50;i++){
		cout<<"Ingrese su dato numero " <<i+1<<": ";
		cin>>arr[i];
	}
}
void Print(int arr[50]){
	for(int i=0;i<50;i++){
		cout<<arr[i]<<" ";
	}cout<<endl;
}
float Media(int arr[50]){
	float S=0;
	for(int i=0;i<50;i++){
		S+=arr[i];
	}S=S/50;
	cout<<"Media = "<<S<<endl;
	return S;
}
void Mediana(int F[], int x[], int dim){
	dim=dim/2;int i=0;
	while(F[i]<dim){i++;}
	cout<<"Mediana = "<<x[i]<<endl;
}
void Moda(int f[], int x[], int dim){
	int max=0,t;
	for(int i=0;i<100;i++){if(f[i]>max){max=f[i];t=i;}}
	cout<<"Moda = "<<x[t]<<endl;
}
float Varianza(float M, int f[], int x[]){
	float v=0;
	for(int i=0;i<100;i++){
		v+=f[i]*(x[i]-M)*(x[i]-M);
	}v=v/50;
	cout<<"Varianza = "<< v<<endl;
	return v;
}
void Desv(float M){cout<<"Desviacion estandar: "<<sqrt(M)<<endl;}	

int main(){
	int datos[50]; Crear(datos);Print(datos);
	int x[100];int f[100];int F[100]; 	
	for(int i=0;i<100;i++){x[i]=i+1;}
	for(int i=0;i<100;i++){f[i]=0;}
	for(int i=0;i<100;i++){for(int j=0;j<50;j++){if(datos[j]==x[i]){f[i]++;}}}
	for(int i=0;i<100;i++){if(i==0){F[i]=f[i];}F[i]=F[i-1]+f[i];}
	Mediana(F,x,50); 
	Moda(f,x,50); 
	Desv(Varianza(Media(datos),f,x));
	
	return 0;
}
