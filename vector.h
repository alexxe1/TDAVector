#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <stdlib.h>

#define TAM_BASE 4

typedef struct
{
    void* datos;
    size_t ce;
    size_t tamMaximo;
    size_t tamElemento;
} Vector;

int crearVector(Vector* vec, size_t tamElemento);
int redimensionarVector(Vector* vec, size_t nuevaCantidadElementos);
void destruirVector(Vector* vec);

int modificarElementoVector(Vector* vec, size_t posicion, void* nuevoElemento);
void recorrerVector(Vector* vec, void (*funcion)(void* elemento));

int insertarEnVectorAlFinal(Vector* vec, void* elemento);
int insertarEnVectorPorPosicion(Vector* vec, size_t posicion, void* elemento);
int insertarEnVectorOrdenado(Vector* vec, void* elemento, int (*cmp)(const void* a, const void* b));

int eliminarElementoEnVectorPorPosicion(Vector* vec, size_t posicion);
int eliminarPrimeraAparicionElementoEnVector(Vector* vec, void* elemento);

int ordenarVectorPorSeleccion(Vector* vec, int (*comparar)(const void* a, const void* b));
void* obtenerMinimo(Vector* vec, int (*comparar)(const void* a, const void* b));

void* copiarMemoria(void* destino, void* origen, size_t cantidad);
int compararMemoria(const void* memoria1, const void* memoria2, size_t cantidad);
int intercambiarMemoria(void* memoria1, void* memoria2, size_t cantidad);

#endif  // VECTOR_H_INCLUDED
