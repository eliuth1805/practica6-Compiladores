#ifndef AST_H
#define AST_H

/* Tipos de nodos del árbol */
typedef enum {
    AST_ID,
    AST_DEREFERENCE,
    AST_ASSIGNMENT,
    AST_EXPRESSION
} TipoNodo;

/* Estructura de un nodo */
typedef struct NodoAST {
    TipoNodo tipo;
    char *valor;

    struct NodoAST *izquierda;
    struct NodoAST *derecha;
} NodoAST;

/* Crear nodos */
NodoAST *crear_nodo(TipoNodo tipo, const char *valor);

/* Construcción de nodos compuestos */
NodoAST *crear_nodo_compuesto(
    TipoNodo tipo,
    const char *valor,
    NodoAST *izquierda,
    NodoAST *derecha
);

/* Mostrar el árbol */
void imprimir_ast(const NodoAST *raiz, int nivel);

/* Liberar memoria */
void liberar_ast(NodoAST *raiz);

#endif
