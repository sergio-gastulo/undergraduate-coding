#include<iostream>

using namespace std;

class Lista{
	private:
	class Nodo{
		public:
			int dato;
			Nodo *sgte;	
	};
	public:
	void InsertaNodoInicio(Nodo** head_ref, int new_dato){
    	Nodo* new_Nodo = new Nodo();  
    	new_Nodo->dato = new_dato;  
  		new_Nodo->sgte = (*head_ref);  
  		(*head_ref) = new_Nodo;  
		}
		
	void InsertaFinal(Nodo** head_ref, int new_dato){
 	  	Nodo* new_Nodo = new Nodo(); 
		Nodo *ultimo = *head_ref;
  		new_Nodo->dato = new_dato;
	    new_Nodo->sgte = NULL;  
  		if (*head_ref == NULL){  
	        *head_ref = new_Nodo;  
    	    return;  
    	}  
		while (ultimo->sgte != NULL){
        	ultimo = ultimo->sgte;
		}  
			ultimo->sgte = new_Nodo;  
    	return;  
		}
	
	void InsertaSegundo(Nodo* prev_Nodo, int new_dato){  
    if (prev_Nodo == NULL){  
        cout<<"Error, no nulo.";  
        return;  
    }
	Nodo* new_Nodo = new Nodo();
	new_Nodo->dato = new_dato;  
  	new_Nodo->sgte = prev_Nodo->sgte;  
  	prev_Nodo->sgte = new_Nodo;  
	}  
	
	void InsertaAntepenult(Nodo *&reco, int x){
		Nodo* aux = new Nodo();
		aux->dato = x;
		while(reco->sgte->sgte != NULL){
			reco = reco->sgte;
		}
		reco->sgte = aux;
	}
	
	void BorrarPrimero(Nodo *&reco){	
		Nodo *aux;
		aux = reco;
		reco = reco->sgte;
		delete aux;
	}
	
	void BorrarSegundo(Nodo *&reco){
		Nodo *aux;
		aux = reco->sgte;
		reco = reco->sgte->sgte;
		delete aux;
	}
	
	void BorrarUltimo(Nodo *&reco){
		Nodo *aux;
		while (reco->sgte->sgte != NULL){
        	reco = reco->sgte;
		}
		aux = reco->sgte;
		delete aux;
	}
	
	void BorrarMaxInfo(Nodo *&reco){
		Nodo *aux; int max=0;
		while(reco != NULL){
			if(reco->dato > max){
				max = reco->dato;
			}
			reco = reco->sgte;
		}
		while(reco != NULL){
			aux = reco; 
			if(reco->dato = max){
				delete aux;
			}
			reco = reco->sgte;
		}
	}
	
};



int main(){
	return 0;
}
