#ifndef NODO_DE_HPP
#define NODO_DE_HPP

template<typename T>
class nodo_de {
private:
    T dato{};
    nodo_de<T>* anterior;
    nodo_de<T>* siguiente;
public:
    // Constructor.
    nodo_de(T dato);

    // Constructor.
    nodo_de(T dato, nodo_de<T>* anterior, nodo_de<T>* siguiente);

    // Pre: -
    // Post: Devuelve un puntero al nodo anterior.
    nodo_de<T>* obtener_anterior();

    // Pre: -
    // Post: Devuelve un puntero al nodo siguiente.
    nodo_de<T>* obtener_siguiente();

    // Pre: -
    // Post: Cambia el puntero al nodo anterior.
    void cambiar_anterior(nodo_de<T>* nuevo);

    // Pre: -
    // Post: Cambia el puntero al nodo siguiente.
    void cambiar_siguiente(nodo_de<T>* nuevo);

    // Pre: -
    // Post: Devuelve el dato almacenado.
    T obtener_dato();

    // Destructor.
    ~nodo_de();
};

#endif