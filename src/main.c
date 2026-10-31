#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"
#include "ast.h"

#define MAX_ENTRADA 1024
#define MAX_TOKENS 256

/*
 * Analizador léxico sencillo.
 * Reconoce identificadores, *, = y espacios.
 */
static int analizar_lexico(
    const char *entrada,
    Terminal *tokens,
    int *cantidad
) {
    int posicion = 0;
    *cantidad = 0;

    while (entrada[posicion] != '\0') {

        if (isspace((unsigned char)entrada[posicion])) {
            posicion++;
            continue;
        }

        if (*cantidad >= MAX_TOKENS) {
            return 0;
        }

        if (entrada[posicion] == '*') {
            tokens[(*cantidad)++] = TOK_STAR;
            posicion++;
        }
        else if (entrada[posicion] == '=') {
            tokens[(*cantidad)++] = TOK_EQUAL;
            posicion++;
        }
        else if (isalpha((unsigned char)entrada[posicion]) ||
                 entrada[posicion] == '_') {

            while (isalnum((unsigned char)entrada[posicion]) ||
                   entrada[posicion] == '_') {
                posicion++;
            }

            tokens[(*cantidad)++] = TOK_ID;
        }
        else {
            return 0;
        }
    }

    return 1;
}

/*
 * Función principal.
 */
int main(void) {
    char entrada[MAX_ENTRADA];
    Terminal tokens[MAX_TOKENS];
    int cantidad_tokens;
    int estado_final = -1;

    printf("====================================\n");
    printf("       PARSER LALR(1) - PRACTICA 6\n");
    printf("====================================\n");

    printf("\nIntroduce una cadena: ");

    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return 1;
    }

    if (!analizar_lexico(entrada, tokens, &cantidad_tokens)) {
        printf("\nERROR: Se encontraron caracteres no validos.\n");
        return 1;
    }

    NodoAST *arbol = NULL;

    ResultadoParser resultado = analizar_cadena(
        tokens,
        cantidad_tokens,
        &arbol,
        &estado_final
    );

    printf("\n========== RESULTADO ==========\n");

    if (estado_final >= 0) {
        printf("Estado final: I%d\n", estado_final);
    } else {
        printf("Estado final: No determinado\n");
    }

    if (resultado == PARSER_VALIDO) {

        printf("Cadena VALIDA.\n");

        printf("\nArbol sintactico (AST):\n");
        imprimir_ast(arbol, 0);

        liberar_ast(arbol);

    } else {

        printf("Cadena INVALIDA.\n");
    }

    printf("===============================\n");

    return 0;
}
