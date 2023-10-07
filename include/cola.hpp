#ifndef COLA_HPP
#define COLA_HPP

#include <exception>
#include "nodo.hpp"
#include <iostream>
class cola_exception : public std::exception {
    // Excepcion especifica y exclusivamente para errores dentro de la cola.
    // Usar de la forma "throw cola_exception();" cuando una precondicion no se cumpla.

    // Ejemplo:
    //     if (condicion_de_error()){
    //         throw cola_exception();
    //     }
};

template<typename T>
class cola {
private:
    nodo<T>* primer_nodo = nullptr;
    nodo<T>* ultimo_nodo = nullptr;
    size_t cantidad_datos = 0;
public:
    // Constructor.
    cola();

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
    cola(const cola& l) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const cola& l) = delete;

    // Destructor.
    ~cola();
};


template <typename T>
cola<T>::cola(){}

template <typename T>
void cola<T>::alta(T dato){
    nodo<T>* nuevo = new nodo(dato);
    
    if ( this->vacio() ){
        this->primer_nodo = nuevo;
    }
    else{
        this->ultimo_nodo->cambiar_siguiente(nuevo);
    }

    this->ultimo_nodo = nuevo;
    this->cantidad_datos++;
}

template <typename T>
T cola<T>::baja(){
    if (this->vacio())
        throw cola_exception();

    // Guardamos nodo a eliminar y que pase el siguiente
    nodo<T>* eliminar = this->primer_nodo;
    this->primer_nodo = this->primer_nodo->obtener_siguiente();

    T resultado = eliminar->obtener_dato();
    delete eliminar;
    this->cantidad_datos--;

    return resultado;
}
template <typename T>
T cola<T>::primero(){
    if (this->vacio())
        throw cola_exception();
    return this->primer_nodo->obtener_dato();
}

template <typename T>
T cola<T>::ultimo(){
    if (this->vacio())
        throw cola_exception();

    return this->ultimo_nodo->obtener_dato();
}

template <typename T>
size_t cola<T>::tamanio(){
    return this->cantidad_datos;
}

template <typename T>
bool cola<T>::vacio(){
    return (this->cantidad_datos == 0);
}

template <typename T>
cola<T>::~cola(){
    while (!this->vacio())
        this->baja();
}

#endif