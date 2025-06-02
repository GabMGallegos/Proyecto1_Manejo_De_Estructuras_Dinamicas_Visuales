#ifndef UI_PILA_H_INCLUDED
#define UI_PILA_H_INCLUDED

#include <SFML/Graphics.hpp>

using namespace std;

class UIPila {
private:
    sf::RenderWindow* ventana;
    sf::Texture texturaBloque;
    sf::Texture texturaCanasta;
    sf::Sprite spriteCanasta;
    sf::Font fuente;

public:
    UIPila(sf::RenderWindow* win);

    void cargarRecursos();
    void dibujarCanasta();
    void dibujarPila(const string* nombres, int cantidad);
    void animarPush(int alturaBloque, const string& nombre);
    void animarPop(int alturaBloque, const string& nombre);
    void obtenerNombres(string* nombres, int& cantidad) const;
};

#endif // UI_PILA_H_INCLUDED
