# El Destino de James

Trabajo Práctico 2 de Algoritmos y Programación 2 2c2023.
Se recomienda fuertemente descargar esta plantilla u, opcionalmente, forkear el repositorio para versionarlo.

## Compilación:

El programa se puede compilar utilizando el **CMakeLists.txt** que está en el repositorio o bien ejecutando por consola:

> g++ -I include src/*.cpp main.cpp -o main -Wall -Werror -Wconversion

Al compilar con **CMake**, se deben agregar todos los archivos **.cpp** en la línea:

> add_executable(ayp2_plantilla_tp2_2c2023 main.cpp #otros archivos#)

## Tests:

Para ejecutar los tests, basta con cargar el **CMakeLists.txt** que se encuentra dentro de la carpeta tests/.

## Organización de archivos:

En la carpeta src/ van a encontrar los archivos .cpp del proyecto.
En la carpeta include/ van a encontrar los headers del proyecto.
Es decisión del estudiante el cómo y donde se guardan los archivos **save_file.csv**, con la consideración de que se
deben abrir usando rutas relativas.
