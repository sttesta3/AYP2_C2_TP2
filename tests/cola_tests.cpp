#include "gtest/gtest.h"
#include "cola.hpp"

class cola_tests : public ::testing::Test {
protected:
    cola<int> cola1{};
    int dato{};
};

// primero() y ultimo() queda probado.
TEST_F(cola_tests, alta) {
    cola1.alta(2);
    EXPECT_EQ(cola1.primero(), 2);
    EXPECT_EQ(cola1.ultimo(), 2);

    cola1.alta(1);
    cola1.alta(3);
    EXPECT_EQ(cola1.primero(), 2);
    EXPECT_EQ(cola1.ultimo(), 3);
}

TEST_F(cola_tests, baja) {
    cola1.alta(1);
    cola1.alta(3);

    dato = cola1.baja();
    EXPECT_EQ(dato, 1);
    EXPECT_EQ(cola1.primero(), 3);
    EXPECT_EQ(cola1.ultimo(), 3);
}

TEST_F(cola_tests, baja_maneja_cola_vacia) {
    EXPECT_THROW(cola1.baja(), cola_exception);
}

TEST_F(cola_tests, vacio) {
    EXPECT_TRUE(cola1.vacio());

    cola1.alta(1);
    EXPECT_FALSE(cola1.vacio());

    cola1.baja();
    EXPECT_TRUE(cola1.vacio());
}

TEST_F(cola_tests, tamanio) {
    EXPECT_EQ(cola1.tamanio(), 0);

    cola1.alta(1);
    cola1.alta(2);
    cola1.alta(3);
    EXPECT_EQ(cola1.tamanio(), 3);

    cola1.baja();
    EXPECT_EQ(cola1.tamanio(), 2);
}

TEST_F(cola_tests, primero_maneja_cola_vacia) {
    EXPECT_THROW(cola1.primero(), cola_exception);
}

TEST_F(cola_tests, ultimo_maneja_cola_vacia) {
    EXPECT_THROW(cola1.ultimo(), cola_exception);
}