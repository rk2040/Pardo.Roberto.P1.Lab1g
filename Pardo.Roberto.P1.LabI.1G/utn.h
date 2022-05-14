#ifndef UTN_H_INCLUDED
#define UTN_H_INCLUDED

int utn_getNumero(int* pResultado, char* mensaje,char* mensajeError, int minimo,int maximo,int reintentos);
int utn_getCaracter(char* pResultado, char* mensaje,char* mensajeError, char minimo,char maximo,int reintentos);
int utn_getNumeroFloat(float* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getCadena(char* pResultado,int len,char* mensaje,char* mensajeError,int reintentos);
int esNombreValido(char* cadena, int len);


int myGetCadena(char* pResultado,int len,char* mensaje,char* mensajeError,int reintentos);

#endif // UTN_H_INCLUDED
