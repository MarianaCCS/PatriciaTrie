#include "node.h"

class PatriciaTrie{
    Node* root;
    public:
    PatriciaTrie(){
        root = new Node(); // por defecto ignoramos su valor
    }
    ~PatriciaTrie(){}

    bool find(std::string prefix);
    void insert(std::string prefix);
};

bool PatriciaTrie::find(std::string prefix){ //recorremos todo el arbol
    int size = int(prefix.size());
    int ind_prefix = 0;  // para recorrer el prefijo
    Node* temp = root; // para recorrer cada nodo

    while (temp->children[int(prefix[ind_prefix])]){ // mientras se pueda recorrer
        temp = temp->children[int(prefix[ind_prefix])]; // se obtiene el temp
        for (auto x:temp->prefix){ // recorremos cada valor de temp
            if (x!=prefix[ind_prefix]) return false;
            ind_prefix++;
        } // se coincide en palabra
        if (ind_prefix==size && temp->endWord) return true; // se retorna true si se encuentra la palabra en el arbol
    }
    return false;
}

void PatriciaTrie::insert(std::string prefix){
    int ind_prefix = 0; // para recorrer prefix
    int size = int(prefix.size()); // para tamaño de prefix

    if (!root->children[int(prefix[ind_prefix])]){ // caso base
        Node* nuevo = new Node(); nuevo->prefix = prefix; nuevo->endWord = true;
        root->children[int(prefix[ind_prefix])] = nuevo;
        return; 
    } 

    Node* temp = root; //recorremos desde raiz
    while (temp->children[int(prefix[ind_prefix])]){// mientras que tenga un hijo asociado
        temp = temp->children[int(prefix[ind_prefix])]; // se recorre
        int temp_size = int(temp->prefix.size()); // tamaño del prefijo del nodo actual
        for (int ind=0; ind<temp_size; ind++){ // recorremos el valor que tiene el nodo
            char x = temp->prefix[ind];
            //if (ind_prefix!=size-1){ // si es distinto a size-1
                if (x==prefix[ind_prefix] && ind_prefix!=size) ind_prefix++; // si coinciden indice solo avanza
                else{ // caso contrario, debe crear un nuevo nodo
                    Node* nuevo = new Node();
                    nuevo->prefix = "";
                    for (int i = ind_prefix; i<size; i++) nuevo->prefix+=prefix[i]; //lo que se debe añadir
                    nuevo->endWord = true; 
                    temp->children[int(nuevo->prefix[0])] = nuevo;

                    // enviar lo que se encuentra despues del prefijo como otro hijo
                    if (ind!=temp_size-1){
                        Node* otro_hijo = new Node();
                        otro_hijo->prefix = ""; otro_hijo->endWord=true;
                        for (int i=ind; i<temp_size; i++) otro_hijo->prefix+=temp->prefix[i]; // añadimos valor para el nuevo hijo (lo que había en nodo)
                        temp->endWord = false; // temp deja de ser endWord(si lo era)
                        temp->children[int(otro_hijo->prefix[0])] = otro_hijo; // añadimos el hijo
                    }
                    return;
                }
           // }
            //else{  // si es igual a size-1 quiere decir que ya es subcadena de otro nodo
                
           // }
        }
    } // llega aqui si ya no tiene un hijo asociado
    Node* nuevo = new Node();
    nuevo->prefix = "";
    for (int i = ind_prefix; i<size; i++) nuevo->prefix+=prefix[i]; //lo que se debe añadir
    nuevo->endWord = true; 
    temp->children[int(nuevo->prefix[0])] = nuevo;
}
