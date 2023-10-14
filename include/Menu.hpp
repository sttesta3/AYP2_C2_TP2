#ifndef MENU_H
#define MENU_H

#include <fstream>
#include <iostream>
#include <string.h>

#include "inventario.hpp"

std::string ruta_entrada = "";
std::string ruta_salida = "";
const size_t TAMANIO_MAXIMO = 15;
const size_t CARGA = 0;
const size_t GUARDADO = 1;
const size_t SOBREESCRITURA = 2;

class Menu {
    private:
        Inventario inventario;
        std::string entrada_usuario = "";

        // Pre: 
        // Post: Imprime mensaje y solicita input, guardando el mismo en this->entrada_usuario
        void SolicitarEntradaUsuario(std::string mensaje);

        // Pre:
        // Post: Devuelve nombre de item
        std::string SolicitarNombreItem();
        // Pre:
        // Post: Devuelve tipo de item
        std::string SolicitarTipoItem();
        // METODOS DE INTERACCIÓN CON INVENTARIO

        bool ProcesarLinea(std::string linea, std::string &nombre, std::string &tipo);

        // Pre:
        // Post: Solicita entrada y carga en inventario
        void Alta();

        // Pre: Item 
        // Post: Carga en inventario 
        void Alta(std::string nombre, std::string tipo);
        // Pre:
        // Post: Solicita entrada y elimina primer aparicion en inventario
        void Baja();
        // Pre:
        // Post: Imprime inventario
        void Consulta();

        // METODOS DE MANEJO DE ARCHIVOS

        // Pre:
        // Post: Carga archivo en inventario del menu
        void CargarArchivo();
        // Pre:
        // Post: Guarda archivo de partida
        void GuardarArchivo();

        // Pre:
        // Post: Consulta si desea cargar
        bool SolicitarCarga(void);
        // Pre:
        // Post: Consulta si desea guardar
        bool SolicitarGuardado(void);

        // Pre: indice = 0 (carga), 1 (guardado), 2 (sobre escribir)
        // Post: 
        void SolicitarForzado(size_t indice);

        // Pre: carga = true -> Archivo de carga, else archivo de guardado
        // Post: 
        bool SolicitarArchivo(bool carga);
        // Pre: bool. True = archivo entrada, False = archivo salida
        // Post: Validar archivo 
        void ValidarArchivoPredefinido(bool entrada_salida);

    public:
        Menu();
        ~Menu();

        // Pre:
        // Post: Corre el juego completo 
        void Juego(void);

};

#endif // MENU_H
