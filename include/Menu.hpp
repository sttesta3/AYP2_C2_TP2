#ifndef MENU_H
#define MENU_H

#include <fstream>
#include <iostream>
#include <string.h>
#include <math.h>

#include "eventos.hpp"
#include "inventario.hpp"

// OPCIONES PARA MENSAJE DE AYUDA
const size_t MENSAJE_AYUDA_INICIAL = 0;
const size_t MENSAJE_AYUDA_INVENTARIO = 1;
const size_t MENSAJE_AYUDA_DESTINO = 2;
const size_t MENSAJE_AYUDA_ERROR = 3;
const size_t MENSAJE_ERROR_ITEM = 4;

// OPCIONES DE MENU
const std::string OPCION_AYUDA = "AYUDA";
const std::string OPCION_SALIR = "SALIR";

const std::string OPCION_DESTINO = "DESTINO";
const std::string OPCION_DESTINO_AGREGAR = "AGREGAR_EVENTO";
const std::string OPCION_DESTINO_DEFINIR = "DEFINIR_DESTINO";
const std::string OPCION_DESTINO_MOSTRAR = "MOSTRAR_SUCESO";

const std::string OPCION_INVENTARIO = "INVENTARIO";
const std::string OPCION_INVENTARIO_ALTA = "ALTA";
const std::string OPCION_INVENTARIO_BAJA = "BAJA";
const std::string OPCION_INVENTARIO_CONSULTA = "CONSULTA";

// OPCIONES FUNCION DE SOLICITAR FORZADO
const size_t CONSULTA_CARGA = 0;
const size_t CONSULTA_GUARDADO = 1;
const size_t CONSULTA_SOBREESCRITURA = 2;

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
        // Post: Interaccion con usuario para solicitar repeticiones evento (entre 0 y 20)
        void solicitar_repeticiones_evento();
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
        // Pre: 
        // Post: Carga en inventario. Utilizado para alta desde archvio
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
        // Pre: -
        // Post: Solicita entrada al usuario, utilizando el mensaje 
        void solicitar_entrada(std::string mensaje);
        // Pre: - 
        // Post: Devuelve nombre de item
        std::string solicitar_nombre_item();
        // Pre: - 
        // Post: Devuelve tipo de item
        std::string solicitar_tipo_item();
        // Pre: - 
        // Post: Consulta si desea cargar
        bool solicitar_carga(void);
        // Pre: - 
        // Post: Consulta si desea guardar
        bool solicitar_guardado(void);
        // Pre: indice = 0 (carga), 1 (guardado), 2 (sobre escribir)
        // Post: Consulta forzada de S/N
        void solicitar_forzado(size_t indice);
        // Pre:
        // Post: Imprime mensaje de ayuda al usuario
        void mensaje_de_ayuda(size_t selector);
        // Pre: 
        // Post: Pasa string a size_t. Devuelve -1 si no es valido
        size_t str_to_int(std::string string);
        // Pre:
        // Post: String len 
        size_t string_len(std::string string);
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
        // Post: Solicita forzado un archivo valido. Si el archivo de guardado no es encontrado, crea uno nuevo
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
