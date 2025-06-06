#include <stdio.h>
#include <time.h>
#include "vector.h"

void mostrarEntero(void* elemento)
{
    printf("%d\n", *(int*)elemento);
}

int esMenor(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

int esPar(const void* a)
{
    return *(int*)a % 2 == 0 ? 1 : 0;
}

void* sumarEnteros(void* a, void* b)
{
    int* resultado = malloc(sizeof(int));

    *resultado = *(int*)a + *(int*)b;

    return resultado;
}

int obtenerNumeroAleatorio()
{
    int numero = (rand() % 10) + 1;

    return numero;
}

int compararEnteros(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int main()
{
    Vector vec;
    srand(time(NULL));
    int buscar = 4;

    crearVector(&vec, sizeof(int));

    for (int i = 0; i < 7; i++)
    {
        int n = obtenerNumeroAleatorio();

        insertarEnVectorAlFinal(&vec, &n);
    }

    ordenarVectorPorSeleccion(&vec, esMenor);
    recorrerVector(&vec, mostrarEntero);

    puts("");

    int* encontro = (int*)busquedaBinariaVector(&vec, &buscar, compararEnteros);

    if (encontro != NULL)
        printf("\nENCONTRADO: %d", *encontro);

    destruirVector(&vec);

    return 0;
}
