#ifndef INVENTARIO_HPP
#define INVENTARIO_HPP

#include "lista_de.hpp"
#include "Item.hpp"
#include <iostream>
#include <fstream>

const size_t TAMANIO_MAXIMO = 15;
class Inventario {
    private:
        Lista_de <Item> inventario = Lista_de <Item> ();

    public:
        Inventario() = default;
        ~Inventario() = default;
        
        // Pre: -
        // Post: Da alta item en inventario
        bool alta(Item nuevo);
        // Pre: -
        // Post: Elimina la primer aparicion de item en inventario. 0 = OK, 1 = No encontrado, 2 = vacio 
        size_t baja(std::string baja);
        // Pre: -
        // Post: Imprime inventario 
        void consulta();
        // Pre: - 
        // Post: Devuelve tamanio del inventario
        size_t tamanio();
        // Pre: Archivo valido para la carga 
        // Post: Carga inventario desde archivo
        size_t cargar_archivo(std::string ruta_archivo);
        // Pre: Archivo valido para guardado
        // Post: Guarda inventario en archivo
        bool guardar_archivo(std::string ruta_archivo);
        // Pre:
        // Post: Separa linea en nombre y tipo. Devuelve true/false si linea es valida
        bool procesar_linea_archivo(std::string linea, std::string &nombre, std::string &tipo);
        // Pre: 
        // Post: Devuelve true/false segun si la linea es valida
        bool analisis_linea_archivo(size_t palabras, std::string linea, std::string tipo); 


};

#endif