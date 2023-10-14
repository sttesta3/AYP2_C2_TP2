#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include "lista_de.hpp"
#include "Item.hpp"
#include <iostream>

class Inventario {
    private:
        Lista_de <Item> inventario = Lista_de <Item> ();

    public:
        Inventario() = default;
        ~Inventario() = default;
        
        // Pre: -
        // Post: Da alta item en inventario
        void alta(Item nuevo);

        // Pre: -
        // Post: Elimina la primer aparicion de item en inventario 
        void baja(std::string baja);

        // Pre: -
        // Post: Elimina primer item de lista 
        Item baja();

        // Pre: -
        // Post: Imprime inventario 
        void consulta();

        // Pre: - 
        // Post: Devuelve tamanio del inventario
        size_t tamanio();
};

#endif