#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

const std::string TIPO_PUZZLE = "PUZZLE";
const std::string TIPO_MUNICION = "MUNICION";
const std::string TIPO_CURATIVO = "CURATIVO";

class Item {
private:
    std::string nombre;
    std::string tipo;
    // Otros atributos relacionados al ítem.

public:
    // Constructor
    Item(std::string nombre, std::string tipo);

    // Constructor default:
    Item() = default;

    // Pre:
    // Post: Muestra por pantalla la información del ítem.
    void listar_informacion();

    // Pre:
    // Post: Carga la información al stream de salida, con el formato especificado.
    // NOTA: Utilizar este método (archivo << item) para cargar la información al archivo .csv.
    friend std::ostream& operator<<(std::ostream& os, const Item& item);

    // Pre:
    // Post: Devuelve true si el nombre coincide.
    bool operator==(const std::string& nombre_recibido);

    // Otros métodos relacionados al uso del ítem.
};

#endif