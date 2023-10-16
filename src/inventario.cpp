#include "inventario.hpp"

bool Inventario::alta(Item nuevo){
    bool resultado = (this->inventario.tamanio() < TAMANIO_MAXIMO);
    if (resultado)
        this->inventario.alta(nuevo);
    
    return resultado;
}

size_t Inventario::baja(std::string baja){
    size_t resultado = 0;
    if (this->inventario.vacio())
        resultado = 2;
    else{
        this->inventario.reiniciar_cursor(true);
        Item posicion = this->inventario.avanzar(true);
        size_t i = 0;  

        while (!(posicion==baja) && this->inventario.puede_avanzar()){
            posicion = this->inventario.avanzar(true);
            i += 1;
        }

        if (posicion==baja)
            this->inventario.baja(i);
        else
            resultado = 1;
    }
    return resultado;
}

void Inventario::consulta(){
    if (this->inventario.vacio())
        std::cout << "Inventario vacio" << std::endl;
    else{
        this->inventario.reiniciar_cursor(true);
        while(this->inventario.puede_avanzar())
            std::cout << this->inventario.avanzar(true) << std::endl;
    }
}

size_t Inventario::tamanio(){
    return this->inventario.tamanio();
}

size_t Inventario::cargar_archivo(std::string ruta_archivo){
    std::ifstream archivo;
    archivo.open(ruta_archivo);

    size_t resultado = 0;
    if (archivo.is_open()){
        std::string linea;
        while (getline(archivo,linea) && this->inventario.tamanio() < 15){
            std::string nombre = "";
            std::string tipo = "";

            if ( this->procesar_linea_archivo(linea,nombre,tipo) ){
                Item nuevo = Item(nombre,tipo);
                this->alta(nuevo);
            }
        }

        if (getline(archivo,linea))
            resultado = 1;
    }
    else
        resultado = 2;

    archivo.close();
    return resultado;
}

bool Inventario::procesar_linea_archivo(std::string linea, std::string &nombre, std::string &tipo){
    size_t i = 0;
    size_t palabras = 0;

    while ( ( linea[i] != '\0' && linea[i] != '\n' ) && palabras < 2){
        if ( linea[i] != ',')
            (palabras == 0) ? nombre += linea[i] : tipo += linea[i];
        else
            palabras++;
    
        i++;
    }
    
    return analisis_linea_archivo(palabras,linea,tipo);
}

bool Inventario::analisis_linea_archivo(size_t palabras, std::string linea, std::string tipo){
    bool resultado = true;
    if (palabras == 0 || palabras >= 2){
        std::cout << "ERROR: Linea mal formateada (se descarta la linea)" << std::endl;
        std::cout << "Linea invalida: " << linea << "\n" <<std::endl;
        resultado = false;
    }
    else if ((tipo != TIPO_CURATIVO) && (tipo != TIPO_MUNICION) && (tipo != TIPO_PUZZLE)){
        std::cout << "ERROR: Tipo de item invalido (se descarta la linea)" << std::endl;
        std::cout << "Linea invalida: " << linea << "\n" << std::endl;
        resultado = false;
    }

    return resultado;
}

bool Inventario::guardar_archivo(std::string ruta_archivo){
    std::ofstream archivo;
    archivo.open(ruta_archivo);

    bool resultado = archivo.is_open();
    if (resultado){
        while (this->inventario.tamanio() > 0)
            archivo << this->inventario.baja(0) << std::endl;
    }
    archivo.close();

    return resultado;
}