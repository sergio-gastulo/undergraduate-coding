#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std; 
int main(){int i, j, t, n;
	srand(time(NULL));do{cout<<"Coloque la dimensión de su matriz deseada: ";cin>>n;}while(n<1);
	double arr[n][n];
	for (i=0;i<n;i++){for(j=0;j<n;j++){
		arr[i][j]=10+rand()%(90);}}
		
	cout<<"Arreglo original: \n";
	for(i=0;i<n;i++){for(j=0;j<n;j++){
		cout<<arr[i][j]<<" ";}cout<<endl;}
		
	for (i=0;i<n;i++){for(j=0;j<n-1;j++){if(arr[i][j]>arr[i][j+1]){
		t=arr[i][j];
		arr[i][j]=arr[i][j+1];
		arr[i][j+1]=t;}}}

	for(j=0;j<n;j++){for (i=0;i<n;i++){if(arr[i][n-1]<arr[i+1][n-1]){
		t=arr[i][n-1];
		arr[i][n-1]=arr[i+1][n-1];
		arr[i+1][n-1]=t;}}}
		
	for(i=0;i<n;i++){
		t=arr[i][i];
		arr[i][i]=arr[i][n-1];
		arr[i][n-1]=t;}

	cout<<"Diagonal ordenada en forma decreciente: \n";
	for(i=0;i<n;i++){for(j=0;j<n;j++){
		cout<<arr[i][j]<<" ";}cout<<endl;}

return 0;}














