#include<iostream>
using namespace std;
int main()
{
	int t;
	cout << "¿Ya ha resuelto el simulacro de la uni 2018-I, a conciencia? Presione 1 para sí y 0 para no. ";
	cin >> t;
	if (t==0)
	{
	cout << "Resuelva, por favor. Sea un muchacho(a) responsable :)" << endl;
	}
	else if (t==1)
	{
	float PROM;
	cout << "Coloque su nota vigesimal: ";
	cin >> PROM;
		if (PROM>11.075 && PROM<=11.285)
		{
		cout << "Felicitaciones, ingresaste a matemática pura." << endl;
		}
		else if (PROM>11.285 && PROM<=12.257)	
		{
		cout << "Felicitaciones, ingresaste a matemática pura y a química pura." << endl;
		}
		else if (PROM>12.257 && PROM<=12.463)	
		{
		cout << "Felicitaciones, ingresaste a matemática pura, química pura e introducción a la ciencia de la computación." << endl;
		}
		else if (PROM>12.463 && PROM<=12.583)	
		{
		cout << "Felicitaciones, ingresaste a matemática pura, química pura, introducción a la ciencia de la computación y física pura." << endl;
		}
		else if (PROM>12.583 && PROM<=20)
		{
		cout << "Ingresaste en todas las carreras de la Facultad de Ciencias, orgullosos de usted." << endl;
		}
		else if (PROM<=11.075 && PROM>=0)
		{
		cout << "Siga practicando y recuerde que la perseverancia da frutos." << endl;
		}
		else 
		{
		cout << "#ERROR#" << endl;
		}
	}
	else 
	{
	cout << "#ERROR#" << endl;
	}
return 0;
}

