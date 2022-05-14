#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "auto.h"
#include "marca.h"
#include "color.h"

#include "utn.h"
#include "pardo.h"




char menu()
{
    char opcion;

    printf("-------------------------------------\n");
    printf("    *** Lavadero de Autos ***        \n");
    printf("-------------------------------------\n");
    printf("A- Altas Auto \n");
    printf("B- Modificar Auto \n");
    printf("C- Baja Auto \n");
    printf("D- Listar Autos \n");
    printf("E- Listar Marcas \n");
    printf("F- Listar Colores \n");
    printf("G- Listar Servicios \n");
    printf("H- Altas Trabajo \n");
    printf("I- Listar Trabajos \n");
    printf("X- Salir \n");
    printf("Ingrese una opcion: \n");
    fflush(stdin);
    scanf("%c", &opcion);
    opcion = toupper(opcion);

    return opcion;
}


// Inicializa todos los autos con valos isEmpty 1 (vacio)
int inicializarAutos(eAuto autos[], int tam)
{
    int exito = 0;

    if(autos != NULL && tam > 0)
    {
        for(int i=0; i<tam; i++)
        {
            autos[i].isEmpty = 1;
        }
        exito = 1;
    }
    return exito;
}


// Buscar la primer posicion libre dentro del array
int buscarLibre(eAuto autos[], int tam)
{
    int indice = -1;

    if(autos != NULL && tam > 0)
    {
        for(int i=0; i<tam; i++)
        {
            if( autos[i].isEmpty )
            {
                indice = i;
                break;
            }
        }
    }
    return indice;
}


// A- Alta
int altaAuto(eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor, int* pNextId)
{
    int exito = 0;
    int indice;
    eAuto auxAuto;

    if(autos != NULL && tamAuto >0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor > 0)
    {
        system("cls");

        printf("-------------------------------------\n");
        printf("       *** Alta de Autos ***        \n");
        printf("-------------------------------------\n");

        indice = buscarLibre(autos, tamAuto);

        if(indice == -1)
        {
            printf("No hay Autos cargados en el sistema.\n");
        }
        else{
            auxAuto.id = *pNextId;

            (*pNextId)++;   // le sumo 1 para el id del siguiente que se de de alta


            printf("Ingrese tipo de caja: m (manual) / a (automatica)\n");
            fflush(stdin);
            scanf("%c", &auxAuto.caja);
            auxAuto.caja = toupper(auxAuto.caja);
            while( !(auxAuto.caja == 'M' || auxAuto.caja == 'A') )
            {
                printf("Ingrese tipo de caja: m (manual) / a (automatica)\n");
                fflush(stdin);
                scanf("%c", &auxAuto.caja);
                auxAuto.caja = toupper(auxAuto.caja);
            }

            mostrarMarcas(marcas, tamMarca);
            //utn_getNumero(&auxAuto.idMarca, "Ingrese Id de la Marca: ", "Error. \nReingrese Id de la Marca: ", 1, 1000, 1);
            printf("Ingrese Id de la Marca: ");
            fflush(stdin);
            scanf("%d", &auxAuto.idMarca);
        // Valido Id
            while( !validarMarca(marcas, tamMarca, auxAuto.idMarca) )
            {
                printf("Error. \nReingrese Id de la Marca: ");
                fflush(stdin);
                scanf("%d", &auxAuto.idMarca);
            }


            mostrarColores(colores, tamColor);
            printf("Ingrese Id del Color: ");
            fflush(stdin);
            scanf("%d", &auxAuto.idColor);
        //Valido Id
            while( !validarColor(colores, tamColor, auxAuto.idColor) )
            {
                printf("Error. Reingrese Id del Color: ");
                fflush(stdin);
                scanf("%d", &auxAuto.idColor);
            }

            auxAuto.isEmpty = 0;

            autos[indice] = auxAuto;

            exito = 1;
        }
    }
    return exito;
}


int cargarDescripcionAuto(eAuto autos[], int tamAuto, int idAuto, char descripcion[], eMarca marcas[], int tamMarca)
{
    int exito = 0;  // 0 si hubo algun problema. 1 si cargo todo bien. -1 si cargo todo bien pero no encontro coincidencia de ID
    int flag = 1;
    int indiceMarca;

    if(autos != NULL && tamAuto > 0 && descripcion != NULL && marcas != NULL && tamMarca > 0)
    {
        exito = 1;
        for(int i=0; i<tamAuto; i++)
        {
            if(autos[i].id == idAuto)
            {
                indiceMarca = autos[i].idMarca;
                strcpy(descripcion, marcas[indiceMarca].descripcion);
                flag = 0;
                break;
            }
        }
        if(flag)
        {
            exito = -1;
        }
    }
    return exito;
}


void mostrarAuto(eAuto unAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)
{
    char descMarca[20];
    char descColor[20];

    if( cargarDescripcionMarca(marcas, tamMarca, unAuto.idMarca, descMarca) &&
        cargarDescripcionColor(colores, tamColor, unAuto.idColor, descColor) )
    {
        printf(" Id     : %d\n", unAuto.id);
        printf(" Marca  : %s\n", descMarca);
        printf(" Color  : %s\n", descColor);
        printf(" Caja   : %c\n", unAuto.caja);
    }
}


void mostrarAutoFila(eAuto unAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)
{
    char descMarca[20];
    char descColor[20];

    if( cargarDescripcionMarca(marcas, tamMarca, unAuto.idMarca, descMarca) &&
        cargarDescripcionColor(colores, tamColor, unAuto.idColor, descColor) )
        {
            printf("%4d     %-10s       %-10s   %c\n", unAuto.id, descMarca, descColor, unAuto.caja);
        }

}


// D- Listar
int mostrarAutos(eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)
{
    int exito = 0;
    int flag = 1;

    if(autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {
        printf("------------------------------------------------\n");
        printf("         *** Listado de Autos ***             \n");
        printf("  Id     Marca           Color       Caja\n");
        printf("------------------------------------------------\n");

        for(int i=0; i<tamAuto; i++)
        {
            if( !autos[i].isEmpty )
            {
                mostrarAutoFila(autos[i], marcas, tamMarca, colores, tamColor);
                flag = 0;
            }
        }
        if( flag )
        {
            printf("No hay Autos cargados en el sistema.\n");
        }
        exito = 1;
    }
    return exito;
}


// Busqueda por Id
int buscarAutoId(eAuto autos[], int tamAuto, int id)
{
    int indice = 0;

    if(autos != NULL && tamAuto > 0)
    {
        for(int i=0; i<tamAuto; i++)
        {
            if( !autos[i].isEmpty && autos[i].id == id)
            {
                indice = i;
                break;
            }
        }
    }
    return indice;
}


// B- Modificar
int menuModificar()
{
    int opcion;

    printf("-------------------------------------\n");
    printf("      *** Modificar Auto ***        \n");
    printf("-------------------------------------\n");
    printf("1- Color \n");
    printf("2- Caja \n");
    printf("0- Salir \n");
    printf("Ingrese una opcion: \n");
    scanf("%d", &opcion);
    return opcion;
}


int validarAuto(eAuto autos[], int tamAuto, int id)
{
    int esValido = 0;

    if(autos != NULL && tamAuto > 0)
    {
        for(int i=0; i<tamAuto; i++)
        {
            if(autos[i].id == id)
            {
                esValido = 1;
                break;
            }
        }
    }
    return esValido;
}


int modificarAuto(eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)
{
    int exito = 0;
    int indice;
    int id;
    eAuto auxAuto;
    char confirmaSalir = 'n';

    if(autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {
        system("cls");
        printf("-------------------------------------\n");
        printf("      *** Modificar Auto ***        \n");
        mostrarAutos(autos, tamAuto, marcas, tamMarca, colores, tamColor);

        utn_getNumero(&id, "Ingrese Id del Auto: ", "Error. Reingrese Id del Auto: ", 1,1000, 5);

        indice = buscarAutoId(autos, tamAuto, id);

        if(indice == -1)
        {
            printf("No se encuentra un Auto con ese Id en el sistema.\n");
        }
        else{
            system("cls");
            mostrarAuto(autos[indice], marcas, tamMarca, colores, tamColor);

            auxAuto = autos[indice];

            do{
                switch(menuModificar())
                {
                case 1:
                    mostrarColores(colores, tamColor);
                    printf("Ingrese Id del Color: ");
                    fflush(stdin);
                    scanf("%d", &auxAuto.idColor);
                //Valido Id
                    while( !validarColor(colores, tamColor, auxAuto.idColor) )
                    {
                        printf("Error. Reingrese Id del Color: ");
                        fflush(stdin);
                        scanf("%d", &auxAuto.idColor);
                    }
                    break;
                case 2:
                        printf("Ingrese tipo de caja: m (manual) / a (automatica)\n");
                        fflush(stdin);
                        scanf("%c", &auxAuto.caja);
                        auxAuto.caja = toupper(auxAuto.caja);
                        while( !(auxAuto.caja == 'M' || auxAuto.caja == 'A') )
                        {
                            printf("Ingrese tipo de caja: m (manual) / a (automatica)\n");
                            fflush(stdin);
                            scanf("%c", &auxAuto.caja);
                            auxAuto.caja = toupper(auxAuto.caja);
                        }
                    break;
                case 0:
                    confirmaSalir = opcionConfirmar("Seguro que quiere salir? s/n ", "Error, vuelva a intentarlo. Salir? s/n ");
                    break;
                default:
                    printf("Opcion invalida.\n");
                    break;
                }

            }while(confirmaSalir != 's');
        }
    }
    return exito;
}



// C- Baja
int bajaAuto(eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)
{
    int exito = 0;
    int indice;
    int id;

    if(autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {
        system("cls");
        printf("-------------------------------------\n");
        printf("      *** Baja de Auto ***        \n");
        mostrarAutos(autos, tamAuto, marcas, tamMarca, colores, tamColor);

        utn_getNumero(&id, "Ingrese Id del Auto: ", "Error. Reingrese Id del Auto: ", 1,1000, 5);

        indice = buscarAutoId(autos, tamAuto, id);

        if(indice == -1)
        {
            printf("No se encuentra un Auto con ese Id en el sistema.\n");
        }
        else{
            system("cls");
            mostrarAuto(autos[indice], marcas, tamMarca, colores, tamColor);

            if( opcionConfirmar("Confirmar baja? s/n: ", "Error. Confirmar baja? s/n: ") == 's' )
            {
                autos[indice].isEmpty = 1;
            }
        }
        exito = 1;
    }
    return exito;
}



//=========================================================================================================================
//DATOS HARCODEO
//=========================================================================================================================
int idAuto[10] = {1,2,3,4,5,6,7,8,9,10};

int idMarca[10] = {1000,1002,1000,1001,1001,1003,1000,1002,1003,1001};

int idColor[10] = {5000,5002,5000,5001,5001,5003,5002,5002,5000,5001};

char caja[10] = {'A','A','M','M','M','A','M','M','M','A'};


int harcodearAutos(eAuto autos[], int tamAuto, int cant, int* pId)
{
    int contador = -1;

    if(autos != NULL && tamAuto > 0 && cant >= 0 && cant <= tamAuto && pId != NULL){
        contador = 0;
        for(int i=0; i<cant; i++){
            autos[i].id = *pId;
            (*pId)++;
            autos[i].idMarca = idMarca[i];
            autos[i].idColor = idColor[i];
            autos[i].caja = caja[i];
            autos[i].isEmpty = 0;
            contador++;
        }
    }
    return contador;
}
