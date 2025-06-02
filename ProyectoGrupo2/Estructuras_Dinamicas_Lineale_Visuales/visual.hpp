#ifndef VISTA_HPP
#define VISTA_HPP

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "mivector.hpp"

using namespace sf;
using namespace std;

template <typename T>
class VistaCola {
private:
    struct NodoVisual {
        RectangleShape rect;
        Text texto;
        float posY;

        NodoVisual(const Font& fuente, const T& valor, float y) {
            rect.setSize(Vector2f(80, 50));
            rect.setFillColor(Color(rand() % 256, rand() % 256, rand() % 256));
            rect.setOutlineColor(Color::Black);
            rect.setOutlineThickness(2);
            rect.setPosition(110, y);
            posY = y;

            stringstream ss;
            ss << valor;
            texto.setFont(fuente);
            texto.setString(ss.str());
            texto.setCharacterSize(18);
            texto.setFillColor(Color::Black);
            FloatRect bounds = texto.getLocalBounds();
            texto.setPosition(110 + (80 - bounds.width) / 2 - bounds.left,
                              y + (50 - bounds.height) / 2 - bounds.top);
        }

        void mover(float dy) {
            posY += dy;
            rect.move(0, dy);
            texto.move(0, dy);
        }
    };

    MiListaDoble<NodoVisual> nodos;
    Font fuente;
    float inicioY = 500;
    float espacio = -60;

public:
    VistaCola() {
        srand(static_cast<unsigned>(time(nullptr)));
        if (!fuente.loadFromFile("arial.ttf")) {
            throw "No se pudo cargar la fuente arial.ttf";
        }
    }

    void encolarVisual(const T& valor) {
        float y = inicioY + nodos.tamano() * espacio;
        nodos.agregarAlFinal(NodoVisual(fuente, valor, y));
    }

    void desencolarVisual() {
        if (nodos.tamano() > 0) {
            nodos.eliminarPrimero();
            for (int i = 0; i < nodos.tamano(); ++i) {
                float destinoY = inicioY + i * espacio;
                float dy = destinoY - nodos[i].posY;
                nodos[i].mover(dy);
            }
        }
    }

    void dibujar(RenderWindow& ventana) {
        for (int i = 0; i < nodos.tamano(); ++i) {
            ventana.draw(nodos[i].rect);
            ventana.draw(nodos[i].texto);
        }
    }

    void reiniciar() {
        nodos.limpiar();
    }
};

#endif
