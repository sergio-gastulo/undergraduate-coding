#include <iostream>
#include <vector>
 
using namespace std;
 
int main()
{
    //vector sin inicializar ni indicar tamaño
    vector<double> arreglo_1;
 
    //vector con tamaño 5 y componentes iniclizadas
    vector<double> arreglo_2(5,3.1415);
 
    //mostrar las componentes con un ciclo
    for(unsigned int i=0;i<arreglo_2.size();i++)
    { //con el mtodo .size() se obtiene el tamaño del vector
        cout<<arreglo_2[i]<<endl;
    }
    cout<<endl<<endl<<endl;
    return 0;
}