#include "polinomio.h"

Polinomio* crearPolinomio() {
    Polinomio *p = (Polinomio*)malloc(sizeof(Polinomio));
    if (p == NULL) {
        printf("No se pudo reservar memoria para el polinomio xD\n");
        return NULL;
    } else {
        p->cabeza = NULL;
        p->cola = NULL;
        p->numTerminos = 0;
    }
    return p;
}

void insertarTermino(Polinomio* p, float coeficiente, int exponente) {
    if (p == NULL) return;

    Nodo* actual = p->cabeza;

    while (actual != NULL) {
        if (actual->termino.exponente == exponente) {
            actual->termino.coeficiente += coeficiente;
            if (actual->termino.coeficiente == 0)
                eliminarTermino(p, exponente);
            return;
        }
        actual = actual->siguiente;
    }

    Nodo* nuevo = (Nodo*) malloc(sizeof(Nodo));
    if (nuevo == NULL) return;
    nuevo->termino.coeficiente = coeficiente;
    nuevo->termino.exponente   = exponente;
    nuevo->siguiente = NULL;
    nuevo->anterior  = NULL;
    p->numTerminos++;

    if (p->cabeza == NULL) {
        p->cabeza = nuevo;
        p->cola   = nuevo;
        return;
    }

    if (exponente > p->cabeza->termino.exponente) {
        nuevo->siguiente = p->cabeza;
        p->cabeza->anterior = nuevo;
        p->cabeza = nuevo;
        return;
    }

    actual = p->cabeza;
    while (actual->siguiente != NULL && actual->siguiente->termino.exponente > exponente) {
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente;
    nuevo->anterior = actual;

    if (actual->siguiente != NULL)
        actual->siguiente->anterior = nuevo;
    else
        p->cola = nuevo;

    actual->siguiente = nuevo;
}

void eliminarTermino(Polinomio* p, int exponente) {
    if (p == NULL || p->cabeza == NULL) return;

    Nodo* actual = p->cabeza;
    while (actual != NULL && actual->termino.exponente != exponente) {
        actual = actual->siguiente;
    }

    if (actual == NULL) return;

    if (actual->anterior != NULL)
        actual->anterior->siguiente = actual->siguiente;
    else
        p->cabeza = actual->siguiente;

    if (actual->siguiente != NULL)
        actual->siguiente->anterior = actual->anterior;
    else
        p->cola = actual->anterior;

    free(actual);
    p->numTerminos--;
}

float potencia(float base, int exp) { // funcion que remplaza pow con la libreria math.h
    float resultado = 1.0;
    for (int i = 0; i < exp; i++)
        resultado *= base;
    return resultado;
}

float evaluarPolinomio(Polinomio* p, float x) {
    if (p == NULL || p->cabeza == NULL) return 0.0f;

    float resultado = 0.0f;
    Nodo* actual = p->cabeza;

    while (actual != NULL) {
        resultado += actual->termino.coeficiente * potencia(x, actual->termino.exponente);
        actual = actual->siguiente;
    }

    return resultado;
}

Polinomio* sumarPolinomios(Polinomio* p1, Polinomio* p2) {
    Polinomio* resultado = crearPolinomio();
    if (resultado == NULL) return NULL;

    Nodo* actual = p1->cabeza;
    while (actual != NULL) {
        insertarTermino(resultado, actual->termino.coeficiente, actual->termino.exponente);
        actual = actual->siguiente;
    }

    actual = p2->cabeza;
    while (actual != NULL) {
        insertarTermino(resultado, actual->termino.coeficiente, actual->termino.exponente);
        actual = actual->siguiente;
    }

    return resultado;
}

Polinomio* multiplicarPolinomios(Polinomio* p1, Polinomio* p2) {
    Polinomio* resultado = crearPolinomio();
    if (resultado == NULL) return NULL;

    Nodo* nodo1 = p1->cabeza;
    while (nodo1 != NULL) {
        Nodo* nodo2 = p2->cabeza;
        while (nodo2 != NULL) {
            insertarTermino(resultado, nodo1->termino.coeficiente * nodo2->termino.coeficiente, nodo1->termino.exponente   + nodo2->termino.exponente);
            nodo2 = nodo2->siguiente;
        }
        nodo1 = nodo1->siguiente;
    }

    return resultado;
}

void destruirPolinomio(Polinomio* p) {
    if (p == NULL) return;

    Nodo* actual = p->cabeza;
    while (actual != NULL) {
        Nodo* temp = actual->siguiente;
        free(actual);
        actual = temp;
    }
    free(p);
}

void mostrarPolinomio(Polinomio* p) {
    if (p == NULL || p->cabeza == NULL) {
        printf("0\n");
        return;
    }

    Nodo* actual  = p->cabeza;
    int   primero = 1;

    while (actual != NULL) {
        float coef = actual->termino.coeficiente;
        int   exp  = actual->termino.exponente;
        int esPositivo = (coef ==  1);
        int esNegativo = (coef == -1);

        if (!primero && coef > 0)
            printf("+");
        primero = 0;

        if (exp == 0) {
            printf("%.g", coef);
        } else if (exp == 1) {
            if (esPositivo) printf("x");
            else if (esNegativo) printf("-x");
            else printf("%.gx", coef);
        } else {
            if (esPositivo) printf("x^%d", exp);
            else if (esNegativo) printf("-x^%d", exp);
            else printf("%.gx^%d", coef, exp);
        }

        actual = actual->siguiente;
    }
    printf("\n");
}

char* polinomioToString(Polinomio* p) {
    char* cadena = (char*) malloc(256);
    cadena[0] = '\0';

    if (p == NULL || p->cabeza == NULL) {
        strcat(cadena, "0");
        return cadena;
    }

    Nodo* actual  = p->cabeza;
    int primero = 1;
    char temp[64];

    while (actual != NULL) {
        float coef = actual->termino.coeficiente;
        int exp = actual->termino.exponente;
        int esPositivo = (coef ==  1);
        int esNegativo = (coef == -1);

        if (!primero && coef > 0)
            strcat(cadena, "+");
        primero = 0;

        if (exp == 0) {
            sprintf(temp, "%.g", coef);
        } else if (exp == 1) {
            if (esPositivo) sprintf(temp, "x");
            else if (esNegativo) sprintf(temp, "-x");
            else sprintf(temp, "%.gx", coef);
        } else {
            if (esPositivo) sprintf(temp, "x^%d", exp);
            else if (esNegativo) sprintf(temp, "-x^%d", exp);
            else sprintf(temp, "%.gx^%d", coef, exp);
        }

        strcat(cadena, temp);
        actual = actual->siguiente;
    }

    return cadena;
}
