#ifndef MODEL_PILA_H_INCLUDED
#define MODEL_PILA_H_INCLUDED

#include <iostream>
using namespace std;

struct NodoP {

    string nombre;
    NodoP* siguiente;

    NodoP(const string& nomb);
};

class Pila {
private:
    NodoP* tope;
    int tamanio;

public:
    Pila();
    ~Pila();

    void push(const string& nombre);
    void pop();
    string top() const;
    bool estaVacia() const;
    int obtenerTamanio() const;

    void mostrarRecursivo();
    void mostrarRecursivoAux(NodoP* NodoP);

    void obtenerNombres(string* nombres, int& cantidad) const;

    friend ostream& operator<<(ostream& os, const Pila& pila);
};

#endif // MODEL_PILA_H_INCLUDED
