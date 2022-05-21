#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "trabajo.h"
#include "auto.h"
#include "marca.h"
#include "color.h"
#include "servicio.h"
#include "fecha.h"
#include "utn.h"
#include "pardo.h"


int inicializarTrabajos(eTrabajo trabajos[], int tamTrabajo)
{
    int exito = 0;

    if(trabajos != NULL && tamTrabajo > 0){
        for(int i=0; i<tamTrabajo; i++)
        {
            trabajos[i].isEmpty = 1;
        }
        exito = 1;
    }
    return exito;
}


int buscarLibreTrabajo(eTrabajo trabajos[], int tamTrabajo)     // -1 si no hay lugar libre, sino devuelve el indice de la primer estructura vacia
{
    int indice = -1;

    if(trabajos != NULL && tamTrabajo > 0)
    {
        for(int i=0; i<tamTrabajo; i++)
        {
            if( trabajos[i].isEmpty )
            {
                indice = i;
                break;
            }
        }
    }
    return indice;
}



int altaTrabajo(eTrabajo trabajos[], int tamTrabajo, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, eServicio servicios[], int tamServicio, int* pNextId)
{
    int exito = 0;
    int indice;
    eTrabajo auxTrabajo;

    if(trabajos != NULL && tamTrabajo > 0 && autos != NULL && tamAuto >0 && servicios != NULL && tamServicio > 0)
    {
        system("cls");

        printf("-------------------------------------\n");
        printf("      *** Alta de trabajo ***        \n");
        printf("-------------------------------------\n");

        indice = buscarLibreTrabajo(trabajos, tamTrabajo);

        if(indice == -1)
        {
            printf("No hay Trabajos cargados en el sistema.\n");
        }
        else{
            auxTrabajo.id = *pNextId;

            (*pNextId)++;

            mostrarAutos(autos, tamAuto, marcas, tamMarca, colores, tamColor);
            //utn_getNumero(&auxTrabajo.idAuto, "Ingrese id Auto: \n", "Error. Reingrese id Auto: \n", 1, 1000, 5);
            printf("Ingrese id del auto: ");
            fflush(stdin);
            scanf("%d", &auxTrabajo.idAuto);
            while( !validarAuto(autos, tamAuto, auxTrabajo.idAuto))
            {
                printf("Error. Reingrese id del Auto: ");
                fflush(stdin);
                scanf("%d", &auxTrabajo.idAuto);
            }

            mostrarServicios(servicios, tamServicio);
            printf("Ingrese id del Servicio: ");
            fflush(stdin);
            scanf("%d", &auxTrabajo.idServicio);
            while( !validarServicio(servicios, tamServicio, auxTrabajo.idServicio))
            {
                printf("Error. Reingrese id del Servicio: ");
                fflush(stdin);
                scanf("%d", &auxTrabajo.idServicio);
            }
        //Fecha año
            utn_getNumero(&auxTrabajo.fecha.anio, "Ingrese anio: aaaa ", "\nError. Reingrese anio: aaaa", 1990, 2022,5);
        //Fecha mes
            utn_getNumero(&auxTrabajo.fecha.mes, "Ingrese mes: mm ", "\nError. Reingrese mes: mm", 1, 12, 5);
        //Fecha dia
            if(auxTrabajo.fecha.mes == 1 || auxTrabajo.fecha.mes == 3 || auxTrabajo.fecha.mes == 5 || auxTrabajo.fecha.mes == 7 ||
               auxTrabajo.fecha.mes == 8 || auxTrabajo.fecha.mes == 10 || auxTrabajo.fecha.mes == 12)
            {
                utn_getNumero(&auxTrabajo.fecha.dia, "Ingrese dia: dd ", "\nError. Reingrese dia: dd", 1, 31, 5);
            }
            else if(auxTrabajo.fecha.mes == 4 || auxTrabajo.fecha.mes == 6 || auxTrabajo.fecha.mes == 9 || auxTrabajo.fecha.mes == 11)
            {
                utn_getNumero(&auxTrabajo.fecha.dia, "Ingrese dia: dd ", "\nError. Reingrese dia: dd", 1, 30, 5);
            }
            else{
                utn_getNumero(&auxTrabajo.fecha.dia, "Ingrese dia: dd ", "\nError. Reingrese dia: dd", 1, 28, 5);
            }

            auxTrabajo.isEmpty = 0;

            trabajos[indice] = auxTrabajo;

            exito = 1;
        }
    }
    return exito;
}


void mostrarTrabajoFila(eTrabajo unTrabajo, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, eServicio servicios[], int tamServicio)
{
    char descMarca[20];
    char descColor[20];
    char descServicio[25];
    float precioServicio;
    int indice;

    for(int i=0; i<tamAuto; i++)
    {
        if(unTrabajo.idAuto == autos[i].id)
        {
            indice = i;

            if( cargarDescripcionMarca(marcas, tamMarca, autos[indice].idMarca, descMarca) &&
                cargarDescripcionColor(colores, tamColor, autos[indice].idColor, descColor) &&
                cargarDescripcionServicios(servicios, tamServicio, unTrabajo.idServicio, descServicio) &&
                cargarPrecioServicio(servicios, tamServicio, unTrabajo.idServicio, &precioServicio) )
            {
                printf(" %2d       %-15s %-15s%-15s $%7.2f         %02d/%02d/%d\n",
                       unTrabajo.id,
                       descMarca,
                       descColor,
                       descServicio,
                       precioServicio,
                       unTrabajo.fecha.dia,
                       unTrabajo.fecha.mes,
                       unTrabajo.fecha.anio
                       );
           }
           break;
        }
    }
}


int mostrarTrabajos(eTrabajo trabajos[], int tamTrabajo, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, eServicio servicios[], int tamServicio)
{
    int exito = 0;
    int flag = 1;

    if(trabajos != NULL && tamTrabajo > 0)
    {
        system("cls");
        printf("---------------------------------------------------------------------------------------------------\n");
        printf("                                *** Lista de Trabajos ***                                          \n");
        printf("  Id        Marca Auto       Color         Servicio          Precio        Fecha Trabajo           \n");
        printf("---------------------------------------------------------------------------------------------------\n");

        for(int i=0; i<tamTrabajo; i++)
        {
            if( !trabajos[i].isEmpty )
            {
                mostrarTrabajoFila(trabajos[i], autos, tamAuto, marcas, tamMarca, colores, tamColor, servicios, tamServicio);
                flag = 0;
            }
        }
        if( flag )
        {
            printf("No hay trabajos para mostrar \n");
        }
        exito = 1;
    }
    return exito;
}


//=========================================================================================================================
//DATOS HARCODEO
//=========================================================================================================================
int idTrabajo[20] = {10000,10001,10002,10003,10004,10005,10006,10007,10008,10009,10010,10011,10012,10013,10014,10015,10016,10017,10018,10019};

int idAutos[20] = {1,5,3,9,2,7,6,8,10,4,7,5,1,7,8,3,5,7,4,10};

int idServicio[20] = {20000,20002,20000,20001,20001,20003,20002,20002,20000,20001,20003,20003,20001,20002,20000,20003,20001,20002,20003,20001};

eFecha fecha[20] = { {22,2,2022},{9,7,2022},{20,7,2022},{13,9,2022},{22,2,2022},{9,7,2022},{22,2,2022},{9,7,2022},{20,7,2022},{13,9,2022},
                     {9,7,2022},{20,7,2022},{22,2,2022},{9,7,2022},{20,7,2022},{13,9,2022},{22,2,2022},{9,7,2022},{22,2,2022},{9,7,2022}
                };


int harcodearTrabajos(eTrabajo trabajos[], int tamTrabajo, int cant, int* pId)
{
    int contador = -1;

    if(trabajos != NULL && tamTrabajo > 0 && cant >= 0 && cant <= tamTrabajo && pId != NULL){
        contador = 0;
        for(int i=0; i<cant; i++){
            trabajos[i].id = *pId;
            (*pId)++;
            trabajos[i].idAuto = idAutos[i];
            trabajos[i].idServicio = idServicio[i];
            trabajos[i].fecha = fecha[i];
            trabajos[i].isEmpty = 0;
            contador++;
        }
    }

    return contador;
}


// Bonus Track  -   Harcodear algunos Trabajos
// 7
int trabajosPorAuto(eTrabajo trabajos[], int tamTrabajo, eServicio servicios[], int tamServicio, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)

{
    int exito = 0;
    int indice;
    int id;
    int flag = 1;

    if(trabajos != NULL && tamTrabajo > 0 && servicios != NULL && tamServicio > 0 && autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {
        mostrarAutos(autos, tamAuto, marcas, tamMarca, colores, tamColor);

        utn_getNumero(&id, "Ingrese Id del Auto: ", "Error. Reingrese Id del Auto: ", 1,1000, 0);

        if( buscarAutoId(autos, tamAuto, id, &indice) )
        {
            if(indice == -1)
            {
                printf("No se encuentra un Auto con ese Id en el sistema.\n");
            }
            else{
                system("cls");
                printf("---------------------------------------------------------------------------------------------------\n");
                printf("                           *** Lista de Trabajos realizados***                                     \n");
                printf("  Id        Marca Auto       Color         Servicio          Precio        Fecha Trabajo           \n");
                printf("---------------------------------------------------------------------------------------------------\n");

                for(int i=0; i<tamTrabajo; i++)
                {
                    if( !trabajos[i].isEmpty && trabajos[i].idAuto == autos[indice].id)
                    {
                        mostrarTrabajoFila(trabajos[i], autos, tamAuto, marcas, tamMarca, colores, tamColor, servicios, tamServicio);
                        flag = 0;
                    }
                }
                if( flag )
                {
                    printf("No hay trabajos para mostrar \n");
                }


            }
            exito = 1;
        }
    }
    return exito;
}


// 8
int precioPorTrabajosPorAuto(eTrabajo trabajos[], int tamTrabajo, eServicio servicios[], int tamServicio, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)
{
    int exito = 0;
    int indice;
    int id;
    int idServ;
    float totalPrecio = 0;
    int flag = 1;

    if(trabajos != NULL && tamTrabajo > 0 && servicios != NULL && tamServicio > 0 && autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {
        mostrarAutos(autos, tamAuto, marcas, tamMarca, colores, tamColor);

        utn_getNumero(&id, "Ingrese Id del Auto: ", "Error. Reingrese Id del Auto: ", 1,1000, 0);

        if( buscarAutoId(autos, tamAuto, id, &indice) )
        {
            if(indice == -1)
            {
                printf("No se encuentra un Auto con ese Id en el sistema.\n");
            }
            else{
                system("cls");
                mostrarAuto(autos[indice], marcas, tamMarca, colores, tamColor);

                for(int i=0; i<tamTrabajo; i++)
                {
                    if( !trabajos[i].isEmpty && trabajos[i].idAuto == autos[indice].id)
                    {
                        idServ = trabajos[i].idServicio;

                        for(int j=0; j<tamServicio; j++)
                        {
                            if(servicios[j].id == idServ)
                            {
                                totalPrecio = totalPrecio + servicios[j].precio;
                                flag = 0;
                            }
                        }
                    }
                }
                if( flag )
                {
                    printf("No hay trabajos para mostrar \n");
                }
                else{
                    printf("El precio total de todos los trabajos en el auto es: $ %.2f\n", totalPrecio);
                }
            }
            exito = 1;
        }
    }
    return exito;
}


// 9
int autosPorServicios(eTrabajo trabajos[], int tamTrabajo, eServicio servicios[], int tamServicio, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)
{
    int exito = 0;
    int indice;
    int id;
    int flag = 1;

    if(trabajos != NULL && tamTrabajo > 0 && servicios != NULL && tamServicio > 0 && autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {
        mostrarServicios(servicios, tamServicio);

        utn_getNumero(&id, "Ingrese Id del Servicio: ", "Error. Reingrese Id del servicio: ", 20000,20003, 0);

        if( buscarServicioId(servicios, tamServicio, id, &indice) )
        {
            if(indice == -1)
            {
                printf("No se encuentra un Servicio con ese Id en el sistema.\n");
            }
            else{
                system("cls");
                printf("---------------------------------------------------------------------------------------------------\n");
                printf("                       *** Lista de Autos por Servicio realizado ***                               \n");
                printf("  Id        Marca Auto       Color         Servicio          Precio        Fecha Trabajo           \n");
                printf("---------------------------------------------------------------------------------------------------\n");

                for(int i=0; i<tamTrabajo; i++)
                {
                    if( !trabajos[i].isEmpty && trabajos[i].idServicio == servicios[indice].id)
                    {
                        mostrarTrabajoFila(trabajos[i], autos, tamAuto, marcas, tamMarca, colores, tamColor, servicios, tamServicio);
                        flag = 0;
                    }
                }
                if( flag )
                {
                    printf("No hay trabajos para mostrar \n");
                }


            }
            exito = 1;
        }
    }
    return exito;
}


// Listar Fechas
int mostrarFechas(eTrabajo trabajos[], int tamTrabajo)
{
    int exito = 0;

    system("cls");
    printf(" -------------------\n");
    printf("  Lista de Fechas   \n");
    printf("     fecha   \n");
    printf(" -------------------\n");

    if(trabajos != NULL && tamTrabajo > 0)
    {
        for(int i=0; i<tamTrabajo; i++){
            if( !trabajos[i].isEmpty )
            {
                printf("  %02d/%02d/%d\n",
                       trabajos[i].fecha.dia,
                       trabajos[i].fecha.mes,
                       trabajos[i].fecha.anio
                       );
            }
        }
        printf("\n\n");

        exito = 1;
    }
    return exito;
}

void mostrarTrabajoFilaFecha(eTrabajo unTrabajo, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, eServicio servicios[], int tamServicio)
{
    char descServicio[25];
    float precioServicio;
    //int indice;

    for(int i=0; i<tamAuto; i++)
    {
        if(unTrabajo.idAuto == autos[i].id)
        {
           // indice = i;

            if( cargarDescripcionServicios(servicios, tamServicio, unTrabajo.idServicio, descServicio) &&
                cargarPrecioServicio(servicios, tamServicio, unTrabajo.idServicio, &precioServicio) )
            {
                printf(" %2d       %-15s $%7.2f         %02d/%02d/%d\n",
                       unTrabajo.id,
                       descServicio,
                       precioServicio,
                       unTrabajo.fecha.dia,
                       unTrabajo.fecha.mes,
                       unTrabajo.fecha.anio
                       );
           }
           break;
        }
    }
}

// 10
int serviciosPorFecha(eTrabajo trabajos[], int tamTrabajo, eServicio servicios[], int tamServicio, eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)
{
    int exito = 0;
    int flag = 1;
    eTrabajo auxTrabajo;

    if(trabajos != NULL && tamTrabajo > 0 && servicios != NULL && tamServicio > 0 && autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {
        mostrarFechas(trabajos, tamTrabajo);

    //Fecha año
        utn_getNumero(&auxTrabajo.fecha.anio, "Ingrese anio: aaaa ", "\nError. Reingrese anio: aaaa", 1990, 2022,5);
    //Fecha mes
        utn_getNumero(&auxTrabajo.fecha.mes, "Ingrese mes: mm ", "\nError. Reingrese mes: mm", 1, 12, 5);
    //Fecha dia
        if(auxTrabajo.fecha.mes == 1 || auxTrabajo.fecha.mes == 3 || auxTrabajo.fecha.mes == 5 || auxTrabajo.fecha.mes == 7 ||
           auxTrabajo.fecha.mes == 8 || auxTrabajo.fecha.mes == 10 || auxTrabajo.fecha.mes == 12)
        {
            utn_getNumero(&auxTrabajo.fecha.dia, "Ingrese dia: dd ", "\nError. Reingrese dia: dd", 1, 31, 5);
        }
        else if(auxTrabajo.fecha.mes == 4 || auxTrabajo.fecha.mes == 6 || auxTrabajo.fecha.mes == 9 || auxTrabajo.fecha.mes == 11)
        {
            utn_getNumero(&auxTrabajo.fecha.dia, "Ingrese dia: dd ", "\nError. Reingrese dia: dd", 1, 30, 5);
        }
        else{
            utn_getNumero(&auxTrabajo.fecha.dia, "Ingrese dia: dd ", "\nError. Reingrese dia: dd", 1, 28, 5);
        }

                system("cls");
        printf("-------------------------------------------------------------------\n");
        printf("           *** Lista de Servicios por Fecha ***                    \n");
        printf("  Id        Servicio          Precio        Fecha Trabajo          \n");
        printf("-------------------------------------------------------------------\n");

        for(int i=0; i<tamTrabajo; i++)
        {
            if( !trabajos[i].isEmpty && auxTrabajo.fecha.anio == trabajos[i].fecha.anio &&
                 auxTrabajo.fecha.mes == trabajos[i].fecha.mes && auxTrabajo.fecha.dia == trabajos[i].fecha.dia)
            {
                mostrarTrabajoFilaFecha(trabajos[i], autos, tamAuto, marcas, tamMarca, colores, tamColor, servicios, tamServicio);
                flag = 0;
            }
        }
        if( flag )
        {
            printf("No hay cargados Servicios realizados ese dia en el sistema.\n");
        }
        exito = 1;
        }
    return exito;
}
