#include <iostream>
using namespace std;
int main(){
    char name[80];
    cout << "Introduzca su nombre ";
    cin.getline(name, sizeof(name));
    cout << "Hola " << name << " ¿cómo está usted?" << endl;
    return 0;
}