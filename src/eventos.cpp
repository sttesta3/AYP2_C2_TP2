#include "eventos.hpp"

void Eventos::acolar(Evento nuevo){
    return this->acolar(nuevo,1);
}

void Eventos::acolar(Evento nuevo,size_t repeticiones){
    for (size_t i = 0; i < repeticiones; i++)
        this->acolar(nuevo);
}

Evento Eventos::descolar(){
    return this->eventos.baja();
}

std::string Eventos::definir_destino(){
    size_t aperturas_mapa = 0;
    size_t guardados = 0;

    while (this->eventos.tamanio() > 0 && guardados < 8){
        Evento posicion = this->descolar();
        if (posicion == ACCION_APERTURA_MAPA)
            aperturas_mapa += 1;
        else if (posicion == ACCION_GUARDADO)
            guardados += 1;
    }

    if (( aperturas_mapa > guardados ) && (aperturas_mapa > 5) && (guardados < 8))
        this->perfil = PERFIL_USUARIO_DESORIENTADO;
    else if ( (guardados > aperturas_mapa) && (5 < guardados) && ( guardados < 8 ) )
        this->perfil = PERFIL_USUARIO_PRECAVIDO;
    else if ( guardados >= 8 )
        this->perfil = PERFIL_USUARIO_ASUSTADO;
    else
        this->perfil = PERFIL_USUARIO_INDETERMINADO;

    return this->mostrar_destino();
}

std::string Eventos::mostrar_destino(){
    return this->perfil;
}

size_t Eventos::tamanio(){
    return this->eventos.tamanio();
}