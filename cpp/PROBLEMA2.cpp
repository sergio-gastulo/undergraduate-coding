#include<iostream>
#include<math.h>

using namespace std;
const int NUM = 10;

// User entry to read vector data
void receiveArrayFromUser(int arr[NUM]){
	for(int i = 0; i < NUM; i++){
		cout << "Ingrese su dato numero "  << i + 1 << ": ";
		cin >> arr[i];
	}
}

// Printing vector data
void vectorPrint(int arr[NUM])
{
	cout << "Vector data:\n [ ";

	for (int i = 0; i < NUM; i++)
	{
		cout << arr[i] << ", ";
	}
	
	cout << " ]\n";
}


// Calculate mean 
float calculateMean(int arr[NUM]){
	float S = 0;

	for (int i = 0; i < NUM; i++)
	{
		S += arr[i];
	}
	
	S = S/NUM;

	cout << "Mean = " << S << endl;	
	return S;
}

// Calculate Median
// Not sure what it does tbh
void calculateMedian(int F[], int x[], int dim)
{
	dim=dim/2;int i=0;
	while(F[i]<dim){i++;}
	cout << "Median = " << x[i] << endl;
}

// Calculate mode
// Not sure why I need f and x tbh
void calculateMode(int f[], int x[], int dim){
	int max=0,t;
	for(int i=0;i<100;i++){if(f[i]>max){max=f[i];t=i;}}
	cout << "calculateMode = " << x[t] << endl;
}

// Calculate Variance
// Not sure how it works, yet
float calculateVariance(float M, int f[], int x[]){
	float v=0;
	for(int i=0;i<100;i++){
		v+=f[i]*(x[i]-M)*(x[i]-M);
	}v=v/NUM;
	cout << "calculateVariance = " <<  v << endl;
	return v;
}

void Desv(float M){cout << "Desviacion estandar: " << sqrt(M) << endl;}	

int main(){
	
	int datos[NUM]; 
	receiveArrayFromUser(datos);
	vectorPrint(datos);

	int x[100];int f[100];int F[100]; 	
	for(int i=0;i<100;i++){x[i]=i+1;}
	for(int i=0;i<100;i++){f[i]=0;}
	for(int i=0;i<100;i++){for(int j=0;j<NUM;j++){if(datos[j]==x[i]){f[i]++;}}}
	for(int i=0;i<100;i++){if(i==0){F[i]=f[i];}F[i]=F[i-1]+f[i];}
	calculateMedian(F,x,NUM); 
	calculateMode(f,x,NUM);
	Desv(calculateVariance(calculateMean(datos),f,x));
	
	return 0;
}
