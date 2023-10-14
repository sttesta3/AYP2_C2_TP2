#include "eventos.hpp"

void Eventos::Acolar(evento nuevo){
    this->eventos.alta(nuevo);
}

evento Eventos::Descolar(){
    return this->eventos.baja();
}

void Eventos::Mostrar(){
    size_t aperturas_mapa = 0;
    size_t guardados = 0;

    while (this->eventos.tamanio() > 0){
        evento posicion = this->Descolar();
        if (posicion == ACCION_APERTURA_MAPA)
            aperturas_mapa += 1;
        else if (posicion == ACCION_GUARDADO)
            guardados += 1;
    }

    if (( aperturas_mapa > guardados ) && (aperturas_mapa > 5) && )
}

size_t Eventos::tamanio(){
    return this->eventos.tamanio();
}