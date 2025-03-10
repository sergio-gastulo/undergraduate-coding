#include <iostream>
#include <string.h>
using namespace std;

void cambiar(char cad[4]);

int main(){
    char palabra[4]="ABC";
    cambiar(palabra);
    cout<<palabra<<endl;
    return 0;
}
void cambiar(char cad[4]){
    cout<< cad << endl;
    strcpy(cad,"DEF");
}
