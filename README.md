# Práctica 6: Parser Canónico LR(1) y Compactación LALR(1)

## Descripción

Este proyecto implementa un analizador sintáctico LALR(1) en lenguaje C. Su función es reconocer cadenas que pertenecen a una gramática determinada y construir un árbol de sintaxis abstracta (AST) cuando la cadena es válida.

El programa utiliza tablas ACTION y GOTO construidas a partir del autómata LALR(1).

## Gramática utilizada

La gramática implementada es:

1. S' → S
2. S → L = R
3. S → R
4. L → * R
5. L → id
6. R → L

Terminales: `=`, `*`, `id` y `$`.

## Estructura del proyecto

```text
Practica6_Compiladores/
├── docs/
├── include/
│   ├── ast.h
│   ├── parser.h
│   └── tablas.h
├── src/
│   ├── ast.c
│   ├── main.c
│   ├── parser.c
│   └── tablas.c
├── tests/
│   └── test_parser.c
├── Makefile
└── README.md
```

## Requisitos

- GCC
- GNU Make
- Sistema operativo Linux

## Compilación

Para compilar el programa:

```bash
make
```

Para eliminar los archivos generados:

```bash
make clean
```

## Ejecución

Para iniciar el analizador:

```bash
./parser
```

El programa solicita una cadena y determina si pertenece a la gramática.

Cuando la cadena es válida, muestra el estado final de aceptación y construye su árbol sintáctico.

Cuando es inválida, muestra el estado donde se detectó el error.

## Pruebas automatizadas

Para compilar y ejecutar las pruebas:

```bash
make test
```

Las pruebas comprueban cinco cadenas válidas y cinco inválidas, además del tipo de AST generado para las cadenas aceptadas.

## Ejemplos

Cadenas válidas:

```text
id
id=id
*id
*id=id
id=*id
```

Cadenas inválidas:

```text
id=
=id
id==id
**
id=id=id
```
## Autor

Jesús Eliuth Martínez Mendoza

Asignatura: Compiladores
Práctica 6: Parser Canónico LR(1) y Compactación LALR(1)
