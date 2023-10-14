#ifndef MENU_H
#define MENU_H

#include <fstream>
#include <iostream>
#include <string.h>

#include "eventos.hpp"
#include "inventario.hpp"

class Menu {
    private:
        Inventario inventario;
        Eventos eventos;
        std::string entrada_usuario = "";

//.........................................................................................
//............. FUNCIONES DE MANEJO DE DESTINO (TP 2)
//.........................................................................................

        // Pre: -
        // Post: Solicita y agrega evento
        void agregar_evento();
        // Pre: -
        // Post: Interaccion con usuario para solicitar evento
        void solicitar_evento();
        // Pre: -
        // Post: Define el perfil del jugador
        void definir_destino();
        // Pre: -
        // Post: Muestra suceso que le ocurrira al jugador
        void mostrar_suceso();

//.........................................................................................
//............. FUNCIONES DE MANEJO DE INVENTARIO (TP 1)
//.........................................................................................

        // Pre:
        // Post: Solicita entrada y carga en inventario
        void alta();

        // Pre: Item 
        // Post: Carga en inventario 
        void alta(std::string nombre, std::string tipo);
        // Pre:
        // Post: Solicita entrada y elimina primer aparicion en inventario
        void baja();
        // Pre:
        // Post: Imprime inventario
        void consulta();

//.........................................................................................
//............. FUNCIONES DE MANEJO DE INTERACCION CON USUARIO
//.........................................................................................

        // Pre: -
        // Post: Menu de interaccion con el inventario
        void interaccion_inventario();

        // Pre: -
        // Post: Menu de interaccion con destino
        void interaccion_destino();

        // Pre: 
        // Post: Solicita entrada al usuario, utilizando el mensaje 
        void solicitar_entrada(std::string mensaje);

        // Pre:
        // Post: Devuelve nombre de item
        std::string solicitar_nombre_item();
        // Pre:
        // Post: Devuelve tipo de item
        std::string solicitar_tipo_item();

        // Pre:
        // Post: Consulta si desea cargar
        bool solicitar_carga(void);
        // Pre:
        // Post: Consulta si desea guardar
        bool solicitar_guardado(void);

        // Pre: indice = 0 (carga), 1 (guardado), 2 (sobre escribir)
        // Post: 
        void solicitar_forzado(size_t indice);

//.........................................................................................
//............. FUNCIONES DE MANEJO DE ARCHVIOS
//.........................................................................................

        // Pre:
        // Post: Separa linea en nombre y tipo. Devuelve true/false si linea es valida
        bool procesar_linea_archivo(std::string linea, std::string &nombre, std::string &tipo);
        // Pre: 
        // Post: Devuelve true/false segun si la linea es valida
        bool analisis_linea_archivo(size_t palabras, std::string linea, std::string tipo); 
        // Pre:
        // Post: Carga archivo en inventario del menu
        void cargar_archivo();
        // Pre:
        // Post: Guarda archivo de partida
        void guardar_archivo();

        // Pre: carga = true -> Archivo de carga, else archivo de guardado
        // Post: 
        void solicitar_archivo(bool carga);
        // Pre: bool. True = archivo entrada, False = archivo salida
        // Post: Validar archivo 
        void validar_ruta_predefinida(bool ruta);

    public:
        Menu();
        ~Menu();

        // Pre:
        // Post: Corre el juego completo 
        void juego(void);

};

#endif // MENU_H
