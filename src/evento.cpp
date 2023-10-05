#include "evento.hpp"

evento::evento(std::string accion) {
    this->accion_ejecutada = accion;
}

bool evento::operator==(const std::string& accion) {
    return this->accion_ejecutada == accion;
}