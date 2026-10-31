#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

/*
 * Copia una cadena reservando memoria.
 */
static char *copiar_cadena(const char *texto) {
    if (texto == NULL) {
        return NULL;
    }

    size_t longitud = strlen(texto) + 1;
    char *copia = malloc(longitud);

    if (copia == NULL) {
        return NULL;
    }

    memcpy(copia, texto, longitud);

    return copia;
}

/*
 * Crea un nodo individual.
 */
NodoAST *crear_nodo(TipoNodo tipo, const char *valor) {
    NodoAST *nuevo = malloc(sizeof(NodoAST));

    if (nuevo == NULL) {
        return NULL;
    }

    nuevo->tipo = tipo;
    nuevo->valor = copiar_cadena(valor);
    nuevo->izquierda = NULL;
    nuevo->derecha = NULL;

    if (valor != NULL && nuevo->valor == NULL) {
        free(nuevo);
        return NULL;
    }

    return nuevo;
}

/*
 * Crea un nodo con hijos.
 */
NodoAST *crear_nodo_compuesto(
    TipoNodo tipo,
    const char *valor,
    NodoAST *izquierda,
    NodoAST *derecha
) {
    NodoAST *nuevo = crear_nodo(tipo, valor);

    if (nuevo == NULL) {
        return NULL;
    }

    nuevo->izquierda = izquierda;
    nuevo->derecha = derecha;

    return nuevo;
}

/*
 * Imprime el árbol sintáctico.
 */
void imprimir_ast(const NodoAST *raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }

    switch (raiz->tipo) {

        case AST_ID:
            printf("ID: %s\n", raiz->valor);
            break;

        case AST_DEREFERENCE:
            printf("DEREFERENCE: %s\n",
                   raiz->valor != NULL ? raiz->valor : "*");
            break;

        case AST_ASSIGNMENT:
            printf("ASSIGNMENT\n");
            break;

        case AST_EXPRESSION:
            printf("EXPRESSION\n");
            break;
    }

    imprimir_ast(raiz->izquierda, nivel + 1);
    imprimir_ast(raiz->derecha, nivel + 1);
}

/*
 * Libera recursivamente la memoria del árbol.
 */
void liberar_ast(NodoAST *raiz) {
    if (raiz == NULL) {
        return;
    }

    liberar_ast(raiz->izquierda);
    liberar_ast(raiz->derecha);

    free(raiz->valor);
    free(raiz);
}
