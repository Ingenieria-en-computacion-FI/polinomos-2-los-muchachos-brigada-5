#ifndef POLINOMIO_H
#define POLINOMIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Termino {
    float coeficiente;
    int exponente;
} Term;

typedef struct Nodo {
    Term termino;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

typedef struct {
    Nodo* cabeza;
    Nodo* cola;
    int numTerminos;
} Polinomio;

Polinomio* crearPolinomio();
void insertarTermino(Polinomio* p, float coeficiente, int exponente);
void eliminarTermino(Polinomio* p, int exponente);
float potencia(float base, int exp);
float evaluarPolinomio(Polinomio* p, float x);
Polinomio* sumarPolinomios(Polinomio* p1, Polinomio* p2);
Polinomio* multiplicarPolinomios(Polinomio* p1, Polinomio* p2);
void mostrarPolinomio(Polinomio* p);
char* polinomioToString(Polinomio* p);
void destruirPolinomio(Polinomio* p);

#endif