#ifndef LISTAS_MODELO_HPP
#define LISTAS_MODELO_HPP

struct Nodo {
    int dato;
    Nodo* siguiente;

    Nodo(int v) : dato(v), siguiente(nullptr) {}
};

class Lista {
private:
    Nodo* cabeza;
    int tamanio;

    int contarRecursivo(Nodo* nodo) const {
        if (nodo == nullptr) return 0;
        return 1 + contarRecursivo(nodo->siguiente);
    }

public:
    Lista() : cabeza(nullptr), tamanio(0) {}

    ~Lista() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    void insertar(int valor, int pos) {
        if (pos < 0 || pos > tamanio) {
            return;
        }
        Nodo* nuevo = new Nodo(valor);
        if (pos == 0) {
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        } else {
            Nodo* ant = cabeza;
            for (int i = 0; i < pos - 1; ++i) {
                ant = ant->siguiente;
            }
            nuevo->siguiente = ant->siguiente;
            ant->siguiente = nuevo;
        }
        ++tamanio;
    }

    void eliminar(int pos) {
        if (pos < 0 || pos >= tamanio || cabeza == nullptr) {
            return;
        }
        if (pos == 0) {
            Nodo* aBorrar = cabeza;
            cabeza = cabeza->siguiente;
            delete aBorrar;
        } else {
            Nodo* ant = cabeza;
            for (int i = 0; i < pos - 1; ++i) {
                ant = ant->siguiente;
            }
            Nodo* aBorrar = ant->siguiente;
            ant->siguiente = aBorrar->siguiente;
            delete aBorrar;
        }
        --tamanio;
    }

    int getTamanio() const {
        return tamanio;
    }

    Nodo* getNodo(int indice) const {
        if (indice < 0 || indice >= tamanio) return nullptr;
        Nodo* actual = cabeza;
        for (int i = 0; i < indice; ++i) {
            actual = actual->siguiente;
        }
        return actual;
    }

    int contarConRecursion() const {
        return contarRecursivo(cabeza);
    }
};


#endif // LISTAS_MODELO_HPP
