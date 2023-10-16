#include <iostream>

struct Nodo {
    int valor;
    Nodo* siguiente;
    Nodo(int val) : valor(val), siguiente(nullptr) {}
};

Nodo* intercalarListas(Nodo* lista1, Nodo* lista2) {
    Nodo nodoFicticio(0);
    Nodo* actual = &nodoFicticio;

    while (lista1 != nullptr && lista2 != nullptr) {
        if (lista1->valor <= lista2->valor) {
            actual->siguiente = lista1;
            lista1 = lista1->siguiente;
        } else {
            actual->siguiente = lista2;
            lista2 = lista2->siguiente;
        }
        actual = actual->siguiente;
    }

    if (lista1 != nullptr) {
        actual->siguiente = lista1;
    } else {
        actual->siguiente = lista2;
    }

    return nodoFicticio.siguiente;
}

// Función auxiliar para imprimir la lista
void imprimirLista(Nodo* cabeza) {
    while (cabeza != nullptr) {
        std::cout << cabeza->valor << " -> ";
        cabeza = cabeza->siguiente;
    }
    std::cout << "nullptr" << std::endl;
}

int main() {
    // Crear dos listas de prueba
    Nodo* lista1 = new Nodo(1);
    lista1->siguiente = new Nodo(3);
    lista1->siguiente->siguiente = new Nodo(5);

    Nodo* lista2 = new Nodo(2);
    lista2->siguiente = new Nodo(4);
    lista2->siguiente->siguiente = new Nodo(6);

    std::cout << "Lista 1: ";
    imprimirLista(lista1);
    std::cout << "Lista 2: ";
    imprimirLista(lista2);

    Nodo* listaIntercalada = intercalarListas(lista1, lista2);
    std::cout << "Lista Intercalada: ";
    imprimirLista(listaIntercalada);

    // Liberar memoria
    while (listaIntercalada != nullptr) {
        Nodo* temp = listaIntercalada;
        listaIntercalada = listaIntercalada->siguiente;
        delete temp;
    }

    return 0;
}
