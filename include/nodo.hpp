#ifndef NODO_HPP
#define NODO_HPP

template<typename T>
class nodo {
private:
    T dato{};
    nodo<T>* siguiente;
public:
    // Constructor.
    nodo(T dato);

    // Pre: -
    // Post: Devuelve un puntero al nodo siguiente.
    nodo<T>* obtener_siguiente();

    // Pre: -
    // Post: Cambia el puntero al nodo siguiente.
    void cambiar_siguiente(nodo<T>* nuevo);

    // Pre: -
    // Post: Devuelve el dato almacenado.
    T obtener_dato();

    // Destructor.
    ~nodo();
};

template <typename T>
nodo<T>::nodo(T dato){
    this->dato = dato;
    this->siguiente = nullptr;
}

template <typename T>
nodo<T>* nodo<T>::obtener_siguiente(){
    return this->siguiente;
}

template <typename T>
void nodo<T>::cambiar_siguiente(nodo<T>* nuevo){
    this->siguiente = nuevo;
}

template <typename T>
T nodo<T>::obtener_dato(){
    return this->dato;
}

template <typename T>
nodo<T>::~nodo(){}

#endif