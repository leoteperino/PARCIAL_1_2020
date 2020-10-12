#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "Cliente.h"
#include "Publicacion.h"
#include "utn.h"
#include "Informes.h"

/**
 * \brief Calcula la cantidad de publicaciones que estan pausadas
 * \param array Publicaciones a ser actualizado
 * \param int Limite del array de Publicaciones
 * \return Retorna la cantidad de publicaciones pausadas o -1(ERROR)
 */
int info_calculaCantidadDePublicacionesPausadas(Publicacion* array, int limite)
{
	int ret=-1;
	int i;
	int contPausadas = 0;
	if(array!=NULL && limite>0)
	{
		for(i=0;i<limite;i++)
		{
			if(array[i].isEmpty==FALSE && array[i].estado==ESTADO_PAUSADA)
			{
				contPausadas++;
			}
		}
		ret = contPausadas;
	}
	return ret;
}

/**
 * \brief Imprime la cantidad mayor de las publicaciones contratadas x el mismo cliente.
 * \param arrayPubli Array de Publicacion a ser actualizado
 * \param limitePubli Limite del array de Publicacion
 * \param arrayCli Array de Clientes a ser actualizado
 * \param limiteCli Limite del Clientes de Publicacion
 * \return Retorna int numero maximo de Publicaciones contratadas por el mismo cliente (EXITO) y -1 (ERROR)
 */
int info_DevolverCantMayorPublicaciones(Publicacion* arrayPubli,int limitePubli,Cliente* arrayCli,int limiteCli)
{
	int ret = -1;
	int i;
	int contPublicaciones;
	int max = 0;
	if(arrayPubli != NULL && limitePubli > 0 && arrayCli != NULL && limiteCli > 0)
	{
		for(i=0;i<limiteCli;i++)
		{
			if(arrayCli[i].isEmpty==FALSE)
			{
				contPublicaciones = publi_contarPublicacionesActivasPorID(arrayPubli, limitePubli, arrayCli[i].id);
				if(contPublicaciones > max)
				{
					max = contPublicaciones;
				}
			}
		}
		ret = max;
	}
	return ret;
}

/**
 * \brief Imprime los datos del Cliente con mas avisos publicados
 * \param arrayPubli Array de Publicacion a ser actualizado
 * \param limitePubli Limite del array de Publicacion
 * \param arrayCli Array de Clientes a ser actualizado
 * \param limiteCli Limite del Clientes de Publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int info_calculaClientesConMasAvisos(Publicacion* arrayPubli,int limitePubli,Cliente* arrayCli,int limiteCli)
{
	int ret = -1;
	int i;
	int contPublicaciones;
	int auxId;
	int auxMayor;
	if(arrayPubli != NULL && limitePubli > 0 && arrayCli != NULL && limiteCli > 0)
	{
		if(publi_checkListaVacia(arrayPubli, limitePubli)==-1)
		{
			printf("la lista de avisos esta vacia.\n");
		}
		else
		{
			ret=0;
			for(i=0;i<limiteCli;i++)
			{
				if(arrayCli[i].isEmpty==FALSE)
				{
					auxId = arrayCli[i].id;
					contPublicaciones = publi_contarPublicacionesActivasPorID(arrayPubli, limitePubli, auxId);
					auxMayor = info_DevolverCantMayorPublicaciones(arrayPubli, LENGTH_PUBLI, arrayCli, LENGTH_CLIENTE);
					if(contPublicaciones == auxMayor)
					{
						printf("ID:%d - Nombre:%s - Apellido:%s - Cuit:%s - Cantidad de Avisos:%d\n",
								arrayCli[i].id,
								arrayCli[i].nombre,
								arrayCli[i].apellido,
								arrayCli[i].cuit,
								contPublicaciones);
					}
				}
			}
		}
	}
	return ret;
}


