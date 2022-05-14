#ifndef TRABAJO_H_INCLUDED
#define TRABAJO_H_INCLUDED

#include "fecha.h"
#include "auto.h"
#include "marca.h"
#include "color.h"
#include "servicio.h"


typedef struct
{
    int id;        // Autoincremental
    int idAuto;    //validar
    int idServicio;//validar
    eFecha fecha;  //validar dia, mes, año
    int isEmpty;
}eTrabajo;

#endif // TRABAJO_H_INCLUDED


int inicializarTrabajos(eTrabajo trabajos[], int tamTrabajo);

int buscarLibreTrabajo(eTrabajo trabajos[], int tamTrabajo);

int altaTrabajo(eTrabajo trabajos[], int tamTrabajo, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, eServicio servicios[], int tamServicio, int* pNextId);

void mostrarTrabajoFila(eTrabajo unTrabajo, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, eServicio servicios[], int tamServicio);

int mostrarTrabajos(eTrabajo trabajos[], int tamTrabajo, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, eServicio servicios[], int tamServicio);

