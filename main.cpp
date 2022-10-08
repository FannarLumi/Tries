//Autor: Mario Jáuregui Gómez
//Matricula: A00832049
#include <iostream>
#include <string>
#include <vector>
//Tamaño del alfabeto
#define alfabeto 26

using namespace std;
//Abecedario que se usa para imprimir el recorrido DFS
string abecedario = "abcdefghijklmnopqrstuvwxyz";

struct Trie{
    //Lista de apuntadores donde se guarda el arbol
    struct Trie *children[alfabeto];
    //Variable para señalar fin de la palabra
    bool wordEnd;
};

//Funcion para crear nodos del arbol.
struct Trie *getNode(void){
    //Crea un nodo con 26 hijos
    struct Trie *pnode = new Trie;
    pnode -> wordEnd = false;
    for (int i = 0; i < alfabeto;++i){
        pnode->children[i] = NULL;
    }
    return pnode;
}
void insert (struct Trie *root, string palabra){
    //Crea una copia del arbol
    struct Trie *p = root;
    int n=palabra.length();
    for (int i = 0;i<n;i++){
        //Se encuentra el indice en el abecedario
        int k = palabra[i] - 'a';
        //Si el apuntador en ese indice es nulo, lo hacemos que sea un trie con 26 hijos
        if(!p -> children[k]){
            p->children[k] =getNode();
        }
        //Pasamos al siguiente hijo
        p = p->children[k];
    }
    //Señalamos que ya se acabo la palabra
    p -> wordEnd = true;
}
bool search (struct Trie *root, string palabra){
    //Crea una copia del árbol
    struct Trie *p = root;
    int n=palabra.length();
    for (int i = 0;i<n;i++){
        //Encuentra el indice de la letra en el abecedario
        int k = palabra[i] - 'a';
        //Si no existe esa letra en los children, regresa falso
        if (p->children[k] == NULL){
            return false;
        }
        //Se pasa al siguiente child
        p = p->children[k];
    }
    //Checa si es el final de la palabra, y si no entonces no se encuentra dentro del arbol
    return (p->wordEnd);
}
void printTrie(struct Trie *root){
    //Crea una copia del root
    struct Trie *p = root;

    //Si ya acabamos la palabra o el root esta vacio, regresa de la funcion
    if(p->wordEnd || p == NULL){
        return;
    }
    //Recorre todo el alfabeto
    for(int i = 0; i < alfabeto; ++i){
        if (p->children[i] != NULL){
            //Si existe el child, entonces lo imprimimos usando el string del alfabeto y llamamos
            //Recursivamente a la función asi asegurandonos de que estamos llendo DFS
           cout << abecedario[i] << endl;
           printTrie(p->children[i]);
        }
    }
}

int main() {


    int N,M;
    string palabra;
    vector<string> buscar;
    struct Trie *arbol = getNode();
    //Recibir datos necesarios
    cout << "Inserte la cantidad de palabras que va a tener el trie" << endl;
    cin >> N;
    cout << "Inserte las palabras" << endl;
    for (int i = 0; i < N; ++i){
        //Guardamos la palabra en el árbol
        cin >> palabra;
        insert(arbol,palabra);
    }
    //Hacemos el recorrido
    printTrie(arbol);

    cout << "Inserte la cantidad de palabras que va a buscar en el trie" << endl;
    cin >> M;
    cout << "Inserte las palabras" << endl;
    for (int j = 0; j < M; ++j){
        //Guardamos las palabras a buscar en un vector
        cin >> palabra;
        buscar.push_back(palabra);
    }
    for (auto i : buscar){
        //Buscamos las palabras en el trie
        cout << search(arbol,i) << endl;
    }

    return 0;
}
