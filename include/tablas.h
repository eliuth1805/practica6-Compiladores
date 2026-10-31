#ifndef TABLAS_H
#define TABLAS_H

#define NUM_ESTADOS 10
#define NUM_TERMINALES 4
#define NUM_NO_TERMINALES 3
#define NUM_PRODUCCIONES 7

/* Terminales */
typedef enum {
    TOK_STAR,
    TOK_ID,
    TOK_EQUAL,
    TOK_EOF
} Terminal;

/* No terminales */
typedef enum {
    NT_S,
    NT_L,
    NT_R
} NoTerminal;

/* Tipos de acciones del parser */
typedef enum {
    ACTION_ERROR,
    ACTION_SHIFT,
    ACTION_REDUCE,
    ACTION_ACCEPT
} TipoAccion;

/* Estructura de una acción */
typedef struct {
    TipoAccion tipo;
    int valor;
} Accion;

/* Estructura de una producción */
typedef struct {
    NoTerminal izquierda;
    int longitud;
} Produccion;

/* Tablas del parser */
extern const Accion ACTION[NUM_ESTADOS][NUM_TERMINALES];

extern const int GOTO[NUM_ESTADOS][NUM_NO_TERMINALES];

extern const Produccion PRODUCCIONES[NUM_PRODUCCIONES];

#endif
