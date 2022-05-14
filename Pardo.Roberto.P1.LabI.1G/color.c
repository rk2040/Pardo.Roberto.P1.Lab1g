#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "color.h"


int cargarDescripcionColor(eColor colores[], int tamColor, int idColor, char descripcion[])
{
    int exito = 0;  // 0 si hubo algun problema. 1 si cargo todo bien. -1 si cargo todo bien pero no encontro coincidencia de ID
    int flag = 1;

    if(colores != NULL && tamColor > 0 && descripcion != NULL)
    {
        exito = 1;
        for(int i=0; i<tamColor; i++)
        {
            if(colores[i].id == idColor)
            {
                strcpy(descripcion, colores[i].descripcion);
                flag = 0;
            }
        }

        if(flag)
        {
            exito = -1;
        }
    }
    return exito;
}


// F- Listar Colores
int mostrarColores(eColor colores[], int tamColor)
{
    int exito = 0;

    printf("-------------------------------------\n");
    printf("           *** Colores ***           \n");
    printf("    Id      Descripcion\n");
    printf("-------------------------------------\n");

    if(colores != NULL && tamColor > 0)
    {
        for(int i=0; i<tamColor; i++)
        {
            printf("    %4d     %10s\n", colores[i].id, colores[i].descripcion);
        }
        printf("\n\n");

        exito = 1;
    }
    return exito;
}


int validarColor(eColor colores[], int tamColor, int id)
{
    int esValido = 0;

    if(colores != NULL && tamColor > 0)
    {
        for(int i=0; i<tamColor; i++)
        {
            if(colores[i].id == id)
            {
                esValido = 1;
                break;
            }
        }
    }
    return esValido;
}
