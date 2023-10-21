#include "Menu.hpp"

Menu::Menu(){
    this->validar_ruta_predefinida_carga();
    this->validar_ruta_predefinida_guardado();
}

Menu::~Menu(){    
    std::cout << "¡Hasta luego!\n" << std::endl;
}

void Menu::juego(void){
    // CARGAR desde archivo
    if (ruta_entrada == "")
        this->solicitar_carga();
    if (ruta_entrada != "")
        this->cargar_archivo_inventario();

    // LOOP DE ITERACION
    do {
        this->solicitar_entrada("MENU INICIAL> Operar sobre inventario/destino: ");

        switch ( OPCIONES_MENU[this->entrada_usuario] ){
            case 1: this->interaccion_destino(); break;
            case 2: this->interaccion_inventario(); break;
            case 3: this->mensaje_de_ayuda(MENSAJE_AYUDA_INICIAL); break;
            default: this->mensaje_de_ayuda(MENSAJE_ERROR);
        }
    } while (this->entrada_usuario != OPCION_SALIR );

    // GUARDAR archivo
    if (ruta_salida == "")
        this->solicitar_guardado();
    if (ruta_salida != "")
        this->guardar_archivo_inventario();
}

void Menu::interaccion_inventario(void){
    do {
        this->solicitar_entrada("INVENTARIO> Accion sobre el inventario: ");

        switch( OPCIONES_MENU_INVENTARIO[this->entrada_usuario] ){
            case 0: this->mensaje_de_ayuda(MENSAJE_ERROR); break;
            case 1: this->alta_inventario(); break;
            case 2: this->baja_inventario(); break;
            case 3: this->consulta_inventario(); break;
            case 4: this->mensaje_de_ayuda(MENSAJE_AYUDA_INVENTARIO); break;
        }
    } while (this->entrada_usuario != OPCION_SALIR);

    this->entrada_usuario = "";
}

void Menu::interaccion_destino(void){
    do {
        this->solicitar_entrada("DESTINO> Accion sobre el destino: ");
        
        switch ( OPCIONES_MENU_DESTINO[ this->entrada_usuario ] ){
            case 1: this->agregar_evento(); break;
            case 2: this->definir_destino(); break;
            case 3: this->mostrar_suceso(); break;
            case 4: this->mensaje_de_ayuda(MENSAJE_AYUDA_DESTINO); break;
            this->mensaje_de_ayuda(MENSAJE_ERROR);
        }
    } while (this->entrada_usuario != OPCION_SALIR);

    this->entrada_usuario = "";
}

//.........................................................................................
//............. FUNCIONES DE MANEJO DE DESTINO (TP 2)
//.........................................................................................

void Menu::agregar_evento(){
    this->solicitar_evento();
    Evento nuevo = Evento( this->entrada_usuario );
    this->solicitar_repeticiones_evento();
    this->eventos.acolar(nuevo,stoi(this->entrada_usuario) );
}

void Menu::definir_destino(){
    std::string perfil = this->eventos.definir_destino();
    if (perfil == PERFIL_USUARIO_INDETERMINADO)
        std::cout << "No se pudo determinar el perfil del jugador\n" << std::endl;
    else
        std::cout << "Destino definido. El jugador es: " << perfil << "\n"<< std::endl;
}

void Menu::mostrar_suceso(){
    std::cout << MENSAJES_SUCESOS[ this->eventos.mostrar_destino() ] << "\n" << std::endl;
}

void Menu::solicitar_evento(){
    this->solicitar_entrada("Evento experimentado: ");
    while (this->entrada_usuario != ACCION_APERTURA_MAPA && this->entrada_usuario != ACCION_GUARDADO){
        this->mensaje_de_ayuda(MENSAJE_ERROR_EVENTOS);
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

void Menu::alta_inventario(){
    // Se consulta tamaño porque seria raro que te pida un item y que no lo pueda agregar
    if (this->inventario.tamanio() < TAMANIO_MAXIMO){
        Item alta = Item(this->solicitar_nombre_item(),this->solicitar_tipo_item());
        this->inventario.alta(alta);
    }
    else
        std::cout << "Tamanio maximo ('"<< TAMANIO_MAXIMO <<") alcanzado" << std::endl;
}

void Menu::baja_inventario(){
    // Se consulta tamaño porque seria raro que te pida un item y que no lo pueda eliminar
    if (this->inventario.tamanio() == 0)
        std::cout << "Inventario vacio" << std::endl;
    else{
        std::string nombre_item = this->solicitar_nombre_item();
        size_t resultado = this->inventario.baja(nombre_item);    
        if (resultado == 1)
            std::cout << "Item '" << nombre_item << "' no encontrado\n" << std::endl;
    }
}

void Menu::consulta_inventario(){
    this->inventario.consulta();
    std::cout << std::endl;
}

void Menu::cargar_archivo_inventario(){
    size_t resultado = this->inventario.cargar_archivo(ruta_entrada);
    if (resultado == 1){
        std::cout << "Se excedio el maximo de elementos en la carga." << std::endl;
        std::cout << "Los items del 15avo en adelante fueron descartados.\n" << std::endl;
    }
}

void Menu::guardar_archivo_inventario(){
    this->inventario.guardar_archivo(ruta_salida);
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

void Menu::solicitar_archivo_carga(){
    this->solicitar_entrada("Ingrese ruta de archivo de carga: ");

    std::ifstream archivo;
    archivo.open(this->entrada_usuario);
    while (!archivo.is_open()){
        std::cout << " - El archivo no pudo ser abierto. favor reingresar\n" << std::endl;
        this->solicitar_entrada("Ingrese ruta de archivo de carga: ");
        archivo.open(this->entrada_usuario);    
    }   
    archivo.close();
}

void Menu::solicitar_archivo_guardado(){
    this->solicitar_entrada("Ingrese ruta de archivo de guardado: ");

    std::ofstream archivo;
    archivo.open(this->entrada_usuario);
    while (!archivo.is_open()){
        std::cout << " - El archivo no pudo ser abierto. favor reingresar\n" << std::endl;
        this->solicitar_entrada("Ingrese ruta de archivo de guardado: ");
        archivo.open(this->entrada_usuario);    

    }   
    archivo.close();
}

void Menu::solicitar_forzado(size_t indice){
    std::string mensaje = MENSAJE_FORZADO[indice];

    this->solicitar_entrada(mensaje);
    while (this->entrada_usuario != "S" && this->entrada_usuario != "N"){
        std::cout << "Entrada invalida. Favor reingresar\n" << std::endl;
        this->solicitar_entrada(mensaje);
    }
}

bool Menu::solicitar_carga(){
    // SOLICITAR ENTRADA DE USUARIO
    this->solicitar_forzado(CONSULTA_CARGA);

    // Intentar abrir archivo 
    bool resultado = (this->entrada_usuario == "S");
    if (resultado){
        this->solicitar_archivo_carga();
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
            this->solicitar_archivo_guardado();
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
        case MENSAJE_ERROR_EVENTOS: {
            std::cout << " - Entrada invalida. Favor reingresar" << std::endl;
            std::cout << " - Eventos programados: " << ACCION_APERTURA_MAPA << " y " << ACCION_GUARDADO << "\n" << std::endl;
        }; break;
        case MENSAJE_ERROR: {
            if (this->entrada_usuario != OPCION_SALIR)
                this->mensaje_de_ayuda(MENSAJE_AYUDA_ERROR);
        };
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

void Menu::validar_ruta_predefinida_carga(){
    std::ifstream archivo;
    archivo.open(ruta_entrada);

    if (archivo.is_open())
        archivo.close();
    else if (ruta_entrada != "") {
        std::cout << "No se pudo abrir la ruta de carga predefinida: " << ruta_entrada << "\n" << std::endl;
        ruta_entrada = "";
    }
}

void Menu::validar_ruta_predefinida_guardado(){
    std::ofstream archivo;
    archivo.open(ruta_salida);

    if (archivo.is_open())
        archivo.close();
    else if (ruta_salida != "") {
        std::cout << "No se pudo abrir la ruta de guardado predefinida: " << ruta_salida << "\n" << std::endl;
        ruta_salida = "";
    }
}
