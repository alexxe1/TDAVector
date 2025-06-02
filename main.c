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

int obtenerNumeroAleatorio()
{
    int numero = (rand() % 10) + 1;

    return numero;
}

int main()
{
    Vector vec;
    srand(time(NULL));

    crearVector(&vec, sizeof(int));

    for (int i = 0; i < 7; i++)
    {
        int n = obtenerNumeroAleatorio();

        insertarEnVectorAlFinal(&vec, &n);
    }

    recorrerVector(&vec, mostrarEntero);

    puts("");

    ordenarVectorPorSeleccion(&vec, esMenor);

    recorrerVector(&vec, mostrarEntero);

    destruirVector(&vec);

    return 0;
}
