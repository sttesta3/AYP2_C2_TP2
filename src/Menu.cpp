#include "Menu.hpp"

Menu::Menu(){
    this->ValidarArchivoPredefinido(true);
    this->ValidarArchivoPredefinido(false);

    // CARGAR desde archivo
    if (ruta_entrada == ""){
        if ( this->SolicitarCarga() )
            this->CargarArchivo();
    }
    else
        this->CargarArchivo();
}

Menu::~Menu(){

    // GUARDAR archivo
    if (ruta_salida == ""){
        if( this->SolicitarGuardado() )
            this->GuardarArchivo();
    }
    else
        this->GuardarArchivo();
    
    std::cout << "¡Hasta luego!\n" << std::endl;
}

void
Menu::Juego(void){
    // LOOP DE ITERACION
    while (this->entrada_usuario.compare("SALIR") ){
        this->SolicitarEntradaUsuario("Accion sobre el inventario: ");

        if (this->entrada_usuario == "ALTA")
            this->Alta();
        else if (this->entrada_usuario == "BAJA")
            this->Baja();
        else if (this->entrada_usuario == "CONSULTA")
            this->Consulta();
        else
            std::cout << "Input invalido, favor reingresar\n" << std::endl;
    }
}

void
Menu::SolicitarEntradaUsuario(std::string mensaje){
    std::cout << mensaje;
    getline(std::cin,this->entrada_usuario);
    std::cout << std::endl;
}

void 
Menu::Alta(){
    // SOLICITAR INPUT A USUARIO
    if (this->inventario.tamanio() < TAMANIO_MAXIMO){
        item alta = item(this->SolicitarNombreItem(),this->SolicitarTipoItem());
        this->inventario.Alta(alta);
    }
    else
        std::cout << "Ha alcanzado el maximo tamanio para el inventario\n" << std::endl;
}

void 
Menu::Alta(std::string nombre, std::string tipo){
    if (this->inventario.tamanio() < TAMANIO_MAXIMO){
        item alta = item(nombre,tipo);
        this->inventario.Alta(alta);
    }
    else
        std::cout << "Ha alcanzado el maximo tamanio para el inventario\n" << std::endl;
}

void 
Menu::Baja(){
    if (this->inventario.tamanio() == 0)
        std::cout << "Inventario vacio" << std::endl;
    else
        this->inventario.Baja(this->SolicitarNombreItem());    
    std::cout << std::endl;
}

void Menu::Consulta(){
    this->inventario.Consulta();
}

bool
Menu::ProcesarLinea(std::string linea, std::string &nombre, std::string &tipo){
    bool resultado = true;
    size_t i = 0;
    size_t words = 0;

    while ( ( linea[i] != '\0' && linea[i] != '\n' ) && words < 2){

        if ( linea[i] != ',')
            (words == 0) ? nombre += linea[i] : tipo += linea[i];
        else{
            (words == 0) ? nombre += '\0' : tipo += '\0';

            words++;
        }
        i++;
    }

    if (words == 0 || words >= 2){
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

void
Menu::CargarArchivo(){
    if (this->inventario.tamanio() == 15){
        std::cout << "Su archivo alcanzó la cantidad maxima de items" << std::endl;
        std::cout << "Todos los items del 15avo en adelante no serán cargados\n" << std::endl;
    }

    std::ifstream archivo_entrada;
    std::string linea;

    archivo_entrada.open(ruta_entrada);
    
    while (getline(archivo_entrada,linea) && this->inventario.tamanio() < 15){
        std::string nombre = "";
        std::string tipo = "";

        if ( this->ProcesarLinea(linea,nombre,tipo) )
            this->Alta(nombre,tipo);
    }
    archivo_entrada.close();

}

void Menu::GuardarArchivo(){
    std::ofstream archivo;
    archivo.open(ruta_salida);
    while (this->inventario.tamanio() > 0)
        archivo << this->inventario.Baja() << std::endl;
    archivo.close();
}

bool 
Menu::SolicitarCarga(){
    // SOLICITAR ENTRADA DE USUARIO
    this->SolicitarForzado(CARGA);

    // Intentar abrir archivo 
    bool resultado = (this->entrada_usuario == "S");
    if (resultado){
        this->SolicitarArchivo(true);
        ruta_entrada = this->entrada_usuario;        
    }

    return resultado;
}

bool 
Menu::SolicitarGuardado(){
    // Solicitar entrada
    this->SolicitarForzado(GUARDADO);

    bool resultado = (this->entrada_usuario == "S");
    // Validacion
    if (resultado){
        // Preguntar por sobreescritura
        if (ruta_entrada != ""){
            this->SolicitarForzado(SOBREESCRITURA);
            if (this->entrada_usuario == "S")
                ruta_salida = ruta_entrada;         
        }

        if ((ruta_entrada != ruta_salida) || ruta_entrada == "" ){
            this->SolicitarArchivo(false);
            ruta_salida = this->entrada_usuario;
        }
    }
    
    return resultado;
}

void Menu::ValidarArchivoPredefinido(bool entrada_salida){
    std::fstream archivo;
    (entrada_salida) ? archivo.open(ruta_entrada) : archivo.open(ruta_salida);

    if (archivo.is_open())
        archivo.close();
    else 
        (entrada_salida) ? ruta_entrada = "" : ruta_salida = "" ;
}


std::string Menu::SolicitarTipoItem(){
    this->SolicitarEntradaUsuario("Tipo del item: ");

    while( !( (this->entrada_usuario == TIPO_CURATIVO) || (this->entrada_usuario == TIPO_MUNICION) || (this->entrada_usuario == TIPO_PUZZLE) )){
        std::cout << "Entrada invalida, favor reingresar" << std::endl;
        this->SolicitarEntradaUsuario("Tipo del item: ");
    }   

    return this->entrada_usuario;
}

std::string Menu::SolicitarNombreItem(){
    this->SolicitarEntradaUsuario("Nombre del item: ");
    return this->entrada_usuario;
}

bool Menu::SolicitarArchivo(bool carga){
    std::string mensaje;
    (carga) ? mensaje = "Ingrese ruta de archivo de carga: ": mensaje = "Ingrese ruta de archivo de guardado: ";

    this->SolicitarEntradaUsuario(mensaje);

    std::fstream test;
    test.open(this->entrada_usuario);
    while (!test.is_open()){
        std::cout << "El archivo no pudo ser abierto. favor reingresar\n" << std::endl;
        this->SolicitarEntradaUsuario(mensaje);
        test.open(this->entrada_usuario);
    }
    test.close();
    (carga) ? ruta_entrada = this->entrada_usuario : ruta_salida = this->entrada_usuario;
}

void Menu::SolicitarForzado(size_t indice){
    std::string mensaje;
    switch (indice){
        case 0: mensaje = "¿Desea cargar inventario desde savefile?[S/N]: "; break;
        case 1: mensaje = "¿Desea guardar inventario en savefile?[S/N]: ";   break;
        case 2: mensaje = "¿Desea sobreescribir archivo de entrada?[S/N]: "; break;
    }

    this->SolicitarEntradaUsuario(mensaje);
    while (this->entrada_usuario != "S" && this->entrada_usuario != "N"){
        std::cout << "Entrada invalida. Favor reingresar" << std::endl;
        this->SolicitarEntradaUsuario(mensaje);
    }
}