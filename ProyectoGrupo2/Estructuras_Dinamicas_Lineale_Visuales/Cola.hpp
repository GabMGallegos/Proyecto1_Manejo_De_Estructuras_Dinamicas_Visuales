#ifndef COLA_HPP
#define COLA_HPP

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Cola
{
private:
    struct Nodo
    {
        T dato;
        Nodo* siguiente;

        Nodo(T val) : dato(val), siguiente(nullptr) {}
    };

    Nodo* nodoFrente;
    Nodo* nodoFinal;
    int tamano;

    void imprimirRecursivo(Nodo* nodo) const
    {
        if (!nodo) return;
        cout << nodo->dato << " -> ";
        imprimirRecursivo(nodo->siguiente);
    }

public:
    Cola() : nodoFrente(nullptr), nodoFinal(nullptr), tamano(0) {}

    ~Cola()
    {
        while (!estaVacia())
        {
            desencolar();
        }
    }

    void encolar(T valor)
    {
        Nodo* nuevoNodo = new Nodo(valor);
        if (estaVacia())
        {
            nodoFrente = nodoFinal = nuevoNodo;
        }
        else
        {
            nodoFinal->siguiente = nuevoNodo;
            nodoFinal = nuevoNodo;
        }
        tamano++;
    }

    void desencolar()
    {
        if (estaVacia())
        {
            throw underflow_error("La cola está vacía");
        }
        Nodo* temp = nodoFrente;
        nodoFrente = nodoFrente->siguiente;
        delete temp;
        tamano--;

        if (!nodoFrente) nodoFinal = nullptr;
    }

    T frente() const
    {
        if (estaVacia())
        {
            throw underflow_error("La cola está vacía");
        }
        return nodoFrente->dato;
    }

    bool estaVacia() const
    {
        return nodoFrente == nullptr;
    }

    int obtenerTamano() const
    {
        return tamano;
    }

    void imprimirRecursivo() const
    {
        imprimirRecursivo(nodoFrente);
        cout << "NULL\n";
    }

    friend ostream& operator<<(ostream& os, const Cola<T>& cola)
    {
        Nodo* actual = cola.nodoFrente;
        while (actual)
        {
            os << "[" << actual->dato << "] -> ";
            actual = actual->siguiente;
        }
        os << "NULL";
        return os;
    }
};

#endif
