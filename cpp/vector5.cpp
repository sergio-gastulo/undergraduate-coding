#include <iostream>
#include <vector>
 
using namespace std;
 
int main()
{
//vector de 20 elementos int iniclizados a 9
vector<int> A(20,9);
 
//se accede al tercer elemento, en la posición 2 del vector
cout<<"El tercer elemento del vector es: "<<A[2]<<endl;
 
return 0;
}