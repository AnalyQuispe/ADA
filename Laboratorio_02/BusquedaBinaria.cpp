// Esta función toma un número entero x
// y un vector creciente v[0..n-1]
// y devuelve un índice j en 0..n
// tal que v[j-1] < x <= v[j].
 
#include <iostream>
using namespace std;

int busquedaBinaria (int x, int n, int v[]) {
    if (v[n-1] < x) return n;
    if (x <= v[0]) return 0;
    // ahora v[0] < x <= v[n-1]
    int i = 0, d = n-1;
    while (i < d-1) {
        int m = (i + d - 1)/2;
        if (v[m] < x) i = m;
        else d = m;
    }
    return d;
}

(i + d - 1)/2

//linea para compilar c++ -std=c++11 BusquedaBinaria.cpp -o BusquedaBinaria