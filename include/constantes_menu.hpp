#ifndef CONSTANTES_MENU_HPP
#define CONSTANTES_MENU_HPP

#include <eventos.hpp>
#include <string>
#include <map>

// OPCIONES PARA MENSAJE DE AYUDA
const size_t MENSAJE_AYUDA_INICIAL = 0;
const size_t MENSAJE_AYUDA_INVENTARIO = 1;
const size_t MENSAJE_AYUDA_DESTINO = 2;
const size_t MENSAJE_AYUDA_ERROR = 3;
const size_t MENSAJE_ERROR_ITEM = 4;
const size_t MENSAJE_ERROR_EVENTOS = 5;
const size_t MENSAJE_ERROR_AYUDA = 6;
const size_t MENSAJE_ERROR_INVALIDO = 7;
const size_t MENSAJE_ERROR_ARCHIVO = 9;
const size_t MENSAJE_ERROR_ARCHIVO_PREDEFINIDO = 10;


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

static std::map <std::string,size_t> OPCIONES_MENU{
    { OPCION_DESTINO, 1 },
    { OPCION_INVENTARIO, 2 },
    { OPCION_AYUDA, 3 },
    { OPCION_SALIR, 4 }
};
static std::map <std::string,size_t> OPCIONES_MENU_INVENTARIO{
    { OPCION_INVENTARIO_ALTA, 1 },
    { OPCION_INVENTARIO_BAJA, 2 },
    { OPCION_INVENTARIO_CONSULTA, 3 },
    { OPCION_AYUDA, 4 },
    { OPCION_SALIR, 5 }    
};
static std::map <std::string,size_t> OPCIONES_MENU_DESTINO{
    { OPCION_DESTINO_AGREGAR, 1 },
    { OPCION_DESTINO_DEFINIR, 2 },
    { OPCION_DESTINO_MOSTRAR, 3 },
    { OPCION_AYUDA, 4 },
    { OPCION_SALIR, 5 }
};
static std::map <size_t,std::string> MENSAJE_FORZADO{
    { CONSULTA_CARGA, "¿Desea cargar inventario desde savefile?[S/N]: " },
    { CONSULTA_GUARDADO, "¿Desea guardar inventario en savefile?[S/N]: " },
    { CONSULTA_SOBREESCRITURA, "¿Desea sobreescribir archivo de entrada?[S/N]: " }
};
static std::map <std::string,std::string> MENSAJES_SUCESOS{
    { PERFIL_USUARIO_DESORIENTADO, "Aumento de factores ambientales" },
    { PERFIL_USUARIO_PRECAVIDO, "Aumento en la cantidad de enemigos" },
    { PERFIL_USUARIO_ASUSTADO, "Evento Pyramid Head adelantado" },
    { PERFIL_USUARIO_INDETERMINADO, "Comportamiento aún no definido" }
};

#endif