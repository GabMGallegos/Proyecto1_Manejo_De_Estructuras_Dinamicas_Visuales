#include "UI_Pila.h"
#include <iostream>
#include <sstream>

using namespace std;

UIPila::UIPila(sf::RenderWindow* win) : ventana(win) {}

void UIPila::cargarRecursos() {
    if (!texturaBloque.loadFromFile("imagen/bloque.png")) {
        std::cerr << "Error cargando bloque.png\n";
    }
    if (!texturaCanasta.loadFromFile("imagen/contenedor2.png")) {
        std::cerr << "Error cargando contenedor.png\n";
    }
    if (!fuente.loadFromFile("fuente/arial/ARIAL.ttf")) {
        std::cerr << "Error al cargar la fuente\n";
    }

    spriteCanasta.setTexture(texturaCanasta);
    sf::Vector2u tam = texturaCanasta.getSize();
    spriteCanasta.setOrigin(0, tam.y);

    spriteCanasta.setScale(0.2f, 0.2f);
    spriteCanasta.setPosition(300, 580);
}

void UIPila::dibujarCanasta() {
    ventana->draw(spriteCanasta);
}

void UIPila::dibujarPila(const string* nombres, int cantidad) {

    if (fuente.getInfo().family.empty()) {
        cerr << "Fuente no cargada, no se puede dibujar texto.\n";
        return;
    }

    float scale = 0.2f;
    float spacing = 160.0f;

    if (cantidad > 4) {
        scale = 0.8f / cantidad;
        spacing = 480.0f / cantidad;
    }

    for (int i = 0; i < cantidad; ++i) {
        sf::Sprite bloque;
        bloque.setTexture(texturaBloque);
        bloque.setScale(scale, scale);
        float posY = 480 - i * spacing;
        bloque.setPosition(320, posY);
        ventana->draw(bloque);

        sf::Text texto;
        texto.setFont(fuente);
        texto.setString(nombres[i]);
        texto.setCharacterSize(18 * scale * 5);
        texto.setFillColor(sf::Color::Black);
        texto.setPosition(400, posY + 40 * scale);
        ventana->draw(texto);

        float nuevaAltura = 0.2f + (cantidad - 1) * 0.05f;
        spriteCanasta.setScale(0.2f, nuevaAltura);
        ventana->draw(spriteCanasta);
    }
}

void UIPila::animarPush(int cantidad, const string& nombre) {

    sf::Sprite bloqueAnimado;
    bloqueAnimado.setTexture(texturaBloque);
    bloqueAnimado.setScale(0.2f, 0.2f);

    sf::Text texto;
    texto.setFont(fuente);
    texto.setString(nombre);
    texto.setCharacterSize(18);
    texto.setFillColor(sf::Color::Black);

    float x = 320;
    float y = -60;

    float destinoY = 480 - (cantidad - 1) * 20;
    bloqueAnimado.setPosition(x, y);
    texto.setPosition(400, y + 40);

    sf::Clock reloj;
    while (y < destinoY) {
        sf::Time dt = reloj.restart();
        y += 200 * dt.asSeconds();
        if (y > destinoY) y = destinoY;

        bloqueAnimado.setPosition(x, y);
        texto.setPosition(400, y + 40);

        ventana->clear(sf::Color::White);
        dibujarCanasta();

        string nombres[100];
        int cantidad;
        ventana->draw(bloqueAnimado);
        ventana->draw(texto);
        ventana->display();
    }
}

void UIPila::animarPop(int alturaBloque, const string& nombre) {

    if (alturaBloque == 0) return;

    sf::Sprite bloqueAnimado;
    bloqueAnimado.setTexture(texturaBloque);
    bloqueAnimado.setScale(0.2f, 0.2f);

    sf::Text texto;
    texto.setFont(fuente);
    texto.setString(nombre);
    texto.setCharacterSize(18);
    texto.setFillColor(sf::Color::Black);

    float x = 320;
    float y = 480 - (alturaBloque - 1) * 60;

    bloqueAnimado.setPosition(x, y);
    texto.setPosition(400, y + 40);

    sf::Clock reloj;
    while (y > -60) {
        sf::Time dt = reloj.restart();
        y -= 200 * dt.asSeconds();
        if (y < -60) y = -60;

        bloqueAnimado.setPosition(x, y);
        texto.setPosition(400, y + 40);

        ventana->clear(sf::Color::White);
        dibujarCanasta();

        ventana->draw(bloqueAnimado);
        ventana->draw(texto);
        ventana->display();
    }
}
