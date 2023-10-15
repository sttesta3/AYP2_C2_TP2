#include "Menu.hpp"

std::string ruta_entrada = "";
std::string ruta_salida = "";

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
    while (this->entrada_usuario.compare(OPCION_SALIR) ){
        this->solicitar_entrada("MENU INICIAL> Operar sobre inventario/destino: ");

        if (this->entrada_usuario == OPCION_DESTINO){
            this->interaccion_destino();
            this->entrada_usuario = "";
        }
        else if (this->entrada_usuario == OPCION_INVENTARIO){
            this->interaccion_inventario();
            this->entrada_usuario = "";
        }
        else if (this->entrada_usuario == OPCION_AYUDA)
            this->mensaje_de_ayuda(MENSAJE_AYUDA_INICIAL);
        else if (this->entrada_usuario != OPCION_SALIR)
            this->mensaje_de_ayuda(MENSAJE_AYUDA_ERROR);
    }
}

void Menu::interaccion_inventario(void){
    // LOOP DE ITERACION
    bool repetir = true;
    do {
        this->solicitar_entrada("INVENTARIO> Accion sobre el inventario: ");

        if (this->entrada_usuario == OPCION_INVENTARIO_ALTA)
            this->alta();
        else if (this->entrada_usuario == OPCION_INVENTARIO_BAJA)
            this->baja();
        else if (this->entrada_usuario == OPCION_INVENTARIO_CONSULTA)
            this->consulta();
        else if (this->entrada_usuario == OPCION_AYUDA)
            this->mensaje_de_ayuda(MENSAJE_AYUDA_INVENTARIO);
        else if (this->entrada_usuario != OPCION_SALIR)
            this->mensaje_de_ayuda(MENSAJE_AYUDA_ERROR);
        else
            repetir = false;

    } while (repetir);
}

void Menu::interaccion_destino(void){
    // LOOP DE ITERACION
    bool repetir = true;    
    do {
        this->solicitar_entrada("DESTINO> Accion sobre el destino: ");
        if (this->entrada_usuario == OPCION_DESTINO_AGREGAR)
            this->agregar_evento();
        else if (this->entrada_usuario == OPCION_DESTINO_DEFINIR)
            this->definir_destino();
        else if (this->entrada_usuario == OPCION_DESTINO_MOSTRAR)
            this->mostrar_suceso();
        else if (this->entrada_usuario == OPCION_AYUDA)
            this->mensaje_de_ayuda(MENSAJE_AYUDA_DESTINO);
        else if (this->entrada_usuario != OPCION_SALIR)
            this->mensaje_de_ayuda(MENSAJE_AYUDA_ERROR);
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
    this->solicitar_repeticiones_evento();
    for (int i = 0; i < stoi(this->entrada_usuario) ; i++)
        this->eventos.acolar(nuevo);
}

void Menu::definir_destino(){
    std::string perfil = this->eventos.definir_destino();
    if (perfil == PERFIL_USUARIO_INDETERMINADO)
        std::cout << "No se pudo determinar el perfil del jugador\n" << std::endl;
    else
        std::cout << "Destino definido. El jugador es: " << perfil << "\n"<< std::endl;
}

void Menu::mostrar_suceso(){
    std::string perfil = this->eventos.mostrar_destino();
    if (perfil == PERFIL_USUARIO_DESORIENTADO)
        std::cout << "Aumento de factores ambientales\n" << std::endl;
    else if (perfil == PERFIL_USUARIO_PRECAVIDO)
        std::cout << "Aumento en la cantidad de enemigos\n" << std::endl;
    else if (perfil == PERFIL_USUARIO_ASUSTADO)
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

void Menu::solicitar_repeticiones_evento(){
    this->solicitar_entrada("Cantidad de veces experimentado: ");
    size_t numero = str_to_int(this->entrada_usuario);
    while (numero <= 0 || numero > 20){
        std::cout << " - Entrada invalida. Favor reingresar" << std::endl;
        if (numero <= 0)
            std::cout << " - El numero ingresado debe ser mayor que cero\n" << std::endl;
        else if (numero > 20)
            std::cout << " - El numero ingresado debe ser menor que " << CANT_EVENTOS_MAXIMA << "\n" << std::endl;
        this->solicitar_entrada("Cantidad de veces experimentado: ");
        numero = str_to_int(this->entrada_usuario);
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
        this->mensaje_de_ayuda(MENSAJE_ERROR_ITEM);
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

    std::ifstream test_i;
    std::ofstream test_o;
    (carga) ? test_i.open(this->entrada_usuario) : test_o.open(this->entrada_usuario);
    if (carga){
        while (!test_i.is_open()){
            std::cout << " - El archivo no pudo ser abierto. favor reingresar\n" << std::endl;
            this->solicitar_entrada(mensaje);
            test_i.open(this->entrada_usuario);    
        }   
        test_i.close();
    }
    else {
        while (!test_o.is_open()){
            std::cout << " - El archivo no pudo ser abierto. favor reingresar\n" << std::endl;
            this->solicitar_entrada(mensaje);
            test_o.open(this->entrada_usuario);
        }
        test_o.close();
    }
    (carga) ? ruta_entrada = this->entrada_usuario : ruta_salida = this->entrada_usuario;
}

void Menu::solicitar_forzado(size_t indice){
    std::string mensaje;
    switch (indice){
        case CONSULTA_CARGA: mensaje = "¿Desea cargar inventario desde savefile?[S/N]: "; break;
        case CONSULTA_GUARDADO: mensaje = "¿Desea guardar inventario en savefile?[S/N]: ";   break;
        case CONSULTA_SOBREESCRITURA: mensaje = "¿Desea sobreescribir archivo de entrada?[S/N]: "; break;
    }

    this->solicitar_entrada(mensaje);
    while (this->entrada_usuario != "S" && this->entrada_usuario != "N"){
        std::cout << "Entrada invalida. Favor reingresar" << std::endl;
        this->solicitar_entrada(mensaje);
    }
}

bool Menu::solicitar_carga(){
    // SOLICITAR ENTRADA DE USUARIO
    this->solicitar_forzado(CONSULTA_CARGA);

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
    this->solicitar_forzado(CONSULTA_GUARDADO);

    bool resultado = (this->entrada_usuario == "S");
    // Validacion
    if (resultado){
        // Preguntar por sobreescritura
        if (ruta_entrada != ""){
            this->solicitar_forzado(CONSULTA_SOBREESCRITURA);
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

void Menu::mensaje_de_ayuda(size_t selector){
    switch (selector){
        case MENSAJE_AYUDA_INICIAL: {
            std::cout << " * " << OPCION_INVENTARIO << ": Sub Menu para modificar inventario" << std::endl;
            std::cout << " * " << OPCION_DESTINO << " Sub Menu para modificar destino" << std::endl;
            std::cout << " * " << OPCION_SALIR << ": Salir de prueba de funcionalidades\n" << std::endl;
        }; break;
        case MENSAJE_AYUDA_INVENTARIO: {
            std::cout << " * " << OPCION_INVENTARIO_ALTA << ": Dar de alta nuevo Item en inventario (max 15)" << std::endl;
            std::cout << " * " << OPCION_INVENTARIO_BAJA << ": Dar de baja Item de inventario" << std::endl;
            std::cout << " * " << OPCION_INVENTARIO_CONSULTA << ": Mostrar inventario" << std::endl;
            std::cout << " * " << OPCION_SALIR << ": Salir de submenu de manejo de inventario\n" << std::endl;
        }; break;
        case MENSAJE_AYUDA_DESTINO: {
            std::cout << " * " << OPCION_DESTINO_AGREGAR << ": Agregar evento de usuario" << std::endl;
            std::cout << " * " << OPCION_DESTINO_DEFINIR << ": Definir perfil de usuario" << std::endl;
            std::cout << " * " << OPCION_DESTINO_MOSTRAR << ": Mostrar suceso segun perfil de usuario" << std::endl;
            std::cout << " * " << OPCION_SALIR << ": Salir de submenu de manejo de destino\n" << std::endl;
        }; break;
        case MENSAJE_AYUDA_ERROR: {
            std::cout << " - Entrada invalida, favor reingresar" << std::endl;
            std::cout << " - Ingrese '"<< OPCION_AYUDA <<"' para ver opciones del sub-menu\n" << std::endl;
        }; break;
        case MENSAJE_ERROR_ITEM: {
            std::cout << " - Entrada invalida, favor reingresar" << std::endl;
            std::cout << " - Tipo de item existentes: " << TIPO_CURATIVO << ", " << TIPO_MUNICION << " y " << TIPO_PUZZLE << "\n" << std::endl;
        }; break;
    }
}

size_t Menu::str_to_int(std::string string){
    size_t largo = string_len(string);
    size_t i = 0;
    size_t resultado = 0;
    
    if (largo > 2)
        resultado = -1;
    else {
        while ( (int)string[i] >= 48 && (int)string[i] <= 57 && i < largo ){
            resultado += int(pow(10,largo - 1 -i))*((int)string[i] - 48);
            i++;
        }
        
        if (((int)string[i] < 48 || (int)string[i] > 57) && i < largo)
            resultado = -1;
    }

    return resultado;
}

size_t Menu::string_len(std::string string){
    size_t i = 0;
    while (string[i] != '\0')
        i++;
    return i;
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

