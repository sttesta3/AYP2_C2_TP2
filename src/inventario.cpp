#include "inventario.hpp"

void Inventario::Alta(item nuevo){
    this->inventario.alta(nuevo);
}

void Inventario::Baja(std::string baja){
    if (this->inventario.vacio())
        std::cout << "Inventario vacio" << std::endl;
    else{
        this->inventario.reiniciar_cursor(true);
        item posicion = this->inventario.avanzar(true);
        size_t i = 0;  

        while (!(posicion==baja) && this->inventario.puede_avanzar()){
            posicion = this->inventario.avanzar(true);
            i += 1;
        }

        if (posicion==baja)
            this->inventario.baja(i);
        else
            std::cout << "Item '" << baja << "' no encontrado" << std::endl;
    }
}

item Inventario::Baja(){
    return this->inventario.baja(0);
}

void Inventario::Consulta(){
    if (this->inventario.vacio())
        std::cout << "Inventario vacio" << std::endl;
    else{
        this->inventario.reiniciar_cursor(true);
        while(this->inventario.puede_avanzar())
            std::cout << this->inventario.avanzar(true) << std::endl;
    }
}
