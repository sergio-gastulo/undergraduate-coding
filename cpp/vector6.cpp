#include <iostream>
#include <vector>
 
using namespace std;
 
int main()
{
//vector de 10 elementos sin inicializar
vector<int> A(10);
//inicializamos todos los elementos en este ciclo
for(int i=0;i<10;i++)
{
A[i]=i+1;
}
//se muetra la longitud antes del borrado
cout<<"la longitud total es: "<<A.size()<<endl;
 
//borramos los elemetos entre las posciones 3 a 6
A.erase(A.begin()+3,A.begin()+6);
 
//mostramos la nueva longitud
cout<<"La nueva longitud es: "<<A.size()<<endl;
 
//mostramos el nuevo orden de los elementos
for(int i=0;i<A.size();i++)
cout<<A[i]<<" ";
 
cout<<endl<<endl;
 
return 0;
}