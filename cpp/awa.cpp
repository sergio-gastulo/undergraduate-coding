#include<iostream>
using namespace std;

float burbu(int arr[10], int N, int t);
float inser(int arr[10], int N, int t);
float read(int arr[10], int N);
float press(int arr[10], int N);
float sele(int arr[10], int n, int t);
float quick(int arr[10], int inf, int sup);

int main(){

	int sz, arr[10], t, inf, sup;
	cout<<"Coloque el tamaño del vector: ";cin>>sz;
	read(arr, sz);cout<<"Arreglo original\n"; press(arr, sz);
	burbu(arr, sz, t);cout<<"Método de la burbuja\n"; press(arr, sz);
	inser(arr, sz, t);cout<<"Método de insercción\n"; press(arr, sz);
	sele(arr, sz, t);cout<<"Método de selección\n"; press(arr, sz);
	quick(arr, 0, sz-1);cout<<"Método de quicksort\n"; press(arr, sz);
	
	return 0;}
	
float read(int arr[10], int N){
	for(int i=0;i<N;i++){cout<<"Ingrese el elemento "<<i+1<<": ";cin>>arr[i];}return 0;}

float press(int arr[10], int N){
	for(int i=0;i<N;i++){
		cout<<arr[i]<<" ";}cout<<endl;return 0;}
	
float burbu(int arr[10], int N, int t){
	for(int i=1;i<N;i++){
		for(int j=0;j<N-1;j++){
			if(arr[j]>arr[j+1]){
				t=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=t;}}}return 0;}

float inser(int arr[10], int N, int t){
	for(int i=1;i<N;i++){
		t=arr[i]; int j;
		j=i-1;
		while((arr[j]>t) && (j>=0)){
			arr[j+1]=arr[j];
			j--;}
		arr[j+1]=t;}return 0;}
		
float sele(int arr[10], int n, int t){
	for(int i=0;i<n;i++){
		t=i;
		for(int j=i+1;j<n;j++){
			if(arr[j]< arr[t]){
				t=j;}}}return 0;}

float quick(int arr[10], int inf, int sup){
	int mitad, x, izq, der;
	izq=inf; der=sup;
	mitad=arr[(izq+der)/2];
	do{
		while(arr[izq]<mitad && izq<sup){
			izq++;}
		while(arr[der]>mitad && der>inf){
			der--;}
		if(izq<=der){
			x=arr[izq];
			arr[izq]=arr[der];
			arr[der]=x;
			izq++;
			der--;}
	}while(izq<=der);
	if(inf<der){quick(arr, inf, der);}
	if(izq<sup){quick(arr, izq, sup);}
return 0;}

	
	
	
	
	
	
	
	
	
	
	
	
	

