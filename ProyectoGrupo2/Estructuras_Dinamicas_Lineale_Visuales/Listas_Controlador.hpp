#ifndef LISTAS_CONTROLADOR_HPP
#define LISTAS_CONTROLADOR_HPP

#include "Listas_Modelo.hpp"

class ControladorLista {
private:
    Lista modelo;

public:
    ControladorLista() {}

    ~ControladorLista() {}

    void insertarNodo(int valor, int pos) {
        modelo.insertar(valor, pos);
    }

    void eliminarNodo(int pos) {
        modelo.eliminar(pos);
    }

    int obtenerTamanio() const {
        return modelo.getTamanio();
    }

    Nodo* obtenerNodo(int indice) const {
        return modelo.getNodo(indice);
    }

    int contarConRecursion() const {
        return modelo.contarConRecursion();
    }
};


#endif // LISTAS_CONTROLADOR_HPP_INCLUDED
