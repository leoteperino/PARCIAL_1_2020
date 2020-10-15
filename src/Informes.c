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
					//contPublicaciones es la cantidad de Publicaciones que tiene cada cliente
					/*Se la pasa como parametro el ID del array Cliente y despues compara que sea el mismo que el
					IdCliente del Array Publicaciones y los cuenta, eso me da la cantidad de Publicaciones, del Cliente
					que se le paso*/
					contPublicaciones = publi_contarPublicacionesPorID(arrayPubli, limitePubli, arrayCli[i].id);
					//Devuelve la Mayor Publicacion contada
					auxMayor = info_DevolverCantMayorPublicaciones(arrayPubli, limitePubli, arrayCli, limiteCli);
					//Comparo y si la mayor Publicacion coincide con alguna de las Publicaciones contadas, esa es la mayor.
					if(auxMayor == contPublicaciones)
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

/**
 * \brief Imprime la cantidad mayor de las publicaciones que tiene un id determinado.
 * \param arrayPubli Array de Publicacion a ser actualizado
 * \param limitePubli Limite del array de Publicacion
 * \param arrayCliente Array de clientes a ser actualizado
 * \param limiteCliente Limite del array cliente
 * \return Retorna int numero maximo de Publicaciones contratadas por el mismo id (EXITO) y -1 (ERROR)
 */
int info_DevolverCantMayorPublicaciones(Publicacion* arrayPubli,int limitePubli,Cliente* arrayCliente,int limiteCliente)
{
	int ret = -1;
	int i;
	int contPublicaciones;
	int max;
	if(arrayPubli != NULL && limitePubli > 0 && arrayCliente != NULL && limiteCliente > 0)
	{
		for(i=0;i<limiteCliente;i++)
		{
			if(arrayCliente[i].isEmpty==FALSE)
			{
				contPublicaciones = publi_contarPublicacionesPorID(arrayPubli, limitePubli, arrayCliente[i].id);
				if(i==0)
				{
					max = contPublicaciones;
				}
				else if(contPublicaciones > max)
				{
					max = contPublicaciones;
				}
			}
		}
		ret = max;
	}
	return ret;
}

/*********************************/
/*********************************/
/*Informe 3 Rubro con mas avisos*/
/*********************************/
/*********************************/
/**
 * \brief Inicializa la entidad Rubro y coloca todos los campos isEmpty vacios.
 * \param Rubro array de Rubros a ser inicializado
 * \param int Limite del array de rubros
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int info_inicializarRubro(Rubro* array,int limite)
{
	int ret = -1;
	int i;
	if(array!=NULL && limite>0)
	{
		for(i=0; i<limite; i++)
		{
			array[i].isEmpty = TRUE;
		}
		ret=0;
	}
	return ret;
}

/**
 * \brief Imprime la lista de Rubros
 * \param Rubro array de Rubros a ser inicializado
 * \param int Limite del array de rubros
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int info_imprimirListaRubros(Rubro* array, int limite)
{
	int ret = -1;
	int i;
	if(array!=NULL && limite>0)
	{
		for(i=0;i<limite;i++)
		{
			if(array[i].isEmpty == FALSE)
			{
				printf("Rubro: %d\n", array[i].rubro);
			}
		}
		ret = 0;
	}
	return ret;
}

/**
 * \brief Verifica si un rubro de la lista de Publicaciones se encuentra ya cargado en la lista de Rubros
 * \param Rubro array de Rubros a ser inicializado
 * \param int Limite del array de rubros
 * \return Retorna 0 si el rubro no esta cargado y 1 si el rubro ya esta cargado.
 */
int info_estaEnMiListaDeRubros(Rubro* array,int limite,int rubro)
{
	int ret=0;
	int i;
	if(array!=NULL && limite>0 && rubro>0)
	{
		for(i=0; i<limite; i++)
		{
			if(array[i].isEmpty==FALSE && array[i].rubro==rubro)
			{
				ret=1;
				break;
			}
		}
	}
	return ret;
}

/**
 * \brief Genera una lista de rubros unica sin rubros repetidos, estos rubros se cargan de la lista de publicaciones
 * \param Rubro arrayRubro array de Rubros a ser inicializado
 * \param int LimiteRubro limite del array de rubros
 * \param Publicacion arrayPubli array de Publicaciones
 * \return Retorna -1[ERROR] y 0[EXITO]
 */
int info_generarListaDeRubros(Rubro* arrayRubro,int limiteRubro,Publicacion* arrayPubli, int limitePubli)
{
	int ret = -1;
	if(arrayRubro!=NULL && limiteRubro>0 && arrayPubli!=NULL)
	{
		int indexPubli;
		int indexRubro=0;
		for(indexPubli=0;indexPubli<limitePubli;indexPubli++)
		{
			if(arrayPubli[indexPubli].isEmpty == FALSE)
			{
				if(info_estaEnMiListaDeRubros(arrayRubro, limiteRubro, arrayPubli[indexPubli].rubro)==0)
				{
					arrayRubro[indexRubro].rubro = arrayPubli[indexPubli].rubro;
					arrayRubro[indexRubro].isEmpty = FALSE;
					indexRubro++;
				}
			}
		}
		ret = 0;
	}
	return ret;
}

/**
 * \brief Cuenta la cantidad de publicaciones que tiene un determinado Rubro que se le pasa por parametro
 * \param Publicacion array Array de Publicacion a ser recorrido
 * \param limite int del array de Publicacion
 * \param rubro int rubro de publicacion.
 * \return Retorna la cantidad de Publicaciones resultado de la suma o -1 (ERROR)
 */
int info_contarPublicacionesPorRubro(Publicacion* array, int limite, int rubro)
{
	int ret = -1;
	int i;
	int contador = 0;
	if(array!=NULL && limite>0 && rubro>0)
	{
		for(i=0; i<limite; i++)
		{
			if((array[i].rubro == rubro) && (array[i].isEmpty == FALSE))
			{
				contador++;
			}
		}
		ret = contador;
	}
	return ret;
}


/**
 * \brief Imprime la cantidad mayor de las publicaciones que tiene un rubro determinado.
 * \param arrayPubli Array de Publicacion a ser actualizado
 * \param limitePubli Limite del array de Publicacion
 * \param arrayRubro Array de Rubros a ser actualizado
 * \param limiteRubro Limite del Rubros de Publicacion
 * \return Retorna int numero maximo de Publicaciones contratadas por el mismo Rubro (EXITO) y -1 (ERROR)
 */
int info_DevolverCantMayorPublicacionesPorRubros(Publicacion* arrayPubli,int limitePubli,Rubro* arrayRubro,int limiteRubro)
{
	int ret = -1;
	int i;
	int contPublicaciones;
	int max;
	if(arrayPubli != NULL && limitePubli > 0 && arrayRubro != NULL && limiteRubro > 0)
	{
		for(i=0;i<limiteRubro;i++)
		{
			if(arrayRubro[i].isEmpty==FALSE)
			{
				contPublicaciones = info_contarPublicacionesPorRubro(arrayPubli, LENGTH_PUBLI, arrayRubro[i].rubro);
				if(i==0)
				{
					max = contPublicaciones;
				}
				else if(contPublicaciones > max)
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
 * \brief Imprime los Rubros con mas avisos.
 * \param arrayPubli Array de Publicacion a ser actualizado
 * \param limitePubli Limite del array de Publicacion
 * \param arrayRubro Array de rubros a ser actualizado
 * \param limiteRubros Limite del array de rubros
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int info_calculaRubrosConMasAvisos(Publicacion* arrayPubli,int limitePubli,Rubro* arrayRubro,int limiteRubro)
{
	int ret = -1;
	int i;
	int contRubros;
	int auxMayor;
	if(arrayPubli != NULL && limitePubli > 0 && arrayRubro != NULL && limiteRubro > 0)
	{
		if(publi_checkListaVacia(arrayPubli, limitePubli)==-1)
		{
			printf("la lista de avisos esta vacia.\n");
		}
		else
		{
			ret=0;
			for(i=0;i<limiteRubro;i++)
			{
				if(arrayRubro[i].isEmpty==FALSE)
				{
					contRubros = info_contarPublicacionesPorRubro(arrayPubli, LENGTH_PUBLI, arrayRubro[i].rubro);
					auxMayor = info_DevolverCantMayorPublicacionesPorRubros(arrayPubli, limitePubli, arrayRubro, limiteRubro);
					if(contRubros == auxMayor)
					{
						printf("Rubro:%d - Cantidad de Avisos:%d\n",
								arrayRubro[i].rubro,
								contRubros);
					}
				}
			}
		}
	}
	return ret;
}

/**
 * \brief Imprime la cantidad mayor de las publicaciones activas que tiene un id determinado.
 * \param arrayPubli Array de Publicacion a ser actualizado
 * \param limitePubli Limite del array de Publicacion
 * \param arrayCliente Array de clientes a ser actualizado
 * \param limiteCliente Limite del array cliente
 * \return Retorna int numero maximo de Publicaciones contratadas por el mismo id (EXITO) y -1 (ERROR)
 */
int info_DevolverCantMayorPublicacionesActivas(Publicacion* arrayPubli,int limitePubli,Cliente* arrayCliente,int limiteCliente)
{
	int ret = -1;
	int i;
	int contPublicaciones;
	int max;
	if(arrayPubli != NULL && limitePubli > 0 && arrayCliente != NULL && limiteCliente > 0)
	{
		for(i=0;i<limiteCliente;i++)
		{
			if(arrayCliente[i].isEmpty==FALSE)
			{
				contPublicaciones = info_contarPublicacionesPorIDActivas(arrayPubli, limitePubli, arrayCliente[i].id);
				if(i==0)
				{
					max = contPublicaciones;
				}
				else if(contPublicaciones > max)
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
 * \brief Cuenta la cantidad de publicaciones activas que tiene un determinado Cliente, cuyo ID se le pasa por parametro
 * \param array Array de Publicacion a ser actualizado
 * \param limite int del array de Publicacion
 * \param idPublicacion int ID de la Publicacion
 * \return Retorna la cantidad de Publicaciones resultado de la suma o -1 (ERROR)
 */
int info_contarPublicacionesPorIDActivas(Publicacion* array, int limite, int id)
{
	int ret = -1;
	int i;
	int contador = 0;
	if(array!=NULL && limite>0 && id>0)
	{
		for(i=0; i<limite; i++)
		{
			if( (array[i].IdCliente == id) &&
				(array[i].isEmpty == FALSE) &&
				(array[i].estado == ESTADO_ACTIVA))
			{
				contador++;
			}
		}
		ret = contador;
	}
	return ret;
}

/**
 * \brief Imprime los datos del Cliente con mas avisos publicados y activos
 * \param arrayPubli Array de Publicacion a ser actualizado
 * \param limitePubli Limite del array de Publicacion
 * \param arrayCli Array de Clientes a ser actualizado
 * \param limiteCli Limite del Clientes de Publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int info_calculaClientesConMasAvisosActivos(Publicacion* arrayPubli,int limitePubli,Cliente* arrayCli,int limiteCli)
{
	int ret = -1;
	int i;
	int contPublicaciones;
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
					contPublicaciones = info_contarPublicacionesPorIDActivas(arrayPubli, limitePubli, arrayCli[i].id);
					auxMayor = info_DevolverCantMayorPublicaciones(arrayPubli, limitePubli, arrayCli, limiteCli);
					if(auxMayor == contPublicaciones)
					{
						printf("Nombre:%s - Apellido:%s - Cuit:%s - Cantidad de Avisos:%d\n",
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

/**
 * \brief Cuenta la cantidad de publicaciones activas que tiene un determinado Cliente, cuyo ID se le pasa por parametro
 * \param array Array de Publicacion a ser actualizado
 * \param limite int del array de Publicacion
 * \param idPublicacion int ID de la Publicacion
 * \return Retorna la cantidad de Publicaciones resultado de la suma o -1 (ERROR)
 */
int info_contarPublicacionesPorIDPausadas(Publicacion* array, int limite, int id)
{
	int ret = -1;
	int i;
	int contador = 0;
	if(array!=NULL && limite>0 && id>0)
	{
		for(i=0; i<limite; i++)
		{
			if( (array[i].IdCliente == id) &&
				(array[i].isEmpty == FALSE) &&
				(array[i].estado == ESTADO_PAUSADA))
			{
				contador++;
			}
		}
		ret = contador;
	}
	return ret;
}

/**
 * \brief Imprime la cantidad mayor de las publicaciones pausadas que tiene un id determinado.
 * \param arrayPubli Array de Publicacion a ser actualizado
 * \param limitePubli Limite del array de Publicacion
 * \param arrayCliente Array de clientes a ser actualizado
 * \param limiteCliente Limite del array cliente
 * \return Retorna int numero maximo de Publicaciones contratadas por el mismo id (EXITO) y -1 (ERROR)
 */
int info_DevolverCantMayorPublicacionesPausadas(Publicacion* arrayPubli,int limitePubli,Cliente* arrayCliente,int limiteCliente)
{
	int ret = -1;
	int i;
	int contPublicaciones;
	int max;
	if(arrayPubli != NULL && limitePubli > 0 && arrayCliente != NULL && limiteCliente > 0)
	{
		for(i=0;i<limiteCliente;i++)
		{
			if(arrayCliente[i].isEmpty==FALSE)
			{
				contPublicaciones = info_contarPublicacionesPorIDPausadas(arrayPubli, limitePubli, arrayCliente[i].id);
				if(i==0)
				{
					max = contPublicaciones;
				}
				else if(contPublicaciones > max)
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
 * \brief Imprime los datos del Cliente con mas avisos pausados
 * \param arrayPubli Array de Publicacion a ser actualizado
 * \param limitePubli Limite del array de Publicacion
 * \param arrayCli Array de Clientes a ser actualizado
 * \param limiteCli Limite del Clientes de Publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int info_calculaClientesConMasAvisosPausados(Publicacion* arrayPubli,int limitePubli,Cliente* arrayCli,int limiteCli)
{
	int ret = -1;
	int i;
	int contPublicaciones;
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
					contPublicaciones = info_contarPublicacionesPorIDPausadas(arrayPubli, LENGTH_PUBLI,arrayCli[i].id);
					auxMayor = info_DevolverCantMayorPublicacionesPausadas(arrayPubli, limitePubli, arrayCli, limiteCli);
					if(auxMayor == contPublicaciones)
					{
						printf("Nombre:%s - Apellido:%s - Cuit:%s - Cantidad de Avisos:%d\n",
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
