#include "vector.h"

int crearVector(Vector* vec, size_t tamElemento)
{
    vec->datos = malloc(TAM_BASE * tamElemento);

    if (!vec->datos)
    {
        return 0;
    }

    vec->ce = 0;
    vec->tamMaximo = TAM_BASE;
    vec->tamElemento = tamElemento;

    return 1;
}

int redimensionarVector(Vector* vec, size_t nuevaCantidadElementos)
{
    void* nuevaMemoria = realloc(vec->datos, nuevaCantidadElementos * vec->tamElemento);

    if (!nuevaMemoria)
    {
        return 0;
    }

    vec->datos = nuevaMemoria;
    vec->tamMaximo = nuevaCantidadElementos;

    return 1;
}

int modificarElementoVector(Vector* vec, size_t posicion, void* nuevoElemento)
{
    if (posicion >= vec->ce)
    {
        return 0;
    }

    void* destino = (char*)vec->datos + (posicion * vec->tamElemento);

    copiarMemoria(destino, nuevoElemento, vec->tamElemento);

    return 1;
}

void recorrerVector(Vector* vec, void (*funcion)(void* elemento))
{
    void* elementoActual = vec->datos;
    size_t i;

    for (i = 0; i < vec->ce; i++)
    {
        funcion(elementoActual);
        elementoActual = (char*)elementoActual + vec->tamElemento;
    }
}

void destruirVector(Vector* vec)
{
    free(vec->datos);

    vec->ce = 0;
    vec->tamMaximo = 0;
    vec->tamElemento = 0;
}

int insertarEnVectorAlFinal(Vector* vec, void* elemento)
{
    if (vec->ce == vec->tamMaximo)
    {
        if (!redimensionarVector(vec, vec->tamMaximo + TAM_BASE))
        {
            return 0;
        }
    }

    void* destino = (char*)vec->datos + (vec->ce * vec->tamElemento);

    copiarMemoria(destino, elemento, vec->tamElemento);

    vec->ce++;

    return 1;
}

int insertarEnVectorPorPosicion(Vector* vec, size_t posicion, void* elemento)
{
    if (posicion > vec->ce)
    {
        return 0;
    }

    if (posicion == vec->ce)
    {
        return insertarEnVectorAlFinal(vec, elemento);
    }

    if (vec->ce == vec->tamMaximo)
    {
        if (!redimensionarVector(vec, vec->tamMaximo + TAM_BASE))
        {
            return 0;
        }
    }

    void* ini = (char*)vec->datos + (posicion * vec->tamElemento);
    void* fin = (char*)vec->datos + (vec->ce * vec->tamElemento);

    while (ini < fin)
    {
        copiarMemoria(fin, (char*)fin - vec->tamElemento, vec->tamElemento);

        fin -= vec->tamElemento;
    }

    copiarMemoria(ini, elemento, vec->tamElemento);
    vec->ce++;

    return 1;
}

int insertarEnVectorOrdenado(Vector* vec, void* elemento, int (*cmp)(const void* a, const void* b))
{
    if (vec->ce == vec->tamMaximo)
    {
        if (!redimensionarVector(vec, vec->tamMaximo + TAM_BASE))
        {
            return 0;
        }
    }

    void* ini = (char*)vec->datos;
    void* fin = (char*)vec->datos + (vec->ce * vec->tamElemento);

    while (ini < fin && cmp(elemento, (char*)fin - vec->tamElemento) > 0)
    {
        copiarMemoria(fin, (char*)fin - vec->tamElemento, vec->tamElemento);

        fin -= vec->tamElemento;
    }

    copiarMemoria(fin, elemento, vec->tamElemento);
    vec->ce++;

    return 1;
}

int eliminarElementoEnVectorPorPosicion(Vector* vec, size_t posicion)
{
    if (posicion >= vec->ce)
    {
        return 0;
    }

    void* ini = (char*)vec->datos + (posicion * vec->tamElemento);
    void* fin = (char*)vec->datos + ((vec->ce - 1) * vec->tamElemento);

    while (ini < fin)
    {
        copiarMemoria(ini, (char*)ini + vec->tamElemento, vec->tamElemento);

        ini += vec->tamElemento;
    }

    vec->ce--;

    return 1;
}

int eliminarPrimeraAparicionElementoEnVector(Vector* vec, void* elemento)
{
    void* ini = (char*)vec->datos;
    void* fin = (char*)vec->datos + vec->ce * vec->tamElemento;
    int encontrado = 0;

    while (ini < fin && encontrado == 0)
    {
        if (compararMemoria(ini, elemento, vec->tamElemento) == 0)
        {
            encontrado = 1;
        }
        else
        {
            ini += vec->tamElemento;
        }
    }

    if (encontrado == 0)
    {
        return 0;
    }

    while (ini < fin)
    {
        copiarMemoria(ini, (char*)ini + vec->tamElemento, vec->tamElemento);

        ini += vec->tamElemento;
    }

    vec->ce--;

    return 1;
}

void ordenarVectorPorSeleccion(Vector* vec, int (*comparar)(const void* a, const void* b))
{
    Vector vecAux = *vec;
    void* ini = (char*)vec->datos;
    const void* fin = (char*)vec->datos + ((vec->ce - 1) * vec->tamElemento);
    void* actual;

    while (ini < fin)
    {
        actual = obtenerMinimo(&vecAux, comparar);

        if (compararMemoria(ini, actual, vec->tamElemento) != 0)
        {
            intercambiarMemoria(ini, actual, vec->tamElemento);
        }

        ini += vec->tamElemento;
        vecAux.datos = (char*)vecAux.datos + vecAux.tamElemento;
        vecAux.ce--;
    }
}

void* obtenerMinimo(Vector* vec, int (*comparar)(const void* a, const void* b))
{
    void* minimo = vec->datos;
    size_t i = 0;
    void* actual;

    for (i = 1; i < vec->ce; i++)
    {
        actual = (char*)vec->datos + i * vec->tamElemento;

        if (comparar(actual, minimo) < 0)
        {
            minimo = actual;
        }
    }

    return minimo;
}

void filtrarVector(Vector* vec, int (*comparar)(const void* a))
{
    void* lectura = (char*)vec->datos;
    void* escritura = (char*)vec->datos;
    void* fin = (char*)vec->datos + (vec->ce * vec->tamElemento);

    while (lectura < fin)
    {
        if (comparar(lectura) == 1)
        {
            if (lectura != escritura)
            {
                copiarMemoria(escritura, lectura, vec->tamElemento);
            }

            escritura += vec->tamElemento;
        }
        else
        {
            vec->ce--;
        }

        lectura += vec->tamElemento;
    }
}

void* reducirVector(Vector* vec, void* (*funcion)(void* a, void* b))
{
    void* ini = (char*)vec->datos;
    void* fin = (char*)vec->datos + (vec->ce * vec->tamElemento);
    void* acumulador = vec->datos;

    while (ini < fin)
    {
        acumulador = funcion(acumulador, ini);
        ini += vec->tamElemento;
    }

    return acumulador;
}

void* busquedaBinariaVector(Vector* vec, void* elemento, int (*comparar)(const void* a, const void* b))
{
    if (vec->ce == 0)
    {
        return NULL;
    }

    char* ini = (char*)vec->datos;
    char* fin = (char*)vec->datos + (vec->ce - 1) * vec->tamElemento;
    size_t numElementos;
    char* medio;
    int comparacion;

    while (ini <= fin)
    {
        numElementos = (fin - ini) / vec->tamElemento;
        medio = ini + (numElementos / 2) * vec->tamElemento;

        comparacion = comparar(medio, elemento);

        if (comparacion == 0)
        {
            return medio;
        }
        else if (comparacion < 0)
        {
            ini = medio + vec->tamElemento;
        }
        else
        {
            fin = medio - vec->tamElemento;
        }
    }

    return NULL;
}

void* copiarMemoria(void* destino, void* origen, size_t cantidad)
{
    if (cantidad == 0)
    {
        return 0;
    }

    unsigned char* pDestino = (unsigned char*)destino;
    unsigned char* pOrigen = (unsigned char*)origen;

    while (cantidad > 0)
    {
        *pDestino = *pOrigen;

        pDestino++;
        pOrigen++;

        cantidad--;
    }

    return pDestino;
}

int compararMemoria(const void* memoria1, const void* memoria2, size_t cantidad)
{
    if (cantidad == 0)
    {
        return 0;
    }

    unsigned char* pMemoria1 = (unsigned char*)memoria1;
    unsigned char* pMemoria2 = (unsigned char*)memoria2;

    while (cantidad > 0 && *pMemoria1 == *pMemoria2)
    {
        pMemoria1++;
        pMemoria2++;

        cantidad--;
    }

    return cantidad == 0 ? 0 : *pMemoria1 - *pMemoria2;
}

int intercambiarMemoria(void* memoria1, void* memoria2, size_t cantidad)
{
    void* aux = malloc(cantidad);

    if (aux == NULL)
    {
        return 0;
    }

    copiarMemoria(aux, memoria1, cantidad);
    copiarMemoria(memoria1, memoria2, cantidad);
    copiarMemoria(memoria2, aux, cantidad);

    free(aux);

    return 1;
}
