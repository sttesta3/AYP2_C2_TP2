#include "item.hpp"
#include <iostream>

item::item(std::string nombre, std::string tipo) {
    this->nombre = nombre;
    this->tipo = tipo;
}

void item::listar_informacion() {
    std::cout << "Nombre: " << this->nombre << " Tipo: " << this->tipo;
}

std::ostream& operator<<(std::ostream& os, const item& item) {
    os << item.nombre << ',' << item.tipo;
    return os;
}

bool item::operator==(const std::string& nombre_recibido) {
    return this->nombre == nombre_recibido;
}