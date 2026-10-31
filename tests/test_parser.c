#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "parser.h"
#include "ast.h"

/* Comprueba cadenas válidas y el tipo de AST generado. */
void probar_valida(
    const char *nombre,
    const Terminal *tokens,
    int cantidad,
    TipoNodo tipo_esperado
) {
    NodoAST *arbol = NULL;
    int estado_final = -1;

    ResultadoParser resultado = analizar_cadena(
        tokens,
        cantidad,
        &arbol,
        &estado_final
    );

    assert(resultado == PARSER_VALIDO);
    assert(arbol != NULL);
    assert(arbol->tipo == tipo_esperado);
    assert(estado_final >= 0);

    printf("[CORRECTO] %s (Estado final: I%d)\n",
           nombre, estado_final);

    liberar_ast(arbol);
}

/* Comprueba cadenas inválidas. */
void probar_invalida(
    const char *nombre,
    const Terminal *tokens,
    int cantidad
) {
    NodoAST *arbol = NULL;
    int estado_final = -1;

    ResultadoParser resultado = analizar_cadena(
        tokens,
        cantidad,
        &arbol,
        &estado_final
    );

    assert(resultado == PARSER_INVALIDO);
    assert(arbol == NULL);
    assert(estado_final >= 0);

    printf("[CORRECTO] %s (Estado final: I%d)\n",
           nombre, estado_final);
}

int main(void) {

    /* Cadenas válidas */
    const Terminal v1[] = {TOK_ID};
    const Terminal v2[] = {TOK_ID, TOK_EQUAL, TOK_ID};
    const Terminal v3[] = {TOK_STAR, TOK_ID};
    const Terminal v4[] = {TOK_STAR, TOK_ID, TOK_EQUAL, TOK_ID};
    const Terminal v5[] = {TOK_ID, TOK_EQUAL, TOK_STAR, TOK_ID};

    /* Cadenas inválidas */
    const Terminal i1[] = {TOK_ID, TOK_EQUAL};
    const Terminal i2[] = {TOK_EQUAL, TOK_ID};
    const Terminal i3[] = {TOK_ID, TOK_EQUAL, TOK_EQUAL, TOK_ID};
    const Terminal i4[] = {TOK_STAR, TOK_STAR};
    const Terminal i5[] = {
        TOK_ID, TOK_EQUAL, TOK_ID, TOK_EQUAL, TOK_ID
    };

    printf("\nPRUEBAS DE CADENAS VALIDAS\n");

    probar_valida("id", v1, 1, AST_ID);
    probar_valida("id=id", v2, 3, AST_ASSIGNMENT);
    probar_valida("*id", v3, 2, AST_DEREFERENCE);
    probar_valida("*id=id", v4, 4, AST_ASSIGNMENT);
    probar_valida("id=*id", v5, 4, AST_ASSIGNMENT);

    printf("\nPRUEBAS DE CADENAS INVALIDAS\n");

    probar_invalida("id=", i1, 2);
    probar_invalida("=id", i2, 2);
    probar_invalida("id==id", i3, 4);
    probar_invalida("**", i4, 2);
    probar_invalida("id=id=id", i5, 5);

    printf("\nTodas las pruebas finalizaron correctamente.\n");

    return 0;
}
