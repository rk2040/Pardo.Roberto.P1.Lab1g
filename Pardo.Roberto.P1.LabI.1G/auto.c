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
    printf("J- Informes complementarios \n");
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
            printf("%4d     %-10s      %-10s   %c\n", unAuto.id, descMarca, descColor, unAuto.caja);
        }

}


// D- Listar
int mostrarAutos(eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)
{
    int exito = 0;
    int flag = 1;

    if(autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {
        system("cls");
        printf("------------------------------------------------\n");
        printf("         *** Listado de Autos ***               \n");
        printf("  Id     Marca           Color       Caja       \n");
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
int buscarAutoId(eAuto autos[], int tamAuto, int id, int* pIndex)
{
    int exito = 0;

    if(autos != NULL && tamAuto > 0 && pIndex != NULL)
    {
        *pIndex = -1;
        for(int i=0; i<tamAuto; i++)
        {
            if( !autos[i].isEmpty && autos[i].id == id)
            {
                *pIndex = i;
                break;
            }
        }
        exito = 1;
    }
    return exito;
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
    printf("0- Volver al menu anterior. \n");
    printf("Ingrese una opcion: \n");
    scanf("%d", &opcion);
    fflush(stdin);
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
    char confirma;

    if(autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {
        system("cls");
        printf("-------------------------------------\n");
        printf("      *** Modificar Auto ***        \n");
        mostrarAutos(autos, tamAuto, marcas, tamMarca, colores, tamColor);

        utn_getNumero(&id, "Ingrese Id del Auto: ", "Error. Reingrese Id del Auto: ", 1,1000, 0);

        if( buscarAutoId(autos, tamAuto, id, &indice) )
        {
            if(indice == -1)
            {
                printf("No se encuentra un Auto con ese Id en el sistema.\n");
            }
            else{
                mostrarAuto(autos[indice], marcas, tamMarca, colores, tamColor);
                confirma = opcionConfirmar("Quiere Modificar este Auto?: s/n ", "Error. Quiere Modificar este Auto?: s/n ");

                if(confirma == 's')
                {
                    auxAuto = autos[indice];

                    do{
                        system("cls");
                        mostrarAuto(autos[indice], marcas, tamMarca, colores, tamColor);
                        switch(menuModificar())
                        {
                        case 1:
                            mostrarColores(colores, tamColor);
                            utn_getNumero(&auxAuto.idColor, "Ingrese Id del Color: ", "Error. Reingrese Id del Color: ", 5000, 5004, 5);
                        //Valido Id
                            while( !validarColor(colores, tamColor, auxAuto.idColor) )
                            {
                                utn_getNumero(&auxAuto.idColor, "Error. Reingrese Id del Color: ", "Error. Reingrese Id del Color: ", 5000, 5004, 5);
                            }
                            autos[indice] = auxAuto;
                            break;
                        case 2:
                                printf("Ingrese tipo de caja: m (manual) / a (automatica)\n");
                                fflush(stdin);
                                scanf("%c", &auxAuto.caja);
                                auxAuto.caja = toupper(auxAuto.caja);
                                while( !(auxAuto.caja == 'M' || auxAuto.caja == 'A') )
                                {
                                    printf("Error. Reingrese tipo de caja: m (manual) / a (automatica)\n");
                                    fflush(stdin);
                                    scanf("%c", &auxAuto.caja);
                                    auxAuto.caja = toupper(auxAuto.caja);
                                }
                                autos[indice] = auxAuto;
                            break;
                        case 0:
                            confirmaSalir = opcionConfirmar("Seguro que quiere salir de la Modificacion? s/n ", "Error, vuelva a intentarlo. salir de la Modificacion? s/n ");
                            break;
                        default:
                            printf("Opcion invalida.\n");
                            break;
                        }

                    }while(confirmaSalir != 's');
                }
                else{
                    printf("Modificacion cancelada por el usuario\n");
                }

            }
            exito = 1;
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
    char confirma;

    if(autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {
        system("cls");
        printf("-------------------------------------\n");
        printf("      *** Baja de Auto ***        \n");
        mostrarAutos(autos, tamAuto, marcas, tamMarca, colores, tamColor);

        utn_getNumero(&id, "Ingrese Id del Auto: ", "Error. Reingrese Id del Auto: ", 1,1000, 0);

        indice = buscarAutoId(autos, tamAuto, id, &indice);

        if( buscarAutoId(autos, tamAuto, id, &indice) )
        {
            if(indice == -1)
            {
                printf("No se encuentra un Auto con ese Id en el sistema.\n");
            }
            else{
                system("cls");
                mostrarAuto(autos[indice], marcas, tamMarca, colores, tamColor);

                confirma = opcionConfirmar("Quiere Confirmar la baja de este Auto? s/n: ", "Error. Quiere Confirmar la baja de este Auto? s/n: ");

                if( confirma == 's' )
                {
                    autos[indice].isEmpty = 1;
                    printf("Baja exitosa.\n");
                }
                else{
                    printf("Baja cancelada por el usuario.\n");
                }
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

int idMarca[10] = {1000,1002,1000,1001,1001,1003,1000,1002,1003,1004};

int idColor[10] = {5000,5002,5000,5001,5004,5003,5002,5002,5000,5001};

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


//===================================================================================================================
//                      Informes complementarios
//===================================================================================================================

// 1
int mostrarAutosPorColorSeleccionado(eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)
{
    int exito = 0;
    int indice;
    int id;

    if(autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {
        mostrarColores(colores, tamColor);
        utn_getNumero(&id, "Ingrese Id del Color: ", "Error. Reingrese Id del Color: ",5000, 5004, 0);

        system("cls");
        printf("------------------------------------------------\n");
        printf("   *** Listado de Autos del Color elegido ***   \n");
        printf("  Id     Marca           Color       Caja       \n");
        printf("------------------------------------------------\n");


        if( buscarColorId(colores, tamColor, id, &indice) )
        {
            if(indice == -1)
            {
                printf("No se encuentra una Marca con ese Id en el sistema.\n");
            }
            else{
                for(int i=0; i<tamAuto; i++)
                {
                    if( !autos[i].isEmpty && autos[i].idColor == id)
                    {
                        mostrarAutoFila(autos[i], marcas, tamMarca, colores, tamColor);
                    }
                }
            }
            exito = 1;
        }
    }
    return exito;
}

// 2
int mostrarAutosPorMarcaSeleccionada(eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)
{
int exito = 0;
    int indice;
    int id;

    if(autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {
        mostrarMarcas(marcas, tamMarca);
        utn_getNumero(&id, "Ingrese Id de la Marca: ", "Error. Reingrese Id de la Marca: ",1000, 1004, 0);

        system("cls");
        printf("------------------------------------------------\n");
        printf("  *** Listado de Autos de la Marca elegida ***  \n");
        printf("  Id     Marca           Color       Caja       \n");
        printf("------------------------------------------------\n");


        if( buscarMarcaId(marcas, tamMarca, id, &indice) )
        {
            if(indice == -1)
            {
                printf("No se encuentra una Marca con ese Id en el sistema.\n");
            }
            else{
                for(int i=0; i<tamAuto; i++)
                {
                    if( !autos[i].isEmpty && autos[i].idMarca == id)
                    {
                        mostrarAutoFila(autos[i], marcas, tamMarca, colores, tamColor);
                    }
                }
            }
            exito = 1;
        }
    }
    return exito;
}

// 3
int promedioAutosPorCaja(eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)
{
    int exito = 0;
    int totalAutos = 0;
    int cajaM = 0;
    int cajaA = 0;
    float promedioM;
    float promedioA;

    if(autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {

        for(int i=0; i<tamAuto; i++)
        {
            if( !autos[i].isEmpty)
            {
                totalAutos ++;

                if(autos[i].caja == 'M')
                {
                    cajaM ++;
                }
                else{
                    cajaA ++;
                }
            }
        }
        if(cajaM > 0)
        {
            promedioM = (float) (cajaM * 100) / totalAutos;
            printf("El promedio de Autos con Caja Manual sobre un total de %d autos es: %% %.2f\n", totalAutos, promedioM);
        }
        else{
            printf("No hay Autos con Caja Manual para promediar.\n");
        }
        if(cajaM > 0)
        {
            promedioA = (float) (cajaA * 100) / totalAutos;
            printf("El promedio de Autos con Caja Automatica sobre un total de %d autos es: %% %.2f\n", totalAutos, promedioA);
        }
        else{
            printf("No hay Autos con Caja Automatica para promediar.\n");
        }

        exito = 1;
    }

    return exito;
}

// 4
int listadoAutosPorCaja(eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)
{
    int exito = 0;

    if(autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {

        system("cls");
        printf("------------------------------------------------\n");
        printf("  *** Listado de Autos por tipo de Caja ***     \n");
        printf("  Id     Marca           Color       Caja       \n");
        printf("------------------------------------------------\n");



        printf("\n  ------ Tipo de Caja Manual ------ \n\n");
        for(int i=0; i<tamAuto; i++)
        {
            if( !autos[i].isEmpty && autos[i].caja == 'M' )
            {
                mostrarAutoFila(autos[i], marcas, tamMarca, colores, tamColor);
            }
        }

        printf("\n  ------ Tipo de Caja Automatica ------ \n\n");
        for(int i=0; i<tamAuto; i++)
        {
            if( !autos[i].isEmpty && autos[i].caja == 'A' )
            {
                mostrarAutoFila(autos[i], marcas, tamMarca, colores, tamColor);
            }
        }

        exito = 1;
    }
    return exito;
}

// 5
int autosPorColoryMarca(eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)
{
    int exito = 0;
    int indiceColor;
    int indiceMarca;
    int idColor;
    int idMarca;
    int total = 0;
    char descColor[20];
    char descMarca[20];

    if(autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {
        mostrarColores(colores, tamColor);
        utn_getNumero(&idColor, "Ingrese Id del Color: ", "Error. Reingrese Id del Color: ",5000, 5004, 0);

        mostrarMarcas(marcas, tamMarca);
        utn_getNumero(&idMarca, "Ingrese Id de la Marca: ", "Error. Reingrese Id de la Marca: ",1000, 1004, 0);


        if( buscarColorId(colores, tamColor, idColor, &indiceColor) && buscarMarcaId(marcas, tamMarca, idMarca, &indiceMarca) )
        {
            if(indiceColor == -1 || indiceMarca == -1)
            {
                printf("No se encuentra un Auto con ese Color y esa Marca en el sistema.\n");
            }
            else{
                cargarDescripcionColor(colores, tamColor, idColor, descColor);
                cargarDescripcionMarca(marcas, tamMarca, idMarca, descMarca);

                for(int i=0; i<tamAuto; i++)
                {
                    if( !autos[i].isEmpty && autos[i].idColor == idColor && autos[i].idMarca == idMarca )
                    {
                        total ++;
                    }
                }
                printf("El total de autos de la Marca %s y el color %s es: %d\n", descMarca, descColor, total);
            }
            exito = 1;
        }
    }
    return exito;
}


// 6
int marcasConMasAutos(eAuto autos[], int tamAuto, eMarca marcas[], int tamMarca, eColor colores[], int tamColor)
{
    int exito = 0;
    int marcaMax;
    int cantidades[tamMarca];
    int flag = 1;
    char descripcion[20];

    if(autos != NULL && tamAuto > 0 && marcas != NULL && tamMarca > 0 && colores != NULL && tamColor)
    {

        for(int i=0; i<tamMarca; i++)
        {
            cantidades[i] = 0;

            for(int j=0; j<tamAuto; j++)
            {
                if( !autos[j].isEmpty && autos[j].idMarca == marcas[i].id )
                {
                    cantidades[i] ++;
                }
            }
        }

        for(int i=0; i<tamMarca; i++)
        {
            if( flag || ( cantidades[i] > marcaMax) )
            {
                marcaMax = cantidades[i];
                cargarDescripcionMarca(marcas, tamMarca, marcas[i].id, descripcion);
                flag = 0;
            }
        }

        for(int i=0; i<tamMarca; i++)
        {
            if(cantidades[i] == marcaMax)
            {
                cargarDescripcionMarca(marcas, tamMarca, marcas[i].id, descripcion);
                printf("La marca mas elegida por los clientes es %s y tiene %d autos\n", descripcion, marcaMax);
            }
        }

        exito = 1;
    }
    return exito;
}
