#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "informes.h"
#include "Auto.h"
#include "Marca.h"
#include "Color.h"
#include "Trabajo.h"
#include "Servicio.h"

#include "utn.h"
#include "pardo.h"


//===================================================================================================================
//                      Informes complementarios
//===================================================================================================================
int menuInformes()
{
    int opcion;

    printf("-------------------------------------\n");
    printf("  *** Informes Complementarios ***   \n");
    printf("-------------------------------------\n");
    printf(" 1- Mostrar Autos por Color seleccionado.\n");
    printf(" 2- Mostrar Autos por Marca seleccionada.\n");
    printf(" 3- Informar Promedio de Autos con Caja Manual y promedio de Autos con Caja Automatica.\n");
    printf(" 4- Mostrar un listado de Autos separados por Tipo de Caja \n");
    printf(" 5- Elegir un Color y una Marca y contar cuantos Autos hay de ese Color y esa Marca \n");
    printf(" 6- Mostrar la o las Marcas mas elegida por los clientes \n");
// Bonus Track  -   Harcodear algunos Trabajos
    printf(" 7- Pedir un Auto y mostrar todos los Trabajos que se le hicieron \n");
    printf(" 8- Pedir un Auto e informar la suma de los importes de todos los Trabajos que se le hicieron \n");
    printf(" 9- Pedir un Servicio y mostrar los autos a los que se le realizaron ese servicio y la fecha \n");
    printf("10- Pedir una fecha y mostrar todos los servicios realizados en la misma \n");
    printf(" 0- Volver al menu anterior. \n");
    printf("Ingrese una opcion: \n");
    scanf("%d", &opcion);
    fflush(stdin);

    return opcion;
}

int informes(eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, eTrabajo trabajos[], int tamTrabajo, eServicio servicios[], int tamServicio)
{
    int exito = 0;
    char salir = 'n';

        do{
            system("cls");

            switch(menuInformes())
            {
            case 1:
                break;
                mostrarAutosPorColorSeleccionado(autos, tamAuto, marcas, tamMarca, colores, tamColor);
            case 2:
                mostrarAutosPorMarcaSeleccionada(autos, tamAuto, marcas, tamMarca, colores, tamColor);
                break;
            case 3:
                promedioAutosPorCaja(autos, tamAuto, marcas, tamMarca, colores, tamColor);
                break;
            case 4:
                listadoAutosPorCaja(autos, tamAuto, marcas, tamMarca, colores, tamColor);
                break;
            case 5:
                autosPorColoryMarca(autos, tamAuto, marcas, tamMarca, colores, tamColor);
                break;
            case 6:
                marcasConMasAutos(autos, tamAuto, marcas, tamMarca, colores, tamColor);
                break;
// Bonus Track  -   Harcodear algunos Trabajos
            case 7:
                trabajosPorAuto(trabajos, tamTrabajo, servicios, tamServicio, autos, tamAuto, marcas, tamMarca, colores, tamColor);
                break;
            case 8:
                precioPorTrabajosPorAuto(trabajos, tamTrabajo, servicios, tamServicio, autos, tamAuto, marcas, tamMarca, colores, tamColor);
                break;
            case 9:
                autosPorServicios(trabajos, tamTrabajo, servicios, tamServicio, autos, tamAuto, marcas, tamMarca, colores, tamColor);
                break;
            case 10:
                serviciosPorFecha(trabajos, tamTrabajo, servicios, tamServicio, autos, tamAuto, marcas, tamMarca, colores, tamColor);
                break;
            case 0:
                salir = opcionConfirmar("Seguro que quiere volver al menu anterior? s/n ", "Error, vuelva a intentarlo. Volver al menu anterior? s/n ");
                break;
            default:
                printf("Opcion invalida.\n");
                break;
        }
        system("pause");

    }while(salir != 's');

    return exito;
}
