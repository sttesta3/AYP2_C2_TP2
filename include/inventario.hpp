#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include "lista_de.hpp"
#include "Item.hpp"
#include <iostream>


class Inventario {
    private:
        lista_de <item> inventario = lista_de <item> ();

    public:
        Inventario() = default;
        ~Inventario() = default;
        
        // Pre: -
        // Post: Da alta item en inventario
        void Alta(item nuevo);

        // Pre: -
        // Post: Elimina la primer aparicion de item en inventario 
        void Baja(std::string baja);

        // Pre: -
        // Post: Elimina primer item de lista 
        item Baja();

        // Pre: -
        // Post: Imprime inventario 
        void Consulta();

        // Pre: - 
        // Post: Devuelve tamanio del inventario
        size_t tamanio();
};

#endif