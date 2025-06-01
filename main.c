#include <stdio.h>
#include "vector.h"

void mostrarEntero(void* elemento)
{
    printf("%d\n", *(int*)elemento);
}

int esMenor(const void* a, const void* b)
{
    return *(int*)a < *(int*)b;
}

int main()
{
    Vector vec;
    int i;
    int numeros[] = {1, 4, 7};

    crearVector(&vec, sizeof(int));

    for (i = 1; i < 10; i++)
    {
        insertarEnVectorAlFinal(&vec, &i);
    }

    insertarEnVectorPorPosicion(&vec, 1, &numeros[0]);
    insertarEnVectorPorPosicion(&vec, 1, &numeros[0]);
    insertarEnVectorPorPosicion(&vec, 5, &numeros[1]);
    insertarEnVectorPorPosicion(&vec, 6, &numeros[1]);
    insertarEnVectorPorPosicion(&vec, 8, &numeros[2]);

    recorrerVector(&vec, mostrarEntero);

    puts("");

    eliminarPrimeraAparicionElementoEnVector(&vec, &numeros[0]);
    eliminarPrimeraAparicionElementoEnVector(&vec, &numeros[1]);
    eliminarPrimeraAparicionElementoEnVector(&vec, &numeros[2]);

    recorrerVector(&vec, mostrarEntero);

    destruirVector(&vec);

    return 0;
}
