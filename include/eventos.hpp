#ifndef EVENTOS_HPP
#define EVENTOS_HPP

#include "cola.hpp"
#include "evento.hpp"
#include <iostream>


class Eventos {
    private:
        cola <evento> eventos = cola <evento> ();

    public:
        Eventos() = default;
        ~Eventos() = default;
        
        // Pre: -
        // Post: Da alta item en inventario
        void Acolar(evento nuevo);

        // Pre: -
        // Post: Elimina la primer aparicion de item en inventario 
        evento Descolar();

        // Pre: -
        // Post: Imprime evento a ejecutar 
        void Mostrar();

        // Pre: - 
        // Post: Devuelve tamanio del inventario
        size_t tamanio();
};

#endif