#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void BFS(vector<vector<int>>& grafo, int inicio, int nodos) {
    vector<bool> visitado(nodos, false);
    queue<int> cola;
    
    visitado[inicio] = true;
    cola.push(inicio);
    
    while (!cola.empty()) {
        int nodo = cola.front();
        cola.pop();
        cout << "Visitando estación: " << nodo << endl;
        
        for (int vecino : grafo[nodo]) {
            if (!visitado[vecino]) {
                visitado[vecino] = true;
                cola.push(vecino);
            }
        }
    }
}

int main() {
    // Definimos el número de estaciones (nodos)
    int numeroDeNodos = 6;

    vector<vector<int>> grafo(numeroDeNodos);

    // Estación 0 conectada a 1 y 2
    grafo[0].push_back(1);
    grafo[0].push_back(2);
    // Estación 1 conectada a 0 y 3
    grafo[1].push_back(0);
    grafo[1].push_back(3);
    // Estación 2 conectada a 0 y 4
    grafo[2].push_back(0);
    grafo[2].push_back(4);
    // Estación 3 conectada a 1 y 5
    grafo[3].push_back(1);
    grafo[3].push_back(5);
    // Estación 4 conectada a 2 y 5
    grafo[4].push_back(2);
    grafo[4].push_back(5);
    // Estación 5 conectada a 3 y 4
    grafo[5].push_back(3);
    grafo[5].push_back(4);

    // Ejecutamos el BFS desde la estación 0
    BFS(grafo, 0, numeroDeNodos);

    return 0;
}
