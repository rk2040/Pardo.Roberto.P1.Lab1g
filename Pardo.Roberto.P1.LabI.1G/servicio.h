#ifndef SERVICIO_H_INCLUDED
#define SERVICIO_H_INCLUDED


typedef struct
{
    int id; // Comienza en 20000
    char descripcion[25];
    float precio;
}eServicio;

#endif // SERVICIO_H_INCLUDED


int cargarDescripcionServicios(eServicio servicios[], int tamServicio, int idServicio, char descripcion[]);

int cargarPrecioServicio(eServicio servicios[], int tamServicio, int idServicio, float* pPrecioServicio);

int mostrarServicios(eServicio servicios[], int tamServicio);

int validarServicio(eServicio servicios[], int tamServicio, int id);

int buscarServicioId(eServicio servicios[], int tamServicio, int id, int* pIndex);

