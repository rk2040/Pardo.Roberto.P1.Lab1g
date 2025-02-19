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
    eFecha fecha;  //validar dia, mes, a�o
    int isEmpty;
}eTrabajo;

#endif // TRABAJO_H_INCLUDED


int inicializarTrabajos(eTrabajo trabajos[], int tamTrabajo);

int buscarLibreTrabajo(eTrabajo trabajos[], int tamTrabajo);

int altaTrabajo(eTrabajo trabajos[], int tamTrabajo, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, eServicio servicios[], int tamServicio, int* pNextId);

void mostrarTrabajoFila(eTrabajo unTrabajo, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, eServicio servicios[], int tamServicio);

int mostrarTrabajos(eTrabajo trabajos[], int tamTrabajo, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, eServicio servicios[], int tamServicio);

int harcodearTrabajos(eTrabajo trabajos[], int tamTrabajo, int cant, int* pId);

int trabajosPorAuto(eTrabajo trabajos[], int tamTrabajo, eServicio servicios[], int tamServicio, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor);

int precioPorTrabajosPorAuto(eTrabajo trabajos[], int tamTrabajo, eServicio servicios[], int tamServicio, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor);

int autosPorServicios(eTrabajo trabajos[], int tamTrabajo, eServicio servicios[], int tamServicio, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor);

int mostrarFechas(eTrabajo trabajos[], int tamTrabajo);

void mostrarTrabajoFilaFecha(eTrabajo unTrabajo, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, eServicio servicios[], int tamServicio);

int serviciosPorFecha(eTrabajo trabajos[], int tamTrabajo, eServicio servicios[], int tamServicio, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor);

