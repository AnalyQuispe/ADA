#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

enum TipoArco { ARCO_BOSQUE, ARCO_AVANCE, ARCO_RETORNO, ARCO_CRUZADO };

class Grafo {
private:
    int V; 
    vector<int>* adj; 

    vector<int> pre; 
    vector<int> post;
    vector<int> padre; 
    int tiempo; 

    // Función utilitaria DFS recursiva
    void dfsUtil(int v) {
        pre[v] = tiempo++;
        for (int w : adj[v]) {
            if (pre[w] == -1) { // No visitado
                padre[w] = v;
                dfsUtil(w);
            }
        }
        post[v] = tiempo++;
    }

public:
    Grafo(int V) {
        this->V = V;
        adj = new vector<int>[V];
        pre.assign(V, -1);
        post.assign(V, -1);
        padre.assign(V, -1);
        tiempo = 0;
    }

    // Añadir arco al grafo
    void agregarArco(int v, int w) {
        adj[v].push_back(w); 
        adj[w].push_back(v); 
    }

    // Construir el bosque DFS
    void GRAPHdfs() {
        for (int v = 0; v < V; v++) {
            if (pre[v] == -1) {
                padre[v] = v; // Marcamos la raíz del árbol DFS
                dfsUtil(v);
            }
        }
    }

    // Clasificar los arcos del grafo
    void clasificarArcos() {
        for (int v = 0; v < V; v++) {
            for (int w : adj[v]) {
                if (padre[w] == v) { // Arco del árbol
                    cout << "Arco (" << v << ", " << w << ") es un ARCO_BOSQUE." << endl;
                } else if (pre[v] < pre[w]) { // Avance o cruzado
                    if (post[w] == -1) {
                        cout << "Arco (" << v << ", " << w << ") es un ARCO_AVANCE." << endl;
                    } else {
                        cout << "Arco (" << v << ", " << w << ") es un ARCO_CRUZADO." << endl;
                    }
                } else { // Retorno o cruzado
                    if (post[w] == -1) {
                        cout << "Arco (" << v << ", " << w << ") es un ARCO_RETORNO." << endl;
                    } else {
                        cout << "Arco (" << v << ", " << w << ") es un ARCO_CRUZADO." << endl;
                    }
                }
            }
        }
    }
};

int main() {
    // Crea un grafo de ejemplo
    Grafo g(6);
    g.agregarArco(0, 1);
    g.agregarArco(0, 2);
    g.agregarArco(1, 3);
    g.agregarArco(1, 4);
    g.agregarArco(2, 4);
    g.agregarArco(3, 4);
    g.agregarArco(3, 5);

    // Construye el bosque DFS y clasifica los arcos
    g.GRAPHdfs();
    auto start = std::chrono::high_resolution_clock::now();
    g.clasificarArcos();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Tiempo de ejecución de clasificarArcos: " << duration.count() << " microsegundos." << std::endl;

    return 0;
}
