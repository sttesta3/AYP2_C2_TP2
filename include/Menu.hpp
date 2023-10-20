#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <string.h>
#include <map>
#include <math.h>

#include "constantes_menu.hpp"
#include "eventos.hpp"
#include "inventario.hpp"

static std::string ruta_entrada = "";
static std::string ruta_salida = "";

class Menu {
    private:
        Inventario inventario = Inventario();
        Eventos eventos = Eventos();
        std::string entrada_usuario = "";
        
//.........................................................................................
//............. FUNCIONES DE MANEJO DE DESTINO (TP 2)
//.........................................................................................

        // Pre: -
        // Post: Solicita y agrega evento
        void agregar_evento();
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
        void alta_inventario();
        // Pre:
        // Post: Solicita entrada y elimina primer aparicion en inventario
        void baja_inventario();
        // Pre:
        // Post: Imprime inventario
        void consulta_inventario();
        // Pre:
        // Post: Inventario -> carga archivo
        void cargar_archivo_inventario();
        // Pre:
        // Post: Inventario -> guarda archivo
        void guardar_archivo_inventario();

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
        // Post: Imprime mensaje de ayuda al usuario
        void mensaje_de_ayuda(size_t selector);
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
        // Pre: -
        // Post: Solicita forzado un archivo valido
        void solicitar_archivo_carga();
        // Pre: -
        // Post: Solicita forzado un archivo valido. Si no encuentra crea uno nuevo
        void solicitar_archivo_guardado();
        // Pre: 
        // Post: Valida ruta predefinida de carga 
        void validar_ruta_predefinida_carga();
        // Pre: 
        // Post: Valida ruta predefinida de guardado 
        void validar_ruta_predefinida_guardado();
        // Pre: indice = 0 (carga), 1 (guardado), 2 (sobre escribir)
        // Post: Consulta forzada de S/N
        void solicitar_forzado(size_t indice);
        // Pre: -
        // Post: Interaccion con usuario para solicitar evento
        void solicitar_evento();
        // Pre: -
        // Post: Interaccion con usuario para solicitar repeticiones evento (entre 0 y 20)
        void solicitar_repeticiones_evento();

//.........................................................................................
//............. FUNCIONES GENERALES DE STRING 
//.........................................................................................

        // Pre: 
        // Post: Devuelve numero en base 10 o -1 si no es valido
        size_t str_to_int(std::string string);
        // Pre: - 
        // Post: String len 
        size_t string_len(std::string string);

    public:
        Menu();
        ~Menu();

        // Pre:
        // Post: Corre el juego completo 
        void juego(void);

};

#endif // MENU_HPP
