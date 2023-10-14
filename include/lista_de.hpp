#ifndef LISTA_DE_HPP
#define LISTA_DE_HPP

#include <exception>
#include <cstdlib>
#include "nodo_de.hpp"

class Lista_exception : public std::exception {
    // Excepcion especifica y exclusivamente para errores dentro de la lista.
    // Usar de la forma "throw lista_exception();" cuando una precondicion no se cumpla.

    // Ejemplo:
    //     if (condicion_de_error()){
    //         throw lista_exception();
    //     }
};

template<typename T>
class Lista_de {
private:
    Nodo_de<T>* primer_nodo = nullptr;
    Nodo_de<T>* ultimo_nodo = nullptr;
    Nodo_de<T>* cursor = nullptr;
    // Nota: pueden no utilizar el índice. Estado inicial / no válido = -1.
    // La lista es 0-indexed.
    int indice_cursor = -1;
    size_t cantidad_datos = 0;

    // Pre: El índice debe ser menor que la cantidad de datos.
    // Post: Devuelve un puntero al nodo asociado al índice deseado.
    Nodo_de<T>* obtener_nodo(size_t indice);

public:
    // Constructor.
    Lista_de();

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
    Lista_de(const Lista_de& l) = delete;

    // El operador = (asignación) está deshabilitado.
    void operator=(const Lista_de& l) = delete;

    // Destructor.
    ~Lista_de();
};

template <typename T>
Nodo_de<T>* Lista_de<T>::obtener_nodo(size_t indice){
    if (indice >= this->tamanio())
        throw Lista_exception();
    
    // Si esta mas cerca del principio, iniciar desde ahi. Caso contrario desde el final
//    bool empezar_del_inicio = ( indice <= ( this->tamanio() / 2) );
    bool empezar_del_inicio = true;

    Nodo_de<T>* posicion = (empezar_del_inicio) ? this->primer_nodo : this->ultimo_nodo;
    for (size_t i = 0; i < indice; i++)
        posicion = posicion->obtener_siguiente();
    
    return posicion;
}

template <typename T>
Lista_de<T>::Lista_de(){}

template <typename T>
void Lista_de<T>::alta(T dato){
    size_t indice = (this->vacio()) ? 0 : this->tamanio();
    return this->alta(dato,indice);
}

template <typename T>
T Lista_de<T>::baja(){
    size_t indice = (this->vacio()) ? 0 : this->tamanio() - 1;
    return this->baja(indice);
}

template <typename T>
void Lista_de<T>::alta(T dato, size_t indice){
    if (indice > this->tamanio())
        throw Lista_exception();

    Nodo_de<T>* nuevo;
    if (this->vacio()){
        nuevo = new Nodo_de(dato);
        this->primer_nodo = nuevo;
        this->ultimo_nodo = nuevo;
    }
    else if (indice == 0) {
        nuevo = new Nodo_de(dato,this->primer_nodo->obtener_anterior(),this->primer_nodo);
        this->primer_nodo->cambiar_anterior(nuevo);
        this->primer_nodo = nuevo;
    }
    else if (indice == this->cantidad_datos){
        nuevo = new Nodo_de(dato,this->ultimo_nodo,this->ultimo_nodo->obtener_siguiente());
        this->ultimo_nodo->cambiar_siguiente(nuevo);
        this->ultimo_nodo = nuevo;
    }
    else {
        Nodo_de<T>* posicion = this->obtener_nodo(indice);
        nuevo = new Nodo_de(dato,posicion->obtener_anterior(),posicion);
        nuevo->obtener_siguiente()->cambiar_anterior(nuevo);
        nuevo->obtener_anterior()->cambiar_siguiente(nuevo);
    }

    if (this->vacio())
        this->reiniciar_cursor(true);

    this->cantidad_datos += 1;
}

template <typename T>
T Lista_de<T>::baja(size_t indice){
    if (indice > this->tamanio())
        throw Lista_exception();

    Nodo_de<T>* eliminar = this->obtener_nodo(indice);
    if (eliminar->obtener_siguiente())
        eliminar->obtener_siguiente()->cambiar_anterior(eliminar->obtener_anterior());
    else
        this->ultimo_nodo = eliminar->obtener_anterior();

    if (eliminar->obtener_anterior())
        eliminar->obtener_anterior()->cambiar_siguiente(eliminar->obtener_siguiente());
    else
        this->primer_nodo = eliminar->obtener_siguiente();

    if (this->cursor == eliminar){
        this->cursor = nullptr;
        this->indice_cursor = -1;
    }

    T resultado = eliminar->obtener_dato();
    delete eliminar;
    this->cantidad_datos--;
    return resultado;
}

template <typename T>
T Lista_de<T>::primero(){
    if (this->vacio())
        throw Lista_exception();
    return this->primer_nodo->obtener_dato();
}

template <typename T>
T Lista_de<T>::ultimo(){
    if (this->vacio())
        throw Lista_exception();
    return this->ultimo_nodo->obtener_dato();
}

template <typename T>
T Lista_de<T>::elemento(size_t indice){
    if (indice >= this->cantidad_datos)
        throw Lista_exception();

    return this->obtener_nodo(indice)->obtener_dato();
}

template <typename T>
bool Lista_de<T>::puede_avanzar(){
    return (this->cursor != nullptr);
}

template <typename T>
T Lista_de<T>::avanzar(bool siguiente){
    if (!this->puede_avanzar())
        throw Lista_exception();

    Nodo_de<T>* actual = cursor;
    if (siguiente)
        cursor = cursor->obtener_siguiente();
    else
        cursor = cursor->obtener_anterior();

    return actual->obtener_dato();
}

template <typename T>
void Lista_de<T>::reiniciar_cursor(bool principio){
    if (this->tamanio() == 0){
        this->cursor = nullptr;
        this->indice_cursor = -1;
    }
    else if (principio){
        this->indice_cursor = 0;
        this->cursor = this->primer_nodo;
    }
    else {
        this->indice_cursor = (int)this->cantidad_datos - 1;
        this->cursor = this->ultimo_nodo;
    }
}

template <typename T>
size_t Lista_de<T>::tamanio(){
    return this->cantidad_datos;
}

template <typename T>
bool Lista_de<T>::vacio(){
    return (this->cantidad_datos == 0);
}

template <typename T>
Lista_de<T>::~Lista_de(){
    while (this->tamanio() > 0)
        this->baja(this->cantidad_datos - 1);    
}

#endif