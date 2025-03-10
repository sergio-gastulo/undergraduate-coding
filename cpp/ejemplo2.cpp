#include <iostream>
using namespace std;
const int F=2;
const int C=2;
int main(){
    float Matriz[F][C];
    // ingreso de datos
    for (int row = 0; row < F; row++){
        for (int col = 0; col < C; col++){
            cout<<"A["<<row<<","<<col<<"] = ";
            cin>>Matriz[row][col];
        }
    }
    //visualizacion de las filas
    for (int row = 0; row < F; row++){
        cout<<"Fila "<<row<<" = [ ";
        for (int col = 0; col < C; col++){
            cout<< Matriz[row][col]<<" ";
        }
        cout<< "]"<<endl;
    }
    //visualizacion de las columnas
    for (int col = 0; col < C; col++){
        cout<<"Columna "<<col<<"="<< endl;
        for (int row = 0; row < F; row++){
            if (row == 0) {
                cout<<"["<<Matriz[row][col]<<endl;
            }
            if (row >0 && row < F-1) {
                cout<<" "<<Matriz[row][col]<<endl;
            }
            if (row==F-1){
                cout<<" "<<Matriz[row][col]<<"]"<<endl;
            }
        }
    }
    //visualizacion de la matriz
    cout<<" A="<<endl;
    cout<<"[ ";
    for (int row = 0; row < F; row++){
        if (row>0){
                cout<<"  ";
            }
        for (int col = 0; col < C; col++){
            cout<<Matriz[row][col]<<" ";
        }
        if (row==F-1){
            cout<<"]";
        }else{
            cout<<endl;
        }
    }
    return 0;
}

