#include <iostream>
#include <vector>
 
using namespace std;
 
int main()
{
//vector de 20 elementos int iniclizados a 9
vector<int> A(20,9);
 
cout<<"El tamano anterior era: "<<A.size()<<endl;
//su tamaño es 20 pero lo cambiaremos a 5
A.resize(5);
//ahora su tamano es
cout<<"El nuevo tamano es: "<<A.size()<<endl;
 
return 0;
}