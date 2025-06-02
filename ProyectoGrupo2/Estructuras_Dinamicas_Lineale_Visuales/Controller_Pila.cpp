#include "Controller_Pila.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>
#include <atomic>
#include <iostream>
#include <mutex>

mutex mutexNombre;

using namespace std;

atomic<bool> comandoPush(false);
atomic<bool> comandoPop(false);
atomic<bool> comandoSalir(false);
string nombreParaPush;


ControllerPila::ControllerPila()
    : ventana(sf::VideoMode(800, 600), "Visualizador de Pila") {
    vista = new UIPila(&ventana);
    vista->cargarRecursos();
    srand(static_cast<unsigned>(time(nullptr)));
}

ControllerPila::~ControllerPila() {
    delete vista;
}

void ControllerPila::run() {

    thread hiloMenu(&ControllerPila::menuConsola, this);

    while (ventana.isOpen()) {
        manejarEventos();

        if (comandoPush) {
            string nombreSeguro;
            {
                lock_guard<mutex> lock(mutexNombre);
                nombreSeguro = nombreParaPush;
            }
            int altura = modelo.obtenerTamanio();
            modelo.push(nombreSeguro);
            vista->animarPush(altura, nombreSeguro);
            comandoPush = false;
        }

        if (comandoPop && !modelo.estaVacia()) {
            int altura = modelo.obtenerTamanio();
            std::string nombre = modelo.top();
            vista->animarPop(altura, nombre);
            modelo.pop();
            comandoPop = false;
        }

        if (comandoSalir) {
            ventana.close();
        }
        actualizarVista();
        ventana.display();
    }

    if (hiloMenu.joinable()) {
        hiloMenu.join();
    }

}

void ControllerPila::manejarEventos() {
    sf::Event event;
    while (ventana.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            ventana.close();
        }

    }
}

void ControllerPila::actualizarVista() {
    ventana.clear(sf::Color::White);
    vista->dibujarCanasta();
    string nombres[100];
    int cantidad;
    modelo.obtenerNombres(nombres, cantidad);
    vista->dibujarPila(nombres, cantidad);
}

void ControllerPila::menuConsola(){
    int opcion;
    string entrada;

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Push (insertar nombre)\n";
        cout << "2. Pop (eliminar tope)\n";
        cout << "3. Top (mostrar tope)\n";
        cout << "4. Mostrar pila\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                cout << "Ingrese un nombre: ";
                getline(cin, entrada);
                {
                    lock_guard<mutex> lock(mutexNombre);
                    nombreParaPush = entrada;
                }
                comandoPush = true;
                break;
            case 2:
                comandoPop = true;
                break;
            case 3:
                if (!modelo.estaVacia()) {
                    cout << "Tope: " << modelo.top() << "\n";
                } else {
                    cout << "La pila está vacía.\n";
                }
                break;
            case 4:
                modelo.mostrarRecursivo();
                break;
            case 5:
                comandoSalir = true;
                return;
            default:
                cout << "Opción inválida. Intenta de nuevo.\n";
        }
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}
