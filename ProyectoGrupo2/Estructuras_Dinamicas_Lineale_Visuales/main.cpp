#include <iostream>
#include <locale.h>
#include <limits>

#include "Listas_Visual.hpp"
#include "Listas_Controlador.hpp"

#include "Controller_Pila.h"

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "Cola.hpp"
#include "visual.hpp"

using namespace std;

void visulizarListas()
{
    ControladorLista* ctrl = new ControladorLista();
    VistaLista vista(ctrl);
    vista.run();
    delete ctrl;
}

void visualizarPilas()
{
    ControllerPila controller;
    controller.run();
}

void visualizarColas()
{
    srand(static_cast<unsigned>(time(nullptr)));

    cout << "Botón E: Enqueue" << endl;
    cout << "Botón D: Dequeue" << endl;


    RenderWindow ventana(VideoMode(300, 600), "Cola Vertical - FIFO");

    Cola<int> cola;
    VistaCola<int> vista;

    while (ventana.isOpen()) {
        Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == Event::Closed)
                ventana.close();


            if (evento.type == Event::KeyPressed) {
                if (evento.key.code == Keyboard::E) {
                    int valor = rand() % 100;
                    cola.encolar(valor);
                    cout << "Cola actual: " << cola << endl;
                    vista.encolarVisual(valor);
                } else if (evento.key.code == Keyboard::D) {
                    if (!cola.estaVacia()) {
                        cout << "Se va a eliminar el valor: " << cola.frente() << endl;
                        cola.desencolar();
                        vista.desencolarVisual();
                    }
                }
            }
        }

        ventana.clear(Color::White);
        vista.dibujar(ventana);
        ventana.display();
    }
}


int main(){
    setlocale(0,"");
    int opc;

    do{
        cout << "\n\n\t\tMenú: Estructuras Dinámicas Lineales Interactivas" << endl;
        cout << "1. Listas" << endl;
        cout << "2. Pilas" << endl;
        cout << "3. Colas" << endl;
        cout << "4. Salir" << endl;
        cout << "Elija una opción: ";

        cin >> opc;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(opc){
            case 1:
            {
                visulizarListas();
                break;
            }
            case 2:
            {
                visualizarPilas();
                break;
            }
            case 3:
            {
                visualizarColas();
                break;
            }
            case 4:
            {
                exit(0);
            }
            default:
            {
                cout << "Inserter opciones válidas!!";
                break;
            }
        }
        system("pause");
        system("cls");

    }while(!(opc==4));
}
