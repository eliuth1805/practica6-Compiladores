#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

/* Inicializa la pila de estados. */
static void inicializar_pila(int *pila, int *tope) {
    *tope = 0;
    pila[0] = 0;
}

/* Inserta un estado en la pila. */
static int apilar(int *pila, int *tope, int estado) {
    if (*tope >= MAX_PILA - 1) {
        return 0;
    }

    pila[++(*tope)] = estado;
    return 1;
}

/* Libera los nodos de la pila semántica. */
static void liberar_pila_ast(NodoAST **pila, int tope) {
    for (int i = 0; i <= tope; i++) {
        liberar_ast(pila[i]);
        pila[i] = NULL;
    }
}

/* Finaliza un análisis inválido. */
static ResultadoParser error_parser(
    NodoAST **pila_ast,
    int tope,
    int *estado_final,
    int estado
) {
    liberar_pila_ast(pila_ast, tope);

    if (estado_final != NULL) {
        *estado_final = estado;
    }

    return PARSER_INVALIDO;
}

/*
 * Ejecuta el análisis sintáctico LALR(1)
 * y construye el árbol sintáctico.
 */
ResultadoParser analizar_cadena(
    const Terminal *tokens,
    int cantidad_tokens,
    NodoAST **arbol_salida,
    int *estado_final
) {
    int pila_estados[MAX_PILA];
    NodoAST *pila_ast[MAX_PILA] = {NULL};

    int tope = 0;
    int posicion = 0;
    int iteraciones = 0;

    if (estado_final != NULL) {
        *estado_final = -1;
    }

    if (arbol_salida == NULL) {
        return PARSER_INVALIDO;
    }

    *arbol_salida = NULL;

    if (cantidad_tokens < 0 ||
        (cantidad_tokens > 0 && tokens == NULL)) {
        return PARSER_INVALIDO;
    }

    inicializar_pila(pila_estados, &tope);

    while (iteraciones < 10000) {
        iteraciones++;

        int estado = pila_estados[tope];

        Terminal token = (posicion < cantidad_tokens)
                         ? tokens[posicion]
                         : TOK_EOF;

        if (token < TOK_STAR || token > TOK_EOF) {
            return error_parser(
                pila_ast, tope, estado_final, estado
            );
        }

        if (token == TOK_EOF && posicion < cantidad_tokens) {
            return error_parser(
                pila_ast, tope, estado_final, estado
            );
        }

        Accion accion = ACTION[estado][(int)token];

        switch (accion.tipo) {

            case ACTION_SHIFT: {
                NodoAST *nuevo = NULL;

                if (token == TOK_ID) {
                    nuevo = crear_nodo(AST_ID, "id");

                    if (nuevo == NULL) {
                        return error_parser(
                            pila_ast, tope, estado_final, estado
                        );
                    }
                }

                if (!apilar(pila_estados, &tope, accion.valor)) {
                    liberar_ast(nuevo);

                    return error_parser(
                        pila_ast, tope, estado_final, estado
                    );
                }

                pila_ast[tope] = nuevo;
                posicion++;

                break;
            }

            case ACTION_REDUCE: {
                int numero = accion.valor;

                if (numero <= 0 ||
                    numero >= NUM_PRODUCCIONES) {
                    return error_parser(
                        pila_ast, tope, estado_final, estado
                    );
                }

                Produccion produccion = PRODUCCIONES[numero];
                int longitud = produccion.longitud;

                if (longitud > tope) {
                    return error_parser(
                        pila_ast, tope, estado_final, estado
                    );
                }

                NodoAST *nuevo = NULL;

                if (numero == 2) {
                    /* S -> L = R */

                    NodoAST *derecha = pila_ast[tope];
                    NodoAST *izquierda = pila_ast[tope - 2];

                    pila_ast[tope] = NULL;
                    pila_ast[tope - 1] = NULL;
                    pila_ast[tope - 2] = NULL;

                    nuevo = crear_nodo_compuesto(
                        AST_ASSIGNMENT,
                        "=",
                        izquierda,
                        derecha
                    );

                    if (nuevo == NULL) {
                        liberar_ast(izquierda);
                        liberar_ast(derecha);
                    }

                } else if (numero == 4) {
                    /* L -> * R */

                    NodoAST *derecha = pila_ast[tope];

                    pila_ast[tope] = NULL;
                    pila_ast[tope - 1] = NULL;

                    nuevo = crear_nodo_compuesto(
                        AST_DEREFERENCE,
                        "*",
                        derecha,
                        NULL
                    );

                    if (nuevo == NULL) {
                        liberar_ast(derecha);
                    }

                } else if (numero == 3 || numero == 6) {
                    /* S -> R y R -> L */

                    nuevo = pila_ast[tope];
                    pila_ast[tope] = NULL;

                } else if (numero == 5) {
                    /* L -> id */

                    nuevo = pila_ast[tope];
                    pila_ast[tope] = NULL;
                }

                if (nuevo == NULL) {
                    return error_parser(
                        pila_ast, tope - longitud,
                        estado_final, estado
                    );
                }

                tope -= longitud;

                int nuevo_estado =
                    GOTO[pila_estados[tope]][produccion.izquierda];

                if (nuevo_estado < 0 ||
                    nuevo_estado >= NUM_ESTADOS) {
                    liberar_ast(nuevo);

                    return error_parser(
                        pila_ast, tope, estado_final, estado
                    );
                }

                if (!apilar(pila_estados, &tope, nuevo_estado)) {
                    liberar_ast(nuevo);

                    return error_parser(
                        pila_ast, tope, estado_final, estado
                    );
                }

                pila_ast[tope] = nuevo;

                break;
            }

            case ACTION_ACCEPT:
                *arbol_salida = pila_ast[tope];
                pila_ast[tope] = NULL;

                if (estado_final != NULL) {
                    *estado_final = estado;
                }

                return PARSER_VALIDO;

            case ACTION_ERROR:
            default:
                return error_parser(
                    pila_ast, tope, estado_final, estado
                );
        }
    }

    return error_parser(
        pila_ast, tope, estado_final, pila_estados[tope]
    );
}
