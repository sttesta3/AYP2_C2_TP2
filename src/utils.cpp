#include "utils.hpp"

size_t str_to_int(std::string string){
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

size_t string_len(std::string string){
    size_t i = 0;
    while (string[i] != '\0')
        i++;
    return i;
}
