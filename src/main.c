#include "polinomio.h"

int main() {

    printf("=== CASO 1: Crear un polinomio vacio ===\n");
    Polinomio* p = crearPolinomio();
    printf("P: "); mostrarPolinomio(p);
    printf("Esperado: 0\n\n");

    printf("=== CASO 2: Suma de polinomios ===\n");
    Polinomio* p1 = crearPolinomio();
    insertarTermino(p1, 3, 2);
    insertarTermino(p1, 2, 1);
    insertarTermino(p1, 1, 0);

    Polinomio* p2 = crearPolinomio();
    insertarTermino(p2, 1, 2);
    insertarTermino(p2, 4, 0);

    printf("P1: "); mostrarPolinomio(p1);
    printf("P2: "); mostrarPolinomio(p2);

    Polinomio* suma = sumarPolinomios(p1, p2);
    printf("P1+P2: "); mostrarPolinomio(suma);
    printf("Esperado: 4x^2+2x+5\n");

    printf("\n=== CASO 3: Simplificacion ===\n");
    Polinomio* p3 = crearPolinomio();
    insertarTermino(p3,  3, 2);
    insertarTermino(p3, -3, 2);
    printf("Resultado: "); mostrarPolinomio(p3);
    printf("Esperado: 0\n");

    printf("\n=== CASO 4: Eliminacion de termino ===\n");
    Polinomio* p4 = crearPolinomio();
    insertarTermino(p4, 5, 3);
    insertarTermino(p4, 2, 1);
    insertarTermino(p4, 7, 0);
    printf("Antes: "); mostrarPolinomio(p4);
    eliminarTermino(p4, 1);
    printf("Despues: "); mostrarPolinomio(p4);
    printf("Esperado: 5x^3+7\n");

    printf("\n=== CASO 5: Multiplicacion ===\n");
    Polinomio* p5 = crearPolinomio();
    insertarTermino(p5, 1, 1);
    insertarTermino(p5, 1, 0);

    Polinomio* p6 = crearPolinomio();
    insertarTermino(p6,  1, 1);
    insertarTermino(p6, -1, 0);

    printf("P5: "); mostrarPolinomio(p5);
    printf("P6: "); mostrarPolinomio(p6);

    Polinomio* producto = multiplicarPolinomios(p5, p6);
    printf("P5*P6: "); mostrarPolinomio(producto);
    printf("Esperado: x^2-1\n");

    printf("\n=== CASO 6: Evaluacion ===\n");
    Polinomio* p7 = crearPolinomio();
    insertarTermino(p7, 3, 2);
    insertarTermino(p7, 2, 1);
    insertarTermino(p7, 1, 0);
    printf("P7: "); mostrarPolinomio(p7);
    printf("P7(2) = %.2f\n", evaluarPolinomio(p7, 2));
    printf("Esperado: 17\n");

    printf("\n=== Caso 7: Conversion a cadena ===\n");
    char* cadena = polinomioToString(p1);
    printf("Cadena: %s\n", cadena);
    free(cadena);

    printf("\n=== CASO 8: Destruir polinomio ===\n");
    Polinomio* p8 = crearPolinomio();
    insertarTermino(p8, 5, 3);
    insertarTermino(p8, 2, 1);
    printf("Antes de destruir: "); mostrarPolinomio(p8);
    destruirPolinomio(p8);
    printf("Polinomio destruido exitosamente\n");

    return 0;
}