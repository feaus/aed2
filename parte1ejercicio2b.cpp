#include <vector>
using namespace std;

struct NodoB {
    vector<int> claves;
    vector<NodoB*> hijos;
    bool esHoja;
    int n;
};

bool buscarEnArbolB(NodoB* raiz, int claveBuscada) {
    int i = 0;
    // Buscar la primera clave mayor o igual a la buscada
    while (i < raiz->n && claveBuscada > raiz->claves[i]) {
        i++;
    }
    // Si la clave está en el nodo actual
    if (i < raiz->n && raiz->claves[i] == claveBuscada) {
        return true;
    }
    // Si es un nodo hoja, la clave no existe
    if (raiz->esHoja) {
        return false;
    }
    // Continuar la búsqueda en el subárbol hijo correspondiente
    return buscarEnArbolB(raiz->hijos[i], claveBuscada);
}
