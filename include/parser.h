#ifndef PARSER_H
#define PARSER_H

#include "tablas.h"
#include "ast.h"

#define MAX_PILA 1000

typedef enum {
    PARSER_VALIDO,
    PARSER_INVALIDO
} ResultadoParser;

/*
 * Analiza una cadena de tokens y construye su AST.
 * Los tokens no deben incluir TOK_EOF.
 * El árbol resultante se entrega mediante arbol_salida.
 * El estado final se entrega mediante estado_final.
 */
ResultadoParser analizar_cadena(
    const Terminal *tokens,
    int cantidad_tokens,
    NodoAST **arbol_salida,
    int *estado_final
);

#endif
