#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "marca.h"
#include "utn.h"
#include "pardo.h"


int cargarDescripcionMarca(eMarca marcas[], int tamMarca, int idMarca, char descripcion[])
{
    int exito = 0;  // 0 si hubo algun problema. 1 si cargo todo bien. -1 si cargo todo bien pero no encontro coincidencia de ID
    int flag = 1;

    if(marcas != NULL && tamMarca > 0 && descripcion != NULL)
    {
        exito = 1;
        for(int i=0; i<tamMarca; i++)
        {
            if(marcas[i].id == idMarca)
            {
                strcpy(descripcion, marcas[i].descripcion);
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


// E- Listar Marcas
int mostrarMarcas(eMarca marcas[], int tamMarca)
{
    int exito = 0;

    system("cls");
    printf("-------------------------------------\n");
    printf("           *** Marcas ***            \n");
    printf("    Id      Descripcion\n");
    printf("-------------------------------------\n");

    if(marcas != NULL && tamMarca > 0)
    {
        for(int i=0; i<tamMarca; i++)
        {
            printf("    %4d     %-10s\n", marcas[i].id, marcas[i].descripcion);
        }
        printf("\n\n");

        exito = 1;
    }
    return exito;
}


int validarMarca(eMarca marcas[], int tamMarca, int id)
{
    int esValido = 0;

    if(marcas != NULL && tamMarca > 0)
    {
        for(int i=0; i<tamMarca; i++)
        {
            if(marcas[i].id == id)
            {
                esValido = 1;
                break;
            }
        }
    }
    return esValido;
}


//===================================================================================================================
//                      Informes complementarios
//===================================================================================================================

int buscarMarcaId(eMarca marcas[], int tamMarca, int id, int* pIndex)
{
    int exito = 0;

    if(marcas != NULL && tamMarca > 0 && pIndex != NULL)
    {
        *pIndex = -1;
        for(int i=0; i<tamMarca; i++)
        {
            if( marcas[i].id == id)
            {
                *pIndex = i;
                break;
            }
        }
        exito = 1;
    }
    return exito;
}


