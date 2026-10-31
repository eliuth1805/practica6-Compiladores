#include "tablas.h"

/*
 * Tabla ACTION
 *
 * Terminales:
 * 0 = *
 * 1 = id
 * 2 = =
 * 3 = $
 *
 * SHIFT: desplazar al estado indicado.
 * REDUCE: reducir mediante la producción indicada.
 * ACCEPT: aceptar la cadena.
 * ERROR: acción no definida.
 */

const Accion ACTION[NUM_ESTADOS][NUM_TERMINALES] = {

    /* Estado 0 */
    {
        {ACTION_SHIFT, 4},
        {ACTION_SHIFT, 5},
        {ACTION_ERROR, 0},
        {ACTION_ERROR, 0}
    },

    /* Estado 1 */
    {
        {ACTION_ERROR, 0},
        {ACTION_ERROR, 0},
        {ACTION_ERROR, 0},
        {ACTION_ACCEPT, 0}
    },

    /* Estado 2 */
    {
        {ACTION_ERROR, 0},
        {ACTION_ERROR, 0},
        {ACTION_SHIFT, 6},
        {ACTION_REDUCE, 6}
    },

    /* Estado 3 */
    {
        {ACTION_ERROR, 0},
        {ACTION_ERROR, 0},
        {ACTION_ERROR, 0},
        {ACTION_REDUCE, 3}
    },

    /* Estado 4 */
    {
        {ACTION_SHIFT, 4},
        {ACTION_SHIFT, 5},
        {ACTION_ERROR, 0},
        {ACTION_ERROR, 0}
    },

    /* Estado 5 */
    {
        {ACTION_ERROR, 0},
        {ACTION_ERROR, 0},
        {ACTION_REDUCE, 5},
        {ACTION_REDUCE, 5}
    },

    /* Estado 6 */
    {
        {ACTION_SHIFT, 4},
        {ACTION_SHIFT, 5},
        {ACTION_ERROR, 0},
        {ACTION_ERROR, 0}
    },

    /* Estado 7 */
    {
        {ACTION_ERROR, 0},
        {ACTION_ERROR, 0},
        {ACTION_REDUCE, 4},
        {ACTION_REDUCE, 4}
    },

    /* Estado 8 */
    {
        {ACTION_ERROR, 0},
        {ACTION_ERROR, 0},
        {ACTION_REDUCE, 6},
        {ACTION_REDUCE, 6}
    },

    /* Estado 9 */
    {
        {ACTION_ERROR, 0},
        {ACTION_ERROR, 0},
        {ACTION_ERROR, 0},
        {ACTION_REDUCE, 2}
    }
};


/*
 * Tabla GOTO
 *
 * No terminales:
 * 0 = S
 * 1 = L
 * 2 = R
 */

const int GOTO[NUM_ESTADOS][NUM_NO_TERMINALES] = {

    /* Estado 0 */
    {1, 2, 3},

    /* Estado 1 */
    {-1, -1, -1},

    /* Estado 2 */
    {-1, -1, -1},

    /* Estado 3 */
    {-1, -1, -1},

    /* Estado 4 */
    {-1, 8, 7},

    /* Estado 5 */
    {-1, -1, -1},

    /* Estado 6 */
    {-1, 8, 9},

    /* Estado 7 */
    {-1, -1, -1},

    /* Estado 8 */
    {-1, -1, -1},

    /* Estado 9 */
    {-1, -1, -1}
};


/*
 * Producciones de la gramática.
 *
 * 1. S' -> S
 * 2. S  -> L = R
 * 3. S  -> R
 * 4. L  -> * R
 * 5. L  -> id
 * 6. R  -> L
 *
 * La producción 0 es una posición reservada.
 */

const Produccion PRODUCCIONES[NUM_PRODUCCIONES] = {

    {NT_S, 0},  /* Reservada */
    {NT_S, 1},  /* S' -> S */
    {NT_S, 3},  /* S -> L = R */
    {NT_S, 1},  /* S -> R */
    {NT_L, 2},  /* L -> * R */
    {NT_L, 1},  /* L -> id */
    {NT_R, 1}   /* R -> L */
};
