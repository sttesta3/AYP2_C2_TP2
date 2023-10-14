#include "eventos.hpp"

void Eventos::acolar(Evento nuevo){
    this->eventos.alta(nuevo);
}

Evento Eventos::descolar(){
    return this->eventos.baja();
}

std::string Eventos::definir_destino(){
    std::string resultado;
    size_t aperturas_mapa = 0;
    size_t guardados = 0;

    while (this->eventos.tamanio() > 0){
        Evento posicion = this->descolar();
        if (posicion == ACCION_APERTURA_MAPA)
            aperturas_mapa += 1;
        else if (posicion == ACCION_GUARDADO)
            guardados += 1;
    }

    if (( aperturas_mapa > guardados ) && (aperturas_mapa > 5) && (guardados < 8))
        this->perfil = "DESORIENTADO";
    else if ( (guardados > aperturas_mapa) && (5 < guardados) && ( guardados < 8 ) )
        this->perfil = "PRECAVIDO";
    else if ( guardados >= 8 )
        this->perfil = "ASUSTADO";
    else
        this->perfil = "INDETERMINADO";

    return this->mostrar_destino();
}

std::string Eventos::mostrar_destino(){
    return this->perfil;
}

size_t Eventos::tamanio(){
    return this->eventos.tamanio();
}