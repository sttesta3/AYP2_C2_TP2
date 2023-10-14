#include "evento.hpp"

Evento::Evento(std::string accion) {
    this->accion_ejecutada = accion;
}

bool Evento::operator==(const std::string& accion) {
    return this->accion_ejecutada == accion;
}