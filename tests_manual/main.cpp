#include "../include/cola.hpp"
#include <iostream>

int main(){
    cola<size_t> cola1{};
    std::cout << "Pre alta" << std::endl;
    cola1.alta(2);
    std::cout << "Pre ultimo" << std::endl;
    std::cout << cola1.ultimo() << std::endl;
    std::cout << cola1.primero() << std::endl;
    if ((cola1.primero() == 2) && (cola1.ultimo() == 2))
        std::cout << "1. OK" << std::endl;
}