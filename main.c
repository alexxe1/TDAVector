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

    reducirVector(&vec, sumarEnteros);

    destruirVector(&vec);

    return 0;
}
