#include "Model_Pila.h"
using namespace std;

NodoP::NodoP(const string& nomb) : nombre(nomb), siguiente(nullptr) {}

Pila::Pila() : tope(nullptr), tamanio(0) {}

    Pila::~Pila() {
        while (!estaVacia()) {
            pop();
        }
    }

    void Pila::push(const string& nombre) {
        if (nombre.empty()) {
            cout << "[Advertencia] No se permite insertar cadenas vacías.\n";
            return;
        }
        NodoP* nuevo = new NodoP(nombre);
        nuevo->siguiente = tope;
        tope = nuevo;
        tamanio++;
    }

    void Pila::pop() {
        if (estaVacia()) return;
        NodoP* temp = tope;
        tope = tope->siguiente;
        delete temp;
        tamanio--;
    }

    string Pila::top() const {
        if (estaVacia()) return "";
        return tope->nombre;
    }

    bool Pila::estaVacia() const {
        return tope == nullptr;
    }

    int Pila::obtenerTamanio() const {
        return tamanio;
    }

    void Pila::mostrarRecursivo() {
        mostrarRecursivoAux(tope);
        cout << endl;
    }

    void Pila::mostrarRecursivoAux(NodoP* NodoP) {
        if (!NodoP) return;
        std::cout << NodoP->nombre << " ";
        mostrarRecursivoAux(NodoP->siguiente);
    }

    void Pila::obtenerNombres(string* arreglo, int& cantidad) const {
        cantidad = 0;

        const int MAX = 100;
        string temp[MAX];

        NodoP* actual = tope;
        while (actual) {
            temp[cantidad++] = actual->nombre;
            actual = actual->siguiente;
        }

        for (int i = 0; i < cantidad; ++i) {
            arreglo[i] = temp[cantidad - i - 1];
        }
    }

    ostream& operator<<(ostream& os, const Pila& pila) {
        NodoP* actual = pila.tope;
        while (actual) {
            os << actual->nombre << " ";
            actual = actual->siguiente;
        }
        return os;
    }
