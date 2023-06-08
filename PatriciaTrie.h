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
    void print_rec(Node* nodo,int pos);
    void print(); // imprime con nivel al que pertenece la palabra
    void remove(std::string prefix);
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
        //std::cout<<"Base: "<<nuevo->prefix<<std::endl;
        return; 
    } 

    Node* temp = root; //recorremos desde raiz
    while (temp->children[int(prefix[ind_prefix])]){// mientras que tenga un hijo asociado
        temp = temp->children[int(prefix[ind_prefix])]; // se recorre
        int temp_size = int(temp->prefix.size()); // tamaño del prefijo del nodo actual
        for (int ind=0; ind<temp_size; ind++){ // recorremos el valor que tiene el nodo
            char x = temp->prefix[ind];
            //if (ind_prefix!=size-1){ // si es distinto a size-1
                if (x==prefix[ind_prefix] && ind_prefix!=size) {
                    ind_prefix++; // si coinciden indice solo avanza
                     
                    if (ind_prefix==size){ // se intenta insertar palabra similar con menos  longitud
                        Node* nuevo = new Node();  // creamos un nod basandonos en temp
                        nuevo->prefix = "";
                        int size_temp_actual = int(temp->prefix.size());
                        for (int nuevo_ind = ind+1; nuevo_ind<size_temp_actual; nuevo_ind++){ // recorremos lo que falta para añadir al nuevo hijo
                            nuevo->prefix+=temp->prefix[nuevo_ind];
                        }
                        for (int nuevo_ind = ind+1; nuevo_ind<size_temp_actual; nuevo_ind++){ // recorremos lo que falta para añadir al nuevo hijo
                            temp->prefix.pop_back();
                        }
                        temp->endWord = nuevo->endWord = true; 

                        // liberamos los hijos de nuevo
                        for (int i=0;i<256;i++) {
                            nuevo->children[i]=temp->children[i];
                            temp->children[i] = nullptr;
                        }

                        // cambiar valores de temp y nuevo
                        /*
                        std::string p = nuevo->prefix;
                        nuevo->prefix = temp->prefix;
                        temp->prefix = p;
                        */
                        temp->children[int(nuevo->prefix[0])] = nuevo;
                        //std::cout<<"Palabra : "<<temp->prefix<<" " <<nuevo->prefix<<std::endl;
                        return;
                    }
                }
               
                
                else{ // caso contrario, debe crear un nuevo nodo y cuidar dependencias del actual
                    Node* nuevo = new Node();
                    nuevo->prefix = "";
                    for (int i = ind_prefix; i<size; i++) nuevo->prefix+=prefix[i]; //lo que se debe añadir
                    nuevo->endWord = true; 
                    //std::cout<<"En else: "<<nuevo->prefix<<std::endl;

                    // enviar lo que se encuentra despues del prefijo como otro hijo
                    if (ind<temp_size-1){
                        Node* otro_hijo = new Node(); // nuevo nodo
                        otro_hijo->prefix = ""; otro_hijo->endWord=true;
                        for (int i=ind; i<temp_size; i++) otro_hijo->prefix+=temp->prefix[i]; // añadimos valor para el nuevo hijo (lo que había en nodo)
                        for (int i=ind; i<temp_size; i++){ // borramos lo de más
                            temp->prefix.pop_back();
                        }
                        temp->endWord = false; // temp deja de ser endWord(si lo era)
                        
                        std::cout<<"Otro hijo: "<<otro_hijo->prefix<<std::endl;
                        
                        // pasamos todas las dependencias al nuevo nodo
                        for (int i=0; i<256; i++) {
                            otro_hijo->children[i] = temp->children[i];
                            temp->children[i] = nullptr;
                        }
                       // temp = temp->children[int(otro_hijo->prefix[0])];
                        temp->children[int(otro_hijo->prefix[0])] = otro_hijo; // añadimos el hijo
                        temp->children[int(nuevo->prefix[0])] = nuevo;     

                    }
                
                    temp->children[int(nuevo->prefix[0])] = nuevo; 
                    return;
                }
        }
    } // llega aqui si ya no tiene un hijo asociado
    Node* nuevo = new Node();
    nuevo->prefix = "";
    for (int i = ind_prefix; i<size; i++) nuevo->prefix+=prefix[i]; //lo que se debe añadir
    nuevo->endWord = true; 
    temp->children[int(nuevo->prefix[0])] = nuevo;
    std::cout<<"Fuera del while: "<<nuevo->prefix<<"\tTemp: "<<temp->prefix<<std::endl;
}

void PatriciaTrie::print_rec(Node* nodo,int pos){
    for (int i = 0; i<256;i++) {
        if (nodo->children[i]) {
            std::cout<<nodo->children[i]->prefix<<","<<pos<<"\t";
            print_rec(nodo->children[i],pos+1);
            std::cout<<std::endl;
        }
    }
}

void PatriciaTrie::print(){
    print_rec(root,0);
}

void PatriciaTrie::remove(std::string prefix){
    if (!find(prefix)){ // primero se busca
        std::cout<<prefix<<" no se encuentra\n"; return;
    }
    /*
        Casos:
            1. Se encuentra la palabra, es hoja (no tiene hijos) - solo borramos el nodo
            2. Se encuentra la palabra, no es hoja (tiene hijos):
                borramos el nodo 
                    - solo tiene un hijo:
                        ese hijo sube (reemplazar)
                    - tiene varios hijos:
                        
    */      
    Node* temp = root; // vamos a recorrer

}