#ifndef LISTA_DE_HPP
#define LISTA_DE_HPP

#include <exception>
#include <cstdlib>
#include "nodo_de.hpp"

class lista_exception : public std::exception {
    // Excepcion especifica y exclusivamente para errores dentro de la lista.
    // Usar de la forma "throw lista_exception();" cuando una precondicion no se cumpla.

    // Ejemplo:
    //     if (condicion_de_error()){
    //         throw lista_exception();
    //     }
};

template<typename T>
class lista_de {
private:
    nodo_de<T>* primer_nodo;
    nodo_de<T>* ultimo_nodo;
    nodo_de<T>* cursor;
    // Nota: pueden no utilizar el índice. Estado inicial / no válido = -1.
    // La lista es 0-indexed.
    int indice_cursor;
    size_t cantidad_datos;

    // Pre: El índice debe ser menor que la cantidad de datos.
    // Post: Devuelve un puntero al nodo asociado al índice deseado.
    nodo_de<T>* obtener_nodo(size_t indice);

public:
    // Constructor.
    lista_de();

    // Pre: -
    // Post: Agrega el dato al final de la lista.
    void alta(T dato);

    // Pre: La lista no puede estar vacía.
    // Post: Elimina el último dato.
    // NOTA: Considerar que se puede dar de baja el nodo cursor.
    T baja();

    // Pre: El índice debe ser menor o igual que la cantidad de datos.
    // Post: Agrega el dato antes del dato en la posición indicada.
    // Si el índice es igual a la cantidad de datos, simplemente agrega al final.
    void alta(T dato, size_t indice);

    // Pre: El índice debe ser menor que la cantidad de datos.
    // Post: Elimina el dato en la posición indicada.
    // Si el índice es igual a la cantidad de datos - 1, simplemente elimina el último dato.
    // NOTA: Considerar que se puede dar de baja el nodo cursor.
    T baja(size_t indice);

    // Pre: La lista no puede estar vacía.
    // Post: Devuelve el primer dato en la lista.
    T primero();

    // Pre: La lista no puede estar vacía.
    // Post: Devuelve el último dato en la lista.
    T ultimo();

    // Pre: El índice debe ser menor que la cantidad de datos.
    // Post: Devuelve el dato en la posición deseada.
    T elemento(size_t indice);

    // Pre: -
    // Post: Devuelve true si se puede avanzar (esto es, que el cursor no sea nullptr).
    bool puede_avanzar();

    // Pre: Se debe poder avanzar.
    // Post: Devuelve el dato del cursor actual y luego lo mueve una posición en la dirección deseada.
    T avanzar(bool siguiente);

    // Pre: -
    // Post: Reinicia el cursor al principio o al final, según lo indicado.
    // Si la lista está vacía, se reinicia el cursor al estado inicial
    // (esto es, cursor = nullptr e indice_cursor = -1).
    void reiniciar_cursor(bool principio);

    // Pre: -
    // Post: Devuelve la cantidad de datos de la lista.
    size_t tamanio();

    // Pre: -
    // Post: Devuelve true si la lista esta vacía (es decir, si no hay datos).
    bool vacio();

    // El constructor de copia está deshabilitado.
    lista_de(const lista_de& l) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const lista_de& l) = delete;

    // Destructor.
    ~lista_de();
};

template <typename T>
nodo_de<T>* lista_de<T>::obtener_nodo(size_t indice){
    if (indice >= this->cantidad_datos)
        throw lista_exception();
    
    // Si esta mas cerca del principio, iniciar desde ahi. Caso contrario desde el final
    if (indice <= this->cantidad_datos / 2){
        this->cursor = this->primer_nodo;
        for (int i = 0; i < indice; i++)
            this->cursor = this->cursor->obtener_siguiente();
    }
    else{
        this->cursor = this->ultimo_nodo;
        for (int i = this->cantidad_datos - 1; i > indice; i--)
            this->cursor = this->cursor->obtener_anterior();
    }
    return cursor;
}

template <typename T>
lista_de<T>::lista_de(){
    this->cantidad_datos = -1;
    this->primer_nodo = nullptr;
    this->ultimo_nodo = nullptr;

    this->cursor = nullptr;
    this->indice_cursor = 0;
}

template <typename T>
void lista_de<T>::alta(T dato){
    return this->alta(dato,this->cantidad_datos);
}

template <typename T>
T lista_de<T>::baja(){
    return this->baja(this->cantidad_datos - 1);
}

template <typename T>
void lista_de<T>::alta(T dato, size_t indice){
    if (indice > this->cantidad_datos)
        throw lista_exception();

    if (indice == this->cantidad_datos){     // Ultimo Nodo
        nodo_de<T>* nuevo = new nodo_de(dato,this->ultimo_nodo,this->ultimo_nodo->obtener_siguiente());
        this->ultimo_nodo->cambiar_siguiente(nuevo);
        this->ultimo_nodo = nuevo;
    }
    else {
        nodo_de<T>* posicion = this->obtener_nodo(indice);
        nodo_de<T>* nuevo = new nodo_de(dato,posicion->obtener_anterior(),posicion);
        nuevo->obtener_siguiente()->cambiar_anterior(nuevo);

        if (nuevo->obtener_anterior()) 
            nuevo->obtener_anterior()->cambiar_siguiente(nuevo);
        else
            this->primer_nodo = nuevo;
    }

    this->cantidad_datos++;
}

template <typename T>
T lista_de<T>::baja(size_t indice){
    if (indice >= this->cantidad_datos)
        throw lista_exception();

    nodo_de<T>* eliminar;
    if (indice == this->cantidad_datos - 1){
        eliminar = this->ultimo_nodo;
        this->ultimo_nodo = this->ultimo_nodo->obtener_anterior();
        this->ultimo_nodo->cambiar_siguiente(nullptr);
    }
    else{
        eliminar = this->obtener_nodo(indice);
        eliminar->obtener_siguiente()->cambiar_anterior(eliminar->obtener_anterior());
        if (eliminar->obtener_anterior())          
            eliminar->obtener_anterior()->cambiar_siguiente(eliminar->obtener_siguiente());
        else
            this->primer_nodo = eliminar->obtener_siguiente();
    }

    if (this->cursor == eliminar){
        this->cursor = this->primer_nodo;
        this->indice_cursor = 0;
    }

    T resultado = eliminar->obtener_dato();
    delete eliminar;
    this->cantidad_datos--;
    return resultado;
}

template <typename T>
T lista_de<T>::primero(){
    return this->primer_nodo->obtener_dato();
}

template <typename T>
T lista_de<T>::ultimo(){
    return this->ultimo_nodo->obtener_dato();
}

template <typename T>
T lista_de<T>::elemento(size_t indice){
    if (indice > this->cantidad_datos)
        throw lista_exception();

    return this->obtener_nodo(indice)->obtener_dato();
}

template <typename T>
bool lista_de<T>::puede_avanzar(){
    return (this->cursor);
}

template <typename T>
T lista_de<T>::avanzar(bool siguiente){
    if (!this->puede_avanzar())
        throw lista_exception();

    nodo_de<T>* actual = cursor;
    if (siguiente)
        cursor = cursor->obtener_siguiente();
    else
        cursor = cursor->obtener_anterior();

    return actual->obtener_dato();
}

template <typename T>
void lista_de<T>::reiniciar_cursor(bool principio){
    if (this->cantidad_datos == 0){
        this->indice_cursor = -1;
        cursor = nullptr;
    }
    else if (principio){
        this->indice_cursor = 0;
        cursor = this->primer_nodo;
    }
    else {
        this->indice_cursor = this->cantidad_datos - 1;
        cursor = this->ultimo_nodo;
    }
}

template <typename T>
size_t lista_de<T>::tamanio(){
    return this->cantidad_datos;
}

template <typename T>
bool lista_de<T>::vacio(){
    return (this->cantidad_datos == 0);
}

template <typename T>
lista_de<T>::~lista_de(){}

#endif