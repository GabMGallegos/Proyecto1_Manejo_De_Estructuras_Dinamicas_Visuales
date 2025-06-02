#ifndef CONTROLLER_PILA_H_INCLUDED
#define CONTROLLER_PILA_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "Model_Pila.h"
#include "UI_Pila.h"

using namespace std;

class ControllerPila {
private:
    Pila modelo;
    sf::RenderWindow ventana;
    UIPila* vista;
    string inputNombre;

public:
    ControllerPila();
    ~ControllerPila();
    void run();
    void menu();

private:
    void menuConsola();
    void manejarEventos();
    void actualizarVista();
};

#endif // CONTROLLER_PILA_H_INCLUDED
