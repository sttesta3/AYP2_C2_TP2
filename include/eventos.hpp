#ifndef EVENTOS_HPP
#define EVENTOS_HPP

#include "cola.hpp"
#include "evento.hpp"

const std::string PERFIL_USUARIO_DESORIENTADO = "DESORIENTADO";
const std::string PERFIL_USUARIO_PRECAVIDO = "PRECAVIDO";
const std::string PERFIL_USUARIO_ASUSTADO = "ASUSTADO";
const std::string PERFIL_USUARIO_INDETERMINADO = "INDETERMINADO";

const size_t CANT_EVENTOS_MAXIMA = 20;

class Eventos {
    private:
        Cola <Evento> eventos = Cola <Evento>();
        std::string perfil = PERFIL_USUARIO_INDETERMINADO;

    public:
        Eventos() = default;
        ~Eventos() = default;
        
        // Pre: -
        // Post: Da alta item en inventario
        void acolar(Evento nuevo);
        // Pre: -
        // Post: Da alta item en inventario
        void acolar(Evento nuevo, size_t repeticiones);

        // Pre: -
        // Post: Elimina la primer aparicion de item en inventario 
        Evento descolar();

        // Pre: -
        // Post: Define y devuelve perfil de jugador
        std::string definir_destino();

        // Pre: -
        // Post: Devuelve perfil de jugador
        std::string mostrar_destino();

        // Pre: - 
        // Post: Devuelve tamanio del inventario
        size_t tamanio();
};

#endif