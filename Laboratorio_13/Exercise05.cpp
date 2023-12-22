#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

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
            if (pre[w] == -1) { 
                padre[w] = v;
                dfsUtil(w);
            }
        }
        post[v] = tiempo++;
    }

public:
    Grafo(int V) : V(V), adj(new vector<int>[V]), tiempo(0) {
        pre.assign(V, -1);
        post.assign(V, -1);
        padre.assign(V, -1);
    }

    ~Grafo() {
        delete[] adj; 
    }

    // Añadir arco al grafo
    void agregarArco(int v, int w) {
        adj[v].push_back(w); 
        adj[w].push_back(v); 
    }

    // Construir el bosque DFS
    void GRAPHdfs() {
        for (int v = 0; v < V; ++v) {
            if (pre[v] == -1) {
                padre[v] = v; 
                dfsUtil(v);
            }
        }
    }

   
    vector<int> getPadres() {
        return padre;
    }
};

// Función para imprimir el ciclo a partir de un arco de retorno
void imprimirCiclo(const vector<int>& pa, int x, int y) {
    vector<int> ciclo;
    int actual = x;

    while (actual != -1) {
        ciclo.push_back(actual);
        if (actual == y) {
            
            for (int i = ciclo.size() - 1; i >= 0; --i) {
                cout << ciclo[i] << (i != 0 ? " -> " : "\n");
            }
            return;
        }
        actual = pa[actual];
    }

    // Si llegamos aquí, no hay ciclo, y no es un ancestro de x
    cout << "El arco (" << x << ", " << y << ") no es un arco de retorno." << endl;
}

int main() {
    
    Grafo g(6);
    g.agregarArco(0, 1);
    g.agregarArco(0, 2);
    g.agregarArco(1, 3);
    g.agregarArco(1, 4);
    g.agregarArco(2, 4);
    g.agregarArco(3, 4);
    g.agregarArco(3, 5);

    // Construye el bosque DFS
    g.GRAPHdfs();

    vector<int> pa = g.getPadres();

    imprimirCiclo(pa, 5, 1);

    return 0;
}
