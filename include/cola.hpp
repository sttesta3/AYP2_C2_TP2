#ifndef COLA_HPP
#define COLA_HPP

#include <exception>
#include "nodo.hpp"
#include <iostream>
class Cola_exception : public std::exception {
    // Excepcion especifica y exclusivamente para errores dentro de la cola.
    // Usar de la forma "throw cola_exception();" cuando una precondicion no se cumpla.

    // Ejemplo:
    //     if (condicion_de_error()){
    //         throw cola_exception();
    //     }
};

template<typename T>
class Cola {
private:
    Nodo<T>* primer_nodo = nullptr;
    Nodo<T>* ultimo_nodo = nullptr;
    size_t cantidad_datos = 0;
public:
    // Constructor.
    Cola();

    // Pre: -
    // Post: Agrega el dato al final de la cola.
    void alta(T dato);

    // Pre: La cola no puede estar vacía.
    // Post: Elimina el último dato.
    T baja();

    // Pre: La cola no puede estar vacía.
    // Post: Devuelve el primer dato en la cola.
    T primero();

    // Pre: La cola no puede estar vacía.
    // Post: Devuelve el último dato en la cola.
    T ultimo();

    // Pre: -
    // Post: Devuelve la cantidad de datos de la cola.
    size_t tamanio();

    // Pre: -
    // Post: Devuelve true si la cola esta vacía (es decir, si no hay datos).
    bool vacio();

    // El constructor de copia está deshabilitado.
    Cola(const Cola& l) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const Cola& l) = delete;

    // Destructor.
    ~Cola();
};

template <typename T>
Cola<T>::Cola(){}

template <typename T>
void Cola<T>::alta(T dato){
    Nodo<T>* nuevo = new Nodo(dato);
    
    if ( this->vacio() )
        this->primer_nodo = nuevo;
    else
        this->ultimo_nodo->cambiar_siguiente(nuevo);

    this->ultimo_nodo = nuevo;
    this->cantidad_datos++;
}

template <typename T>
T Cola<T>::baja(){
    if (this->vacio())
        throw Cola_exception();

    // Guardamos nodo a eliminar y que pase el siguiente
    Nodo<T>* eliminar = this->primer_nodo;
    this->primer_nodo = this->primer_nodo->obtener_siguiente();

    T resultado = eliminar->obtener_dato();
    delete eliminar;
    this->cantidad_datos--;

    return resultado;
}
template <typename T>
T Cola<T>::primero(){
    if (this->vacio())
        throw Cola_exception();
    return this->primer_nodo->obtener_dato();
}

template <typename T>
T Cola<T>::ultimo(){
    if (this->vacio())
        throw Cola_exception();

    return this->ultimo_nodo->obtener_dato();
}

template <typename T>
size_t Cola<T>::tamanio(){
    return this->cantidad_datos;
}

template <typename T>
bool Cola<T>::vacio(){
    return (this->cantidad_datos == 0);
}

template <typename T>
Cola<T>::~Cola(){
    while (!this->vacio())
        this->baja();
}

#endif