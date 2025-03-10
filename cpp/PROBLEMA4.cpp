#include<iostream>
using namespace std;

void Full(int arr[5][3]){
	for(int i=0;i<5;i++){
		for(int j=0;j<3;j++){
			cout<<"Ingrese la nota del alumno "<<i+1<<" en el examen "<<j+1<<": ";
			cin>>arr[i][j];	
		}
	}
}
void Print(int arr[5][3]){
	for(int i=0;i<5;i++){
		for(int j=0;j<3;j++){
			cout<<arr[i][j]<<" ";
		}
		cout<<endl;
	}
}
void PE(int arr[5][3], int n){
	float PE=0;
	for(int i=0;i<5;i++){
		PE+=arr[i][n];
	}
	cout<<"Promedio del Examen "<<n+1<<" = "<<PE/5<<endl;
}
void PA(int arr[5][3], int n){
	float PA=0;
	for(int i=0;i<3;i++){
		PA+=arr[n][i];
	}
	cout<<"Promedio del Alumno "<<n+1<<" = "<<PA/3<<endl;
}

int main(){
	int NOTAS[5][3];Full(NOTAS);
	for(int i=0;i<3;i++){PE(NOTAS,i);}
	for(int i=0;i<5;i++){PA(NOTAS,i);}
	
	return 0;
}