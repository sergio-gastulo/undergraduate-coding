#include <iostream>
#include <vector>
 
using namespace std;
 
int main()
{
//vector de 10 elementos inicializados a 9
vector<int> A(5,9);
 
//insertamos el valor 2 en la tercera posición del array
A.insert(A.begin()+3,2);
 
//mostramos el nuevo vector con un 2 que se insertó antes
for(unsigned int i=0;i<A.size();i++)
cout<<A[i]<<"  ";
 
cout<<endl<<endl;
return 0;
}