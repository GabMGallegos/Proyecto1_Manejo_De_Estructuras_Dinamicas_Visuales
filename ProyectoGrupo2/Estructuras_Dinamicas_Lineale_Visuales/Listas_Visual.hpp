#ifndef LISTAS_VISUAL_HPP
#define LISTAS_VISUAL_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <limits>
#include <thread>
#include <mutex>
#include <atomic>

using namespace std;

#include "Listas_Controlador.hpp"

class VistaLista {
private:
    ControladorLista* controlador;

    sf::RenderWindow ventana;
    sf::Font fuente;

    const float anchoNodo   = 80.f;
    const float altoNodo    = 40.f;
    const float espacio     = 30.f;
    const float margenIzq   = 50.f;
    const float centroY     = 300.f;

    bool arrastrando;
    sf::Vector2i arrastrarOffset;

    std::thread consolaThread;
    std::atomic<bool> cerrarVentanaRequested;

    std::mutex mtx;
    bool peticionInsertar;
    bool peticionEliminar;
    int valorInsertar;
    int posicionInsertar;
    int posicionEliminar;

public:
    VistaLista(ControladorLista* ctrl)
        : controlador(ctrl),
          ventana(sf::VideoMode(1024, 600), "Visualizador de Lista Dinámica"),
          arrastrando(false),
          cerrarVentanaRequested(false),
          peticionInsertar(false),
          peticionEliminar(false),
          valorInsertar(0),
          posicionInsertar(0),
          posicionEliminar(0)
    {
        if (!fuente.loadFromFile("arial.ttf")) {
            cerr << "Error: no se pudo cargar la fuente \"arial.ttf\"\n";
        }
        ventana.setFramerateLimit(60);
        consolaThread = std::thread(&VistaLista::menuConsolaLoop, this);
    }

    ~VistaLista() {
        if (consolaThread.joinable()) {
            consolaThread.join();
        }
    }

    void run() {
        while (ventana.isOpen()) {
            procesarEventos();

            if (cerrarVentanaRequested.load()) {
                ventana.close();
            }

            procesarPeticiones();
            dibujar();
        }
    }

private:
    void menuConsolaLoop() {
        while (!cerrarVentanaRequested.load()) {
            cout << "\n---- Menú de Lista Dinámica ----\n";
            cout << "1) Insertar nodo\n";
            cout << "2) Eliminar nodo\n";
            cout << "3) Cerrar ventana de visualización\n";
            cout << "Opción: ";

            int opcion;
            cin >> opcion;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada inválida. Debes ingresar 1, 2 o 3.\n";
                continue;
            }

            if (opcion == 1) {
                int val, pos;
                cout << "Valor a insertar: ";
                cin >> val;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Entrada inválida para valor.\n";
                    continue;
                }
                cout << "Posición (0 a " << controlador->obtenerTamanio() << "): ";
                cin >> pos;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Entrada inválida para posición.\n";
                    continue;
                }
                {
                    lock_guard<mutex> lock(mtx);
                    peticionInsertar = true;
                    valorInsertar   = val;
                    posicionInsertar = pos;
                }
            }
            else if (opcion == 2) {
                int n = controlador->obtenerTamanio();
                if (n <= 0) {
                    cout << "La lista está vacía, no hay nada que eliminar.\n";
                    continue;
                }
                int pos;
                cout << "Posición a eliminar (0 a " << (n - 1) << "): ";
                cin >> pos;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Entrada inválida para posición.\n";
                    continue;
                }
                {
                    lock_guard<mutex> lock(mtx);
                    peticionEliminar = true;
                    posicionEliminar = pos;
                }
            }
            else if (opcion == 3) {
                cerrarVentanaRequested.store(true);
                break;
            }
            else {
                cout << "Opción inválida. Elige 1, 2 o 3.\n";
            }
        }
    }

    void procesarPeticiones() {
        lock_guard<mutex> lock(mtx);
        if (peticionInsertar) {
            controlador->insertarNodo(valorInsertar, posicionInsertar);
            cout << "Nodo con valor " << valorInsertar
                 << " insertado en posición " << posicionInsertar << ".\n";
            peticionInsertar = false;
        }
        if (peticionEliminar) {
            controlador->eliminarNodo(posicionEliminar);
            cout << "Nodo en posición " << posicionEliminar
                 << " eliminado.\n";
            peticionEliminar = false;
        }
    }

    void procesarEventos() {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
                cerrarVentanaRequested.store(true);
            }
            else if (evento.type == sf::Event::MouseButtonPressed) {
                if (evento.mouseButton.button == sf::Mouse::Left) {
                    arrastrando = true;
                    sf::Vector2i ratonLocal(evento.mouseButton.x, evento.mouseButton.y);
                    sf::Vector2i ratonGlobal = ventana.getPosition() + ratonLocal;
                    arrastrarOffset = ventana.getPosition() - ratonGlobal;
                }
            }
            else if (evento.type == sf::Event::MouseButtonReleased) {
                if (evento.mouseButton.button == sf::Mouse::Left) {
                    arrastrando = false;
                }
            }
            else if (evento.type == sf::Event::MouseMoved) {
                if (arrastrando) {
                    sf::Vector2i ratonLocal(evento.mouseMove.x, evento.mouseMove.y);
                    sf::Vector2i ratonGlobal = ventana.getPosition() + ratonLocal;
                    ventana.setPosition(ratonGlobal + arrastrarOffset);
                }
            }
        }
    }

    void dibujar() {
        if (!ventana.isOpen()) return;
        ventana.clear(sf::Color::White);
        int n = controlador->obtenerTamanio();
        float x = margenIzq;
        for (int i = 0; i < n; ++i) {
            Nodo* nodo = controlador->obtenerNodo(i);
            if (nodo == nullptr) {
                x += anchoNodo + espacio;
                continue;
            }
            sf::RectangleShape rect(sf::Vector2f(anchoNodo, altoNodo));
            rect.setFillColor(sf::Color(100, 200, 250));
            rect.setPosition(x, centroY - altoNodo / 2.f);
            ventana.draw(rect);

            sf::Text texto;
            texto.setFont(fuente);
            texto.setString(std::to_string(nodo->dato));
            texto.setCharacterSize(18);
            texto.setFillColor(sf::Color::Black);

            sf::FloatRect bbox = texto.getLocalBounds();
            float anchoTexto = bbox.width;
            float altoTexto  = bbox.height;
            float offsetX    = (anchoNodo - anchoTexto) / 2.f;
            float offsetY    = (altoNodo  - altoTexto ) / 2.f;
            texto.setPosition(
                x + offsetX - bbox.left,
                (centroY - altoNodo / 2.f) + offsetY - bbox.top
            );
            ventana.draw(texto);

            if (i + 1 < n) {
                float radio = 4.f;
                sf::CircleShape cir(radio);
                cir.setFillColor(sf::Color::Black);
                cir.setPosition(x + anchoNodo - radio, centroY - radio);
                ventana.draw(cir);

                sf::VertexArray flecha(sf::Lines, 6);
                flecha[0].position = sf::Vector2f(x + anchoNodo, centroY);
                flecha[1].position = sf::Vector2f(x + anchoNodo + espacio, centroY);
                flecha[2].position = sf::Vector2f(x + anchoNodo + espacio, centroY);
                flecha[3].position = sf::Vector2f(x + anchoNodo + espacio - 8.f, centroY - 4.f);
                flecha[4].position = sf::Vector2f(x + anchoNodo + espacio, centroY);
                flecha[5].position = sf::Vector2f(x + anchoNodo + espacio - 8.f, centroY + 4.f);

                for (std::size_t j = 0; j < flecha.getVertexCount(); ++j) {
                    flecha[j].color = sf::Color::Black;
                }
                ventana.draw(flecha);
            }
            x += anchoNodo + espacio;
        }
        ventana.display();
    }
};


#endif // LISTAS_VISUAL_HPP_INCLUDED
