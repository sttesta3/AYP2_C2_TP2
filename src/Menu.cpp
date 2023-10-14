#include "Menu.hpp"

std::string ruta_entrada = "";
std::string ruta_salida = "";
const size_t TAMANIO_MAXIMO = 15;
const size_t CARGA = 0;
const size_t GUARDADO = 1;
const size_t SOBREESCRITURA = 2;

Menu::Menu(){
    this->validar_ruta_predefinida(true);
    this->validar_ruta_predefinida(false);

    // CARGAR desde archivo
    if (ruta_entrada == "")
        this->solicitar_carga();

    if (ruta_entrada != "")
        this->cargar_archivo();
}

Menu::~Menu(){
    // GUARDAR archivo
    if (ruta_salida == "")
        this->solicitar_guardado();

    if (ruta_salida != "")
        this->guardar_archivo();
    
    std::cout << "¡Hasta luego!\n" << std::endl;
}

void Menu::juego(void){
    // LOOP DE ITERACION
    while (this->entrada_usuario.compare("SALIR") ){
        this->solicitar_entrada("MENU INICIAL> Operar sobre inventario/destino: ");

        if (this->entrada_usuario == "DESTINO"){
            this->interaccion_destino();
            this->entrada_usuario = "";
        }
        else if (this->entrada_usuario == "INVENTARIO"){
            this->interaccion_inventario();
            this->entrada_usuario = "";
        }
        else if (this->entrada_usuario == "AYUDA"){
            std::cout << " * INVENTARIO: Sub Menu para modificar inventario" << std::endl;
            std::cout << " * DESTINO: Sub Menu para modificar destino" << std::endl;
            std::cout << " * SALIR: Salir de prueba de funcionalidades\n" << std::endl;
        }
        else if (this->entrada_usuario != "SALIR"){
            std::cout << " - Input invalido, favor reingresar" << std::endl;
            std::cout << " - Ingrese 'AYUDA' para ver opciones del menu\n" << std::endl;
        }
    }
}

void Menu::interaccion_inventario(void){
    // LOOP DE ITERACION
    bool repetir = true;
    do {
        this->solicitar_entrada("INVENTARIO> Accion sobre el inventario: ");

        if (this->entrada_usuario == "ALTA")
            this->alta();
        else if (this->entrada_usuario == "BAJA")
            this->baja();
        else if (this->entrada_usuario == "CONSULTA")
            this->consulta();
        else if (this->entrada_usuario == "AYUDA"){
            std::cout << " * ALTA: Dar de alta nuevo Item en inventario (max 15)" << std::endl;
            std::cout << " * BAJA: Dar de baja Item de inventario" << std::endl;
            std::cout << " * CONSULTA: Mostrar inventario" << std::endl;
            std::cout << " * SALIR: Salir de submenu de manejo de inventario\n" << std::endl;
        }
        else if (this->entrada_usuario != "SALIR"){
            std::cout << " - Input invalido, favor reingresar" << std::endl;
            std::cout << " - Ingrese 'AYUDA' para ver opciones del sub-menu\n" << std::endl;
        }
        else
            repetir = false;

    } while (repetir);
}

void Menu::interaccion_destino(void){
    // LOOP DE ITERACION
    bool repetir = true;    
    do {
        this->solicitar_entrada("DESTINO> Accion sobre el destino: ");
        if (this->entrada_usuario == "AGREGAR_EVENTO")
            this->agregar_evento();
        else if (this->entrada_usuario == "DEFINIR_DESTINO")
            this->definir_destino();
        else if (this->entrada_usuario == "MOSTRAR_SUCESO")
            this->mostrar_suceso();
        else if (this->entrada_usuario == "AYUDA"){
            std::cout << " * AGREGAR_EVENTO: Agregar evento de usuario" << std::endl;
            std::cout << " * DEFINIR_DESTINO: Definir perfil de usuario" << std::endl;
            std::cout << " * MOSTRAR_SUCESO: Mostrar suceso segun perfil de usuario" << std::endl;
            std::cout << " * SALIR: Salir de submenu de manejo de destino\n" << std::endl;
        }
        else if (this->entrada_usuario != "SALIR"){
            std::cout << " - Input invalido, favor reingresar" << std::endl;
            std::cout << " - Ingrese 'AYUDA' para ver opciones del sub-menu\n" << std::endl;
        }
        else
            repetir = false;
    } while (repetir);
}

//.........................................................................................
//............. FUNCIONES DE MANEJO DE DESTINO (TP 2)
//.........................................................................................

void Menu::agregar_evento(){
    this->solicitar_evento();
    Evento nuevo = Evento( this->entrada_usuario );
    this->eventos.acolar(nuevo);
}

void Menu::definir_destino(){
    std::string perfil = this->eventos.definir_destino();
    if (perfil == "INDETERMINADO")
        std::cout << "No se pudo determinar el perfil del jugador" << std::endl;
    else
        std::cout << "Destino definido. El jugador es: " << perfil << "\n"<< std::endl;
}

void Menu::mostrar_suceso(){
    std::string perfil = this->eventos.mostrar_destino();
    if (perfil == "DESORIENTADO")
        std::cout << "Aumento de factores ambientales\n" << std::endl;
    else if (perfil == "PRECAVIDO")
        std::cout << "Aumento en la cantidad de enemigos\n" << std::endl;
    else if (perfil == "ASUSTADO")
        std::cout << "Evento Pyramid Head adelantado\n" << std::endl;
    else
        std::cout << "Comportamiento aún no definido\n" << std::endl;
}

void Menu::solicitar_evento(){
    this->solicitar_entrada("Evento experimentado: ");
    while (this->entrada_usuario != ACCION_APERTURA_MAPA && this->entrada_usuario != ACCION_GUARDADO){
        std::cout << " - Entrada invalida. Favor reingresar" << std::endl;
        std::cout << " - Eventos programados: " << ACCION_APERTURA_MAPA << " y " << ACCION_GUARDADO << "\n" << std::endl;
        this->solicitar_entrada("Evento experimentado: ");
    }
}

//.........................................................................................
//............. FUNCIONES DE MANEJO DE INVENTARIO (TP 1)
//.........................................................................................

void Menu::alta(){
    // SOLICITAR INPUT A USUARIO
    if (this->inventario.tamanio() < TAMANIO_MAXIMO){
        Item alta = Item(this->solicitar_nombre_item(),this->solicitar_tipo_item());
        this->inventario.alta(alta);
    }
    else
        std::cout << "Ha alcanzado el maximo tamanio para el inventario\n" << std::endl;
}

void Menu::alta(std::string nombre, std::string tipo){
    if (this->inventario.tamanio() < TAMANIO_MAXIMO){
        Item alta = Item(nombre,tipo);
        this->inventario.alta(alta);
    }
    else
        std::cout << "Ha alcanzado el maximo tamanio para el inventario\n" << std::endl;
}

void Menu::baja(){
    if (this->inventario.tamanio() == 0)
        std::cout << "Inventario vacio" << std::endl;
    else
        this->inventario.baja(this->solicitar_nombre_item());    
}

void Menu::consulta(){
    this->inventario.consulta();
    std::cout << std::endl;
}

//.........................................................................................
//............. FUNCIONES DE MANEJO DE INTERACCION CON USUARIO
//.........................................................................................

void Menu::solicitar_entrada(std::string mensaje){
    std::cout << mensaje;
    getline(std::cin,this->entrada_usuario);
    std::cout << std::endl;
}

std::string Menu::solicitar_tipo_item(){
    this->solicitar_entrada("Tipo del item: ");

    while( !( (this->entrada_usuario == TIPO_CURATIVO) || (this->entrada_usuario == TIPO_MUNICION) || (this->entrada_usuario == TIPO_PUZZLE) )){
        std::cout << " - Entrada invalida, favor reingresar" << std::endl;
        std::cout << " - Tipo de item existentes: " << TIPO_CURATIVO << ", " << TIPO_MUNICION << " y " << TIPO_PUZZLE << "\n" << std::endl;
        this->solicitar_entrada("Tipo del item: ");
    }   

    return this->entrada_usuario;
}

std::string Menu::solicitar_nombre_item(){
    this->solicitar_entrada("Nombre del item: ");
    return this->entrada_usuario;
}

void Menu::solicitar_archivo(bool carga){
    std::string mensaje;
    (carga) ? mensaje = "Ingrese ruta de archivo de carga: ": mensaje = "Ingrese ruta de archivo de guardado: ";

    this->solicitar_entrada(mensaje);

    std::fstream test;
    test.open(this->entrada_usuario);
    while (!test.is_open()){
        std::cout << " - El archivo no pudo ser abierto. favor reingresar\n" << std::endl;
        this->solicitar_entrada(mensaje);
        test.open(this->entrada_usuario);
    }
    test.close();
    (carga) ? ruta_entrada = this->entrada_usuario : ruta_salida = this->entrada_usuario;
}

void Menu::solicitar_forzado(size_t indice){
    std::string mensaje;
    switch (indice){
        case 0: mensaje = "¿Desea cargar inventario desde savefile?[S/N]: "; break;
        case 1: mensaje = "¿Desea guardar inventario en savefile?[S/N]: ";   break;
        case 2: mensaje = "¿Desea sobreescribir archivo de entrada?[S/N]: "; break;
    }

    this->solicitar_entrada(mensaje);
    while (this->entrada_usuario != "S" && this->entrada_usuario != "N"){
        std::cout << "Entrada invalida. Favor reingresar" << std::endl;
        this->solicitar_entrada(mensaje);
    }
}

bool Menu::solicitar_carga(){
    // SOLICITAR ENTRADA DE USUARIO
    this->solicitar_forzado(CARGA);

    // Intentar abrir archivo 
    bool resultado = (this->entrada_usuario == "S");
    if (resultado){
        this->solicitar_archivo(true);
        ruta_entrada = this->entrada_usuario;        
    }

    return resultado;
}

bool Menu::solicitar_guardado(){
    // Solicitar entrada
    this->solicitar_forzado(GUARDADO);

    bool resultado = (this->entrada_usuario == "S");
    // Validacion
    if (resultado){
        // Preguntar por sobreescritura
        if (ruta_entrada != ""){
            this->solicitar_forzado(SOBREESCRITURA);
            if (this->entrada_usuario == "S")
                ruta_salida = ruta_entrada;         
        }

        if ((ruta_entrada != ruta_salida) || ruta_entrada == "" ){
            this->solicitar_archivo(false);
            ruta_salida = this->entrada_usuario;
        }
    }
    
    return resultado;
}

//.........................................................................................
//............. FUNCIONES DE MANEJO DE ARCHVIOS
//.........................................................................................

void Menu::cargar_archivo(){
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

        if ( this->procesar_linea_archivo(linea,nombre,tipo) )
            this->alta(nombre,tipo);
    }
    archivo_entrada.close();

}

void Menu::guardar_archivo(){
    std::ofstream archivo;
    archivo.open(ruta_salida);
    while (this->inventario.tamanio() > 0)
        archivo << this->inventario.baja() << std::endl;
    archivo.close();
}

bool Menu::solicitar_carga(){
    // SOLICITAR ENTRADA DE USUARIO
    this->solicitar_forzado(CARGA);

    // Intentar abrir archivo 
    bool resultado = (this->entrada_usuario == "S");
    if (resultado){
        this->solicitar_archivo(true);
        ruta_entrada = this->entrada_usuario;        
    }

    return resultado;
}

bool Menu::solicitar_guardado(){
    // Solicitar entrada
    this->solicitar_forzado(GUARDADO);

    bool resultado = (this->entrada_usuario == "S");
    // Validacion
    if (resultado){
        // Preguntar por sobreescritura
        if (ruta_entrada != ""){
            this->solicitar_forzado(SOBREESCRITURA);
            if (this->entrada_usuario == "S")
                ruta_salida = ruta_entrada;         
        }

        if ((ruta_entrada != ruta_salida) || ruta_entrada == "" ){
            this->solicitar_archivo(false);
            ruta_salida = this->entrada_usuario;
        }
    }
    
    return resultado;
}

void Menu::validar_ruta_predefinida(bool entrada_salida){
    std::fstream archivo;
    (entrada_salida) ? archivo.open(ruta_entrada) : archivo.open(ruta_salida);

    if (archivo.is_open())
        archivo.close();
    else 
        (entrada_salida) ? ruta_entrada = "" : ruta_salida = "" ;
}

bool Menu::procesar_linea_archivo(std::string linea, std::string &nombre, std::string &tipo){
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

bool Menu::analisis_linea_archivo(size_t palabras, std::string linea, std::string tipo){
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

