#ifndef MARCA_H_INCLUDED
#define MARCA_H_INCLUDED

typedef struct
{
    int id; // Comienza en 1000
    char descripcion[20];
}eMarca;

#endif // MARCA_H_INCLUDED


int cargarDescripcionMarca(eMarca marcas[], int tamMarca, int idMarca, char descripcion[]);

int mostrarMarcas(eMarca marcas[], int tamMarca);

int validarMarca(eMarca marcas[], int tamMarca, int id);

