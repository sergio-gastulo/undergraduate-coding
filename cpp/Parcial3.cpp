#include<iostream>
#include<iomanip>
using namespace std;

struct Persona{
	char Nombre[50];
	double Altura;
	double Peso;
	char Sexo;
}Persona[10], *P = Persona;

void Ord(double* p, int dim){
	double x;
	for(int i=0;i<dim;i++){
		for(int j=0;j<dim-1;j++){
			if(*(p+j)>*(p+j+1)){
				x=*(p+j);
				*(p+j)=*(p+j+1);
				*(p+j+1)=x;
			}
		}
	}
}

void Media(double* p, int dim){
	double Sum=0;
	for(int i=0;i<dim;i++){
		Sum+=*(p+i);
	}
	cout<< "La media del IMC es: " << Sum/dim << endl;
}

void Mediana(double* p, int dim){
	if(dim%2==0){
		cout << "La mediana del IMC es: " << (*(p+dim/2)+*(p+dim/2 + 1))/2 << endl;
	}	
	else{
		cout << "La mediana del IMC es: " << *(p+dim/2 + 1) << endl;
	}
}


int main(){
	
	double *IMC = new double[10];
	double IMC_umbral;
	cout<<"\n\nColoque su IMC umbral: ";cin>>IMC_umbral;
	
	for(int i=0;i<10;i++){
		fflush(stdin);
		cout<<endl;
		cout<<"Nombre: ";cin.getline((P+i)->Nombre, 50, '\n');
		cout<<"Altura (en cm): ";cin>>(P+i)->Altura;
		while((P+i)->Altura<54.6){
			cout<<"Ingrese una altura mayor a la del hombre mas pequenyo del mundo: ";cin>>(P+i)->Altura;
		}
		cout<<"Peso: ";cin>>(P+i)->Peso;
		cout<<"Sexo, recuerde que solo puede elegir M (masculino) o F (femenino): ";cin>>(P+i)->Sexo;
		(P+i)->Sexo=toupper((P+i)->Sexo);
		while((P+i)->Sexo!='M' && (P+i)->Sexo != 'F'){
			cout<<"Por favor, elija su sexo correspondiente, no somos pro-LGTBI.";
			cin>>(P+i)->Sexo;
			(P+i)->Sexo=toupper((P+i)->Sexo);
		
		}
		*(IMC+i) = 10000 * (P+i)->Peso / ((P+i)->Altura * (P+i)->Altura);
		
		if(*(IMC+i)>=IMC_umbral){
			cout<<"El IMC de " << (P+i)->Nombre << " es " << *(IMC+i) << '\n';
		}
		else {
			cout << "Lo sentimos, pero el IMC de " <<  (P+i)->Nombre << " es menor al IMC umbral." << endl;
		}
	}
	
	cout<<"\n\n DATOS HOMBRES \n\n";
	
	cout << setw(102) << setfill('-') << '\n' << setfill(' ');
	
	cout<< "|" 
		<< setw(15) << "Altura (cm)"
		<< "|" 
		<< right << setw(10) << "Peso" 
		<< "|"
		<< right << setw(6) << "Sexo" 
		<< "|"
		<< right << setw(15) << "IMC"
		<< "|"
		<< right << setw(50) << "Nombre"
		<< "|"
		<<endl;
	
	cout << setw(102) << setfill('-') << '\n' << setfill(' ');
	
	for(int i=0;i<10;i++){
		if((P+i)->Sexo=='M'){
			cout << "|" 
			<< setw(15) << (P+i)->Altura 
			<< "|" 
			<< right << setw(10) << (P+i)->Peso 
			<< "|" 
			<< right << setw(6) << 'M' 
			<< "|" 
			<< right << setw(15);
			if(*(IMC+i)>=IMC_umbral) {cout << *(IMC+i) << "*";}
			else { cout << *(IMC+i);}
			cout << "|" 
			<< right << setw(50) << (P+i)->Nombre
			<< "|" 
			<<endl;	 
			cout << setw(102) << setfill('-') << '\n' << setfill(' ');
		}
	}
	
	cout<<"\n\n DATOS MUJERES \n\n";
	
	cout << setw(102) << setfill('-') << '\n' << setfill(' ');
	
	cout<< "|" 
		<< setw(15) << "Altura (cm)"
		<< "|" 
		<< right << setw(10) << "Peso" 
		<< "|"
		<< right << setw(6) << "Sexo" 
		<< "|"
		<< right << setw(15) << "IMC"
		<< "|"
		<< right << setw(50) << "Nombre"
		<< "|"
		<<endl;
	
	cout << setw(102) << setfill('-') << '\n' << setfill(' ');
	
	for(int i=0;i<10;i++){
		if((P+i)->Sexo=='M'){
			cout << "|" 
			<< setw(15) << (P+i)->Altura 
			<< "|" 
			<< right << setw(10) << (P+i)->Peso 
			<< "|" 
			<< right << setw(6) << 'M' 
			<< "|" 
			<< right << setw(15);
			if(*(IMC+i)>=IMC_umbral) {cout << *(IMC+i) << "*";}
			else { cout << *(IMC+i);}
			cout << "|" 
			<< right << setw(50) << (P+i)->Nombre
			<< "|" 
			<<endl;	 
			cout << setw(102) << setfill('-') << '\n' << setfill(' ');
		}
	}
	
	Ord(IMC, 10);
	Media(IMC, 10);
	Mediana(IMC, 10);
	
	delete[] IMC;
	delete[] P;
	
	return 0;
}
