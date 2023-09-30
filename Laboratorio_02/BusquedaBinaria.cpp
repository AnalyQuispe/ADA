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
        int m = (i + d)/2;
        if (v[m] < x) i = m-1;
        else d = m;
    }
    return d;
}


int main() {
    int v[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    int x = 4;
    int n = 11;
    int j = busquedaBinaria(x, n, v);
    cout << j << endl;
    return 0;
}

//linea para compilar c++ -std=c++11 BusquedaBinaria.cpp -o BusquedaBinaria