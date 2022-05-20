#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

typedef struct
{
    int id; // Comienza en 5000
    char descripcion[20];
}eColor;

#endif // COLOR_H_INCLUDED


int cargarDescripcionColor(eColor colores[], int tamColor, int idColor, char descripcion[]);

int mostrarColores(eColor colores[], int tamColor);

int validarColor(eColor colores[], int tamColor, int id);

int buscarColorId(eColor colores[], int tamColor, int id, int* pIndex);

