#include <iostream>
#include <vector>
 
using namespace std;
 
int main()
{
//vector de 6 elementos inicializados a 9
vector<int> A(6,9);
 
//insertamos el valor -1 tres veces (3) desde la cuarta posición del array
A.insert(A.begin()+4,3,-1);
 
//mostramos el nuevo vector con un 2 que se insertó antes
for(unsigned int i=0;i<A.size();i++)
cout<<A[i]<<"  ";
 
cout<<endl<<endl;
return 0;
}