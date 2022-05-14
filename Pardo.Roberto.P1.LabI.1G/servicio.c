#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "servicio.h"


int cargarDescripcionServicios(eServicio servicios[], int tamServicio, int idServicio, char descripcion[])
{
    int exito = 0;  // 0 si hubo algun problema. 1 si cargo todo bien. -1 si cargo todo bien pero no encontro coincidencia de ID
    int flag = 1;

    if(servicios != NULL && tamServicio > 0 && descripcion != NULL)
    {
        exito = 1;
        for(int i=0; i<tamServicio; i++)
        {
            if(servicios[i].id == idServicio)
            {
                strcpy(descripcion, servicios[i].descripcion);
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


int cargarPrecioServicio(eServicio servicios[], int tamServicio, int idServicio, float* pPrecioServicio)
{
    int exito = 0; // devuelve 1 si esta todo bien. 0 si hubo un problema con los parametros  y  -1 si busco y no encontro.
    int flag = 1;

    if(servicios != NULL && tamServicio > 0 && pPrecioServicio >= 0){
        exito = 1;
        for(int i=0; i<tamServicio; i++){
            if(servicios[i].id == idServicio){
                (*pPrecioServicio) = servicios[i].precio;

                flag = 0;
                break;
            }
        }
        if(flag){
            exito = -1;
        }
    }
    return exito;
}


// G- Listar Servicios
int mostrarServicios(eServicio servicios[], int tamServicio)
{
    int exito = 0;

    printf(" --------------------------------------------\n");
    printf("             Lista de Servicios              \n");
    printf("    id Serv.     Servicios       Precio \n");
    printf(" --------------------------------------------\n");

    if(servicios != NULL && tamServicio > 0){
        for(int i=0; i<tamServicio; i++){
            printf("    %d          %-10s   $%10.2f\n", servicios[i].id, servicios[i].descripcion, servicios[i].precio);
        }
        printf("\n\n");

        exito = 1;
    }
    return exito;
}


int validarServicio(eServicio servicios[], int tamServicio, int id)
{
    int esValido = 0; // devuelve 1 si esta todo bien. 0 si hubo un problema con los parametros  y  -1 si busco y no encontro.

    if(servicios != NULL && tamServicio > 0){

        for(int i=0; i<tamServicio; i++){
            if(servicios[i].id == id){
                esValido = 1;
                break;
            }
        }
    }
    return esValido;
}
