#include <stdio.h>
#include <stdlib.h>

#include "trabajo.h"
#include "auto.h"
#include "marca.h"
#include "color.h"
#include "servicio.h"
#include "fecha.h"
#include "utn.h"
#include "pardo.h"

#define TAM_AUTO 1000
#define TAM_MARCA 5
#define TAM_COLOR 5
#define TAM_SERV 4
#define TAM_TRAB 1000


int main()
{
    eAuto autos[TAM_AUTO];
    int nextIdAuto = 1;
    eTrabajo trabajos[TAM_TRAB];
    int nextIdTrabajo = 10000;
   // eMarca marcas[TAM_MARCA];
   // int nextIdMarca = 1000;
   // eColor colores[TAM_COLOR];
   // int nextIdColor = 5000;
   // eServicio servicios[TAM_SERV];
   // int nextIdServicio = 20000;
    char salir = 'n';

// Harcodeo de Estructuras
    eMarca marcas[TAM_MARCA] ={
        {1000, "Renault"},
        {1001, "Ford"},
        {1002, "Fiat"},
        {1003, "Chevrolet"},
        {1004, "Peugeot"}
    };

    eColor colores[TAM_COLOR] = {
        {5000, "Negro"},
        {5001, "Blanco"},
        {5002, "Rojo"},
        {5003, "Verde"},
        {5004, "Azul"}
    };

    eServicio servicios[TAM_SERV] = {
        {20000, "Lavado", 450.00},
        {20001, "Pulido", 500.00},
        {20002, "Encerado", 600.00},
        {20003, "Completo", 900.00}
    };


    if(!inicializarAutos(autos, TAM_AUTO))
    {
        printf("Problemas al inicializar.\n");
    }
    else{
        printf("Inicializo bien.\n");
    }

    if(!inicializarTrabajos(trabajos, TAM_TRAB))
    {
        printf("Problemas al inicializar.\n");
    }
    else{
        printf("Inicializo bien.\n");
    }

    harcodearAutos(autos, TAM_AUTO, 10, &nextIdAuto);


    do{
        system("cls");

        switch(menu())
        {
        case 'A':
            if( !altaAuto(autos, TAM_AUTO, marcas, TAM_MARCA, colores, TAM_COLOR, &nextIdAuto))
            {
                printf("Hubo algun problema al dar de alta.\n");
            }
            else{
                printf("Alta exitosa.\n");
            }
            break;
        case 'B':
            if( !modificarAuto(autos, TAM_AUTO, marcas, TAM_MARCA, colores, TAM_COLOR))
            {
                printf("Hubo un problema al intentar hacer la modificacion.\n");
            }
            else{
                printf("Modificacion exitosa.\n");
            }
            break;
        case 'C':
            if( !bajaAuto(autos, TAM_AUTO, marcas, TAM_MARCA, colores, TAM_COLOR))
            {
                printf("Hubo un problema al intentar hacer la Baja.\n");
            }
            else{
                printf("Baja exitosa.\n");
            }
            break;
        case 'D':
            mostrarAutos(autos, TAM_AUTO, marcas, TAM_MARCA, colores, TAM_COLOR);
            break;
        case 'E':
            mostrarMarcas(marcas, TAM_MARCA);
            break;
        case 'F':
            mostrarColores(colores, TAM_COLOR);
            break;
        case 'G':
            mostrarServicios(servicios, TAM_SERV);
            break;
        case 'H':
            if( !altaTrabajo(trabajos, TAM_TRAB, autos, TAM_AUTO, marcas, TAM_MARCA, colores, TAM_COLOR, servicios, TAM_SERV, &nextIdTrabajo) )
            {
                printf("Hubo algun problema al dar de alta.\n");
            }
            else{
                printf("Alta exitosa.\n");
            }
            break;
        case 'I':
            mostrarTrabajos(trabajos, TAM_TRAB, autos, TAM_AUTO, marcas, TAM_MARCA, colores, TAM_COLOR, servicios, TAM_SERV);
            break;
        case 'X':
            salir = opcionConfirmar("Seguro que quiere salir? s/n ", "Error, vuelva a intentarlo. Salir? s/n ");
            break;
        default:
            printf("Opcion invalida.\n");
            break;
        }
        system("pause");

    }while(salir != 's');


    return 0;
}

