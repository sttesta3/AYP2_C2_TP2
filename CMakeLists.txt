cmake_minimum_required(VERSION 3.22)
project(ayp2_plantilla_tp2_2c2023)

set(CMAKE_C_STANDARD 23)

add_compile_options(-Wall -Werror -Wconversion)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")
set(CXXFLAGS "-Wall -Werror -Wconversion")
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")

include_directories(include)
include_directories(src)

add_executable(ayp2_plantilla_tp2_2c2023
        main.cpp
        src/evento.cpp
        src/item.cpp
        include/cola.hpp
        include/lista_de.hpp
        include/nodo.hpp
        include/nodo_de.hpp
        # Otros archivos .cpp, de la forma src/ejemplo.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")