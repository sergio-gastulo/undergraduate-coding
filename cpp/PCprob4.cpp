#include<iostream>
#include<stdlib.h>

using namespace std;

int main(){
	
	char *q; q = new char[5];
	q[0]='A'; q[1]='B'; q[2]='C'; q[3]='D'; q[4]='E'; 
	
	int **p;
	p = new int *[5];
	for(int i=0;i<5;i++){
		p[i] = new int [5]; 
	}
	
	for(int i=0;i<5;i++){
		for(int j=i+1;j<5;j++){
			cout<<"Ingrese la distancia de la ciudad "<<q[i]<<" a la ciudad "<<q[j]<<endl;
			cin>>p[i][j];
		}
	}
	
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			p[j][i]=p[i][j];
		}
		p[i][i]=0;
	}
	
	for(int i=0;i<6;i++){
		if(i==0){cout<<"Ciudad\Ciudad \t";}
		else{cout<<"Ciudad "<<q[i-1]<<"\t\t";}
	}
	cout<<endl;
	
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(j==0){cout<<"Ciudad "<<q[i]<<"\t";}
			cout<<p[i][j]<<"\t\t\t";
		}
		cout<<endl;
	}
	
	
	for(int i=0;i<5;i++){
		delete[] p[i];
	}
	delete[] q;
	return 0;
}

/*cuadro = new int*[5-1];
for(){
cuadro[i]=new int[5-i];
cuadro[ca][cb]=d_ab;
delete[]  tabla*/
