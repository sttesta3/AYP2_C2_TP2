#include "gtest/gtest.h"
#include "lista_de.hpp"

class lista_de_tests : public ::testing::Test {
protected:
    lista_de<int> lista{};
    int dato{};
};

// primero() y ultimo() queda probado.
TEST_F(lista_de_tests, alta) {
    lista.alta(2);
    EXPECT_EQ(lista.primero(), 2);
    EXPECT_EQ(lista.ultimo(), 2);

    lista.alta(1);
    lista.alta(3);
    EXPECT_EQ(lista.primero(), 2);
    EXPECT_EQ(lista.ultimo(), 3);
}

TEST_F(lista_de_tests, baja) {
    lista.alta(1);
    lista.alta(3);

    dato = lista.baja();
    EXPECT_EQ(dato, 3);
    EXPECT_EQ(lista.primero(), 1);
    EXPECT_EQ(lista.ultimo(), 1);
}

TEST_F(lista_de_tests, baja_maneja_lista_vacia) {
    lista.alta(1);
    lista.baja();
    EXPECT_THROW(lista.baja(), lista_exception);
}

TEST_F(lista_de_tests, elemento) {
    lista.alta(1);
    lista.alta(2, 0);
    lista.alta(3);
    lista.baja(0);

    EXPECT_EQ(lista.elemento(0), 1);
    EXPECT_EQ(lista.elemento(1), 3);
    EXPECT_EQ(lista.elemento(0), lista.primero());
    EXPECT_EQ(lista.elemento(1), lista.ultimo());
}

TEST_F(lista_de_tests, elemento_maneja_indice_mayor_igual) {
    lista.alta(1);
    lista.alta(2);
    lista.alta(3);

    EXPECT_THROW(lista.elemento(3), lista_exception);
    EXPECT_THROW(lista.elemento(4), lista_exception);
    EXPECT_NO_THROW(lista.elemento(2));
}

TEST_F(lista_de_tests, alta_indice) {
    lista.alta(1, 0);
    lista.alta(2, 1);
    lista.alta(3, 1);

    EXPECT_EQ(lista.primero(), 1);
    EXPECT_EQ(lista.elemento(1), 3);
    EXPECT_EQ(lista.ultimo(), 2);
}

TEST_F(lista_de_tests, alta_indice_maneja_indice_mayor) {
    lista.alta(1);
    lista.alta(2);
    lista.alta(3);

    EXPECT_THROW(lista.alta(4, 4), lista_exception);
    EXPECT_THROW(lista.alta(5, 5), lista_exception);
    EXPECT_NO_THROW(lista.alta(6, 3));
}

TEST_F(lista_de_tests, baja_indice) {
    lista.alta(1);
    lista.alta(2);
    lista.alta(3, 1);
    lista.alta(4, 1);

    dato = lista.baja(2);
    EXPECT_EQ(dato, 3);

    dato = lista.baja(2);
    EXPECT_EQ(dato, 2);

    dato = lista.baja(0);
    EXPECT_EQ(dato, 1);

    EXPECT_EQ(lista.primero(), 4);
    EXPECT_EQ(lista.ultimo(), 4);
}

TEST_F(lista_de_tests, baja_indice_maneja_indice_mayor_igual) {
    lista.alta(1);
    lista.alta(2);
    lista.alta(3);

    EXPECT_THROW(lista.baja(3), lista_exception);
    EXPECT_THROW(lista.baja(4), lista_exception);
    EXPECT_NO_THROW(lista.baja(2));
}

TEST_F(lista_de_tests, vacio) {
    EXPECT_TRUE(lista.vacio());

    lista.alta(1);
    EXPECT_FALSE(lista.vacio());

    lista.baja();
    EXPECT_TRUE(lista.vacio());
}

TEST_F(lista_de_tests, tamanio) {
    EXPECT_EQ(lista.tamanio(), 0);

    lista.alta(1);
    lista.alta(2);
    lista.alta(3);
    EXPECT_EQ(lista.tamanio(), 3);

    lista.baja();
    EXPECT_EQ(lista.tamanio(), 2);
}

TEST_F(lista_de_tests, puede_avanzar) {
    EXPECT_FALSE(lista.puede_avanzar());

    lista.alta(1);
    lista.alta(2);
    EXPECT_FALSE(lista.puede_avanzar());

    lista.reiniciar_cursor(true);
    EXPECT_TRUE(lista.puede_avanzar());

    lista.reiniciar_cursor(false);
    EXPECT_TRUE(lista.puede_avanzar());
}

TEST_F(lista_de_tests, avanzar) {
    lista.alta(1);
    lista.alta(2);
    lista.alta(3, 0);
    lista.alta(4, 2);

    lista.reiniciar_cursor(true);
    EXPECT_EQ(lista.avanzar(true), 3);
    EXPECT_EQ(lista.avanzar(true), 1);

    lista.reiniciar_cursor(false);
    EXPECT_EQ(lista.avanzar(false), 2);
    EXPECT_EQ(lista.avanzar(false), 4);
}

TEST_F(lista_de_tests, avanzar_maneja_no_puede_avanzar) {
    EXPECT_THROW(lista.avanzar(true), lista_exception);

    lista.alta(1);
    lista.alta(2);

    lista.reiniciar_cursor(true);
    EXPECT_NO_THROW(lista.avanzar(false));
    EXPECT_THROW(lista.avanzar(false), lista_exception);

    lista.reiniciar_cursor(false);
    EXPECT_NO_THROW(lista.avanzar(true));
    EXPECT_THROW(lista.avanzar(true), lista_exception);
}

TEST_F(lista_de_tests, reiniciar_cursor) {
    lista.alta(1);
    lista.reiniciar_cursor(true);
    EXPECT_TRUE(lista.puede_avanzar());

    lista.baja();
    lista.reiniciar_cursor(true);
    EXPECT_FALSE(lista.puede_avanzar());

    lista.reiniciar_cursor(false);
    EXPECT_FALSE(lista.puede_avanzar());
}

// Test problemático. Prueba estado interno (privado).
/*TEST_F(lista_de_tests, caso_borde_cursor_actual_se_elimina) {
    lista.alta(1);
    lista.alta(2);
    lista.alta(3);
    lista.alta(4);

    lista.reiniciar_cursor(true);
    lista.avanzar(true);
    lista.avanzar(true);
    lista.baja(2);
    EXPECT_FALSE(lista.puede_avanzar());

    lista.reiniciar_cursor(true);
    lista.baja(0);
    EXPECT_FALSE(lista.puede_avanzar());

    lista.reiniciar_cursor(false);
    lista.baja();
    EXPECT_FALSE(lista.puede_avanzar());

    lista.reiniciar_cursor(true);
    EXPECT_TRUE(lista.puede_avanzar());
}*/

TEST_F(lista_de_tests, primero_maneja_lista_vacia) {
    EXPECT_THROW(lista.primero(), lista_exception);
}

TEST_F(lista_de_tests, ultimo_maneja_lista_vacia) {
    EXPECT_THROW(lista.ultimo(), lista_exception);
}