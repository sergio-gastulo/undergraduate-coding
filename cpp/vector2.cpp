#include <iostream>
#include <vector>
 
using namespace std;
 
int main(){
//vector de 20 elementos int inicializados a 9
    vector<int> A(20,9);
//vector B sin inicializar
    vector<int> B;
    cout<<B<<endl; 
//copiamos el contenido de A en B
B=A;

return 0;
}