#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "utn.h"
#include "Cliente.h"
#include "Publicacion.h"

static int publi_generarNuevoId (void);

/**
 * \brief Genera un nuevo ID cada vez que se da de alta una Publicacion
 * \return Retorna el id que se genero.
 */
static int publi_generarNuevoId (void) {
	static int id = 0;
	id = id+1;
	return id;
}

/**
 * \brief Imprime el array de Publicaciones
 * \param array Array de Publicaciones a ser actualizado
 * \param limite Limite del array de Publicaciones
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int publi_imprimirArrayPublicacion(Publicacion* array,int limite)
{
	int ret = -1;
	int i;
	char strEstado[LENGTH_ESTADO];
	if(array != NULL && limite > 0)
	{
		if(publi_checkListaVacia(array, limite)==-1)
		{
			printf("La lista de Publicaciones esta vacia.");
		}
		else
		{
			publi_ordenarPublicacionID(array,limite);
			for(i=0;i<limite;i++)
			{
				if(array[i].isEmpty == FALSE)
				{
					if(array[i].estado==ESTADO_ACTIVA)
					{
						sprintf(strEstado,"Activa");
					}
					else
					{
						sprintf(strEstado,"Pausada");
					}
					printf("ID:%d - Rubro:%d - Texto:%s - Estado:%s - IdCliente:%d\n",
							array[i].id,
							array[i].rubro,
							array[i].texto,
							strEstado,
							array[i].IdCliente);
				}
			}
			ret = 0;
		}
	}
	return ret;
}

/**
 * \brief Inicializa el array
 * \param array Array de Publicacion a ser actualizado
 * \param limite Limite del array de Publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int publi_inicializarArrayPublicacion(Publicacion* array,int limite)
{
	int ret = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			array[i].isEmpty = TRUE;
			array[i].estado = ESTADO_ACTIVA;
		}
		ret = 0;
	}
	return ret;
}

/**
 * \brief Da de alta un Publicacion en una posicion del array y valida si el ID ingresado corresponde a una lista
 * \param array Array de Publicacion a ser actualizado
 * \param limite Limite del array de Publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int publi_altaArrayPublicacion(Publicacion* arrayPublicacion,int limitePublicacion,Cliente* arrayCliente, int limiteCliente)
{
	int ret = -1;
	Publicacion bufferPublicacion;
	int auxIndice;
	int auxIndiceCliente;
	if(arrayPublicacion != NULL && limitePublicacion > 0 && arrayCliente != NULL && limiteCliente > 0)
	{
		auxIndice = publi_getEmptyIndexPublicacion(arrayPublicacion,limitePublicacion);
		if(auxIndice>=0)
		{
			printf("\nLista de Clientes:");
			if(!cliente_imprimirArrayCliente(arrayCliente, limiteCliente))
			{
				if(!utn_getNumero(&bufferPublicacion.IdCliente,"\nIngrese el ID del Cliente para publicar: ","ERROR",MIN_ID,MAX_ID,QTY_REINT))
				{
					auxIndiceCliente = cliente_buscarIdCliente(arrayCliente, limiteCliente, bufferPublicacion.IdCliente);
					if(auxIndiceCliente>=0)
					{
						if( !utn_getNumero(&bufferPublicacion.rubro,"Ingrese el Rubro: ","ERROR",MIN_RUBRO,MAX_RUBRO,QTY_REINT) &&
							!utn_getTexto(bufferPublicacion.texto,LENGTH_TEXTO,"Ingrese el texto: ","ERROR",QTY_REINT))
						{
							bufferPublicacion.id = publi_generarNuevoId();
							bufferPublicacion.isEmpty = FALSE;
							bufferPublicacion.estado = ESTADO_ACTIVA;
							arrayPublicacion[auxIndice] = bufferPublicacion;
							printf("La Publicacion se dio de alta con exito!!\n");
							publi_imprimirArrayPublicacionPorID(arrayPublicacion, limitePublicacion, bufferPublicacion.id);
							ret = 0;
						}
						else
						{
							printf("No hay lugares vacios en el Array.\n");
						}
					}
					else
					{
						printf("No se encuentra el ID ingresado.\n");
					}
				}
			}
		}
		else
		{
			printf("No hay lugares vacios en el Array.\n");
		}
	}
	return ret;
}

/**
 * \brief Imprime una Publicacion por su numero de ID que se pasa como parametro
 * \param array Array de Publicacion a ser actualizado
 * \param limite Limite del array de Publicacion
 * \param id ID a ser buscado
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int publi_imprimirArrayPublicacionPorID(Publicacion* array,int limite, int id)
{
	int ret = -1;
	int i;
	char strEstado[LENGTH_ESTADO];
	if(array != NULL && limite > 0)
	{
		if(publi_checkListaVacia(array, limite)==-1)
		{
			printf("La lista de Publicaciones esta vacia.");
		}
		else
		{
			publi_ordenarPublicacionID(array,limite);
			for(i=0;i<limite;i++)
			{
				if(array[i].isEmpty == FALSE && array[i].id == id)
				{
					if(array[i].estado==ESTADO_ACTIVA)
					{
						sprintf(strEstado,"Activa");
					}
					else
					{
						sprintf(strEstado,"Pausada");
					}
					printf("ID:%d - Rubro:%d - Texto:%s - Estado:%s - IdCliente:%d\n",
							array[i].id,
							array[i].rubro,
							array[i].texto,
							strEstado,
							array[i].IdCliente);
				}
			}
			ret = 0;
		}
	}
	return ret;
}

/**
 * \brief Imprime los datos del Cliente al cual le pertenece una publicacion pasando ID de publicacion
 * \param arrayPubli Array de Publicacion a ser actualizado
 * \param limitePubli Limite del array de Publicacion
 * \param arrayCli Array de Clientes a ser actualizado
 * \param limiteCli Limite del Clientes de Publicacion
 * \param idPublicacion int ID de la Publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int publi_imprimirClientexIdPublicacion(Publicacion* arrayPubli,int limitePubli,Cliente* arrayCli,int limiteCli, int idPublicacion)
{
	int ret = -1;
	int i;
	int auxIdCliente;
	int auxIndice_Cliente;
	if(arrayPubli != NULL && limitePubli > 0 && arrayCli != NULL && limiteCli > 0 && idPublicacion > 0)
	{
		for(i=0;i<limitePubli;i++)
		{
			auxIdCliente = publi_devolverIdClientePorIdPublicacion(arrayPubli, limitePubli, idPublicacion);
			if((arrayPubli[i].isEmpty == FALSE) &&
			   (arrayPubli[i].IdCliente == auxIdCliente))
			{
				auxIndice_Cliente = cliente_buscarIdCliente(arrayCli, limiteCli, arrayPubli[i].IdCliente);
				if(auxIndice_Cliente >= 0)
				{
					printf("Nombre:%s - Apellido:%s - Cuit:%s\n",
							arrayCli[auxIndice_Cliente].nombre,
							arrayCli[auxIndice_Cliente].apellido,
							arrayCli[auxIndice_Cliente].cuit);
					break;
				}
			}
		}
		ret=0;
	}
	return ret;
}

/**
 * \brief recorre las publicaciones por el ID pasado por parametro y Devuelve el valor del campo idCliente de dicha publicacion.
 * \param arrayPubli Array de Publicacion a ser actualizado
 * \param limite int del array de Publicacion
 * \param idPublicacion int ID de la Publicacion
 * \return Retorna el volor del campo idCliente o -1 (ERROR)
 */
int publi_devolverIdClientePorIdPublicacion(Publicacion* array, int limite, int idPublicacion)
{
	int ret=-1;
	int i;
	int auxIdCliente;
	if(array != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if((array[i].id == idPublicacion) && (array[i].isEmpty == FALSE))
			{
				auxIdCliente = array[i].IdCliente;
				break;
			}
		}
		ret = auxIdCliente;
	}
	return ret;
}

/**
 * \brief Actualiza el estado a Pausada de una publicacion cuyo ID se recibe por parametro
 * \param array Array de Publicacion a ser actualizado
 * \param limite Limite del array de Publicacion
 * \param ID de la publicacon a actualizar
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int publi_PausarPublicacion(Publicacion* array, int limite, int id)
{
	int ret = -1;
	int i;
	Publicacion bufferPublicacion;
	char auxChar;
	if(array != NULL && limite > 0 && id > 0)
	{
		if(!utn_getCaracterSN(&auxChar,LEN_CHAR,
							  "Confirma el cambio de estado a pausada de esta publicacion?[S/N]:",
							  "ERROR\n",QTY_REINT))
		{
			switch(auxChar)
			{
			 	 case 's':
			 	 case 'S':
			 		for(i=0;i<limite;i++)
					{
						if(array[i].id == id)
						{
							bufferPublicacion.id = array[i].id;
							bufferPublicacion.rubro=array[i].rubro;
							strncpy(bufferPublicacion.texto,array[i].texto,LENGTH_TEXTO);
							bufferPublicacion.estado =  ESTADO_PAUSADA;
							bufferPublicacion.IdCliente = array[i].IdCliente;
							bufferPublicacion.isEmpty = array[i].isEmpty;
							array[i] = bufferPublicacion;
							ret = 0;
						}
					}
			 		printf("La publicacion ha sido pausada.\n");
			 		break;
			 	case 'n':
			 	case 'N':
			 		break;
			}
		}
	}
	return ret;
}

/**
 * \brief Actualiza el estado a Activada de una publicacion cuyo ID se recibe por parametro
 * \param array Array de Publicacion a ser actualizado
 * \param limite Limite del array de Publicacion
 * \param ID de la publicacon a actualizar
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int publi_ActivarPublicacion(Publicacion* array, int limite, int id)
{
	int ret = -1;
	int i;
	Publicacion bufferPublicacion;
	char auxChar;
	if(array != NULL && limite > 0 && id > 0)
	{
		if(!utn_getCaracterSN(&auxChar,LEN_CHAR,
							  "Confirma el cambio de estado a activada de esta publicacion?[S/N]:",
							  "ERROR\n",QTY_REINT))
		{
			switch(auxChar)
			{
			 	 case 's':
			 	 case 'S':
			 		for(i=0;i<limite;i++)
					{
						if(array[i].id == id)
						{
							bufferPublicacion.id = array[i].id;
							bufferPublicacion.rubro=array[i].rubro;
							strncpy(bufferPublicacion.texto,array[i].texto,LENGTH_TEXTO);
							bufferPublicacion.estado =  ESTADO_ACTIVA;
							bufferPublicacion.IdCliente = array[i].IdCliente;
							bufferPublicacion.isEmpty = array[i].isEmpty;
							array[i] = bufferPublicacion;
							ret = 0;
						}
					}
			 		printf("La publicacion ha sido activada.\n");
			 		break;
			 	case 'n':
			 	case 'N':
			 		break;
			}
		}
	}
	return ret;
}

/**
 * \brief Actualiza los datos del estado de una Publicacion a activa
 * \param array Array de Publicacion a ser actualizado
 * \param limite Limite del array de Publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int publi_ActivarArrayPublicacion(Publicacion* array,int limite)
{
	int ret = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			array[i].estado = ESTADO_PAUSADA;
			ret = 0;
		}
	}
	return ret;
}

/**
* \brief Busca un ID en un array y devuelve la posicion en que se encuentra
* \param array Publicacion Array de Publicacion
* \param limite int Tamaño del array
* \param posicion int* Puntero a la posicion del array donde se encuentra el valor buscado
* \return int Return (-1) si no encuentra el valor buscado o Error [Invalid length or NULL pointer] - (0) si encuentra el valor buscado
*/
int publi_buscarIdPublicacion(Publicacion* array, int limite, int valorBuscado)
{
	int ret = -1;
	int i;
	if(array != NULL && limite > 0 && valorBuscado >= 0)
	{
		for(i=0;i<limite;i++)
		{
			if(array[i].isEmpty==FALSE && array[i].id == valorBuscado)
			{
				ret = i;
				break;
			}
		}
	}
	return ret;
}

/**
 * \brief Buscar primer posicion vacia
 * \param array Array de Publicacion
 * \param limite Limite del array de Publicacion
 * \return Retorna el incice de la posicion vacia y -1 (ERROR)
 */
int publi_getEmptyIndexPublicacion(Publicacion* array,int limite)
{
	int ret = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			if(array[i].isEmpty == TRUE)
			{
				ret = i;
				break;
			}
		}
	}
	return ret;
}

/**
 * \brief Ordenar el array de Publicacion por ID ascendente
 * \param array Array de Publicacion
 * \param limite Limite del array de Publicacion
 * \return Retorna el incice de la posicion vacia y -1 (ERROR)
 */
int publi_ordenarPublicacionID(Publicacion* array,int limite)
{
	int ret = -1;
	int flagSwap;
	int i;
	Publicacion buffer;
	if(array != NULL && limite > 0)
	{
		do
		{
			flagSwap = 0;
			for(i=0;i<limite-1;i++)
			{
				if(array[i].isEmpty || array[i+1].isEmpty)
				{
					continue;
				}
				if(array[i].id > array[i+1].id)
				{
					flagSwap = 1;
					buffer = array[i];
					array[i] = array[i+1];
					array[i+1]=buffer;
				}
			}
			limite--;
		}while(flagSwap);
	}
	return ret;
}

/**
 * \brief Ordenar el array de Publicacion por un doble criterio ascendente o descendente
 * \param array Array de Publicacion
 * \param len int Limite del array de Publicacion
 * \param orden int [1]-Indica ascendente - [0]-Indica Descendente
 * \return Retorna el incice de la posicion vacia y -1 (ERROR)
 */
int publi_ordenarPublicacionDobleCriterio(Publicacion* list, int len, int order)
{
	int ret=-1;
	int flagSwap;
	int i;
	Publicacion buffer;
	if(list!=NULL && len>0)
	{
		do
		{
			flagSwap = 0;
			for(i=0;i<len-1;i++)
			{
				if(
					(order==1 && strncmp(list[i].texto,list[i+1].texto,ARRAY_LEN_NOMBRE)>0) ||
				    ((order==1 && strncmp(list[i].texto,list[i+1].texto,ARRAY_LEN_NOMBRE)==0) &&
				    (list[i].estado > list[i+1].estado)) ||
				    (order==0 && strncmp(list[i].texto,list[i+1].texto,ARRAY_LEN_NOMBRE) < 0) ||
				    ((order==0 && strncmp(list[i].texto,list[i+1].texto,ARRAY_LEN_NOMBRE) == 0) &&
				    (list[i].estado < list[i+1].estado)))
				{
					flagSwap = 1;
					buffer = list[i];
					list[i] = list[i+1];
					list[i+1]=buffer;
				}
			}
			len--;
		}while(flagSwap);
	}
	return ret;
}

/**
 * \brief Chequea que la lista de Publicaciones este cargada
 * \param array Array de Publicaciones a ser actualizado
 * \param int len longitud del array de entidades
 * \return Retorna 0, si la lista esta con al menos 1 entidad y -1 si la lista esta vacia.
 */
int publi_checkListaVacia(Publicacion* list, int len)
{
	int ret=-1;
	int contador = 0;
	int i;
	if(list!=NULL && len>0)
	{
		for(i=0;i<len;i++)
		{
			if(list[i].isEmpty==FALSE)
			{
				contador++;
			}
		}
		if(contador>0)
		{
			ret=0;
		}
	}
	return ret;
}

/**
 * \brief Da de alta una Publicacion en una posicion del array
 * \param array Array de Publicacion a ser actualizado
 * \param limite Limite del array de Publicacion
 * \param indice Posicion a ser actualizada
 * \param id Identificador a ser asignado a la Publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int publi_mocksPublicacion(Publicacion* array,int limite,int rubro,char* texto,int idCliente)
{
	int ret = -1;
	Publicacion bufferPublicacion;
	int auxIndice;
	if(array != NULL && limite > 0)
	{
		auxIndice = publi_getEmptyIndexPublicacion(array,limite);
		if(auxIndice>=0)
		{
		    bufferPublicacion.id = publi_generarNuevoId();
		    bufferPublicacion.rubro = rubro;
		    strncpy(bufferPublicacion.texto,texto,LENGTH_TEXTO);
			bufferPublicacion.estado = ESTADO_ACTIVA;
			bufferPublicacion.IdCliente = idCliente;
			bufferPublicacion.isEmpty = FALSE;
			array[auxIndice] = bufferPublicacion;
			ret = 0;
		}
	}
	return ret;
}

/**
 * \brief Imprime el array de Publicaciones del ID pasado por parametro
 * \param array Array de Publicaciones a ser actualizado
 * \param limite Limite del array de Publicaciones
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int publi_imprimirArrayPublicacionPorIDCliente(Publicacion* array,int limite,int id)
{
	int ret = -1;
	int i;
	int contPublicaciones = 0;
	char strEstado[LENGTH_ESTADO];
	if(array != NULL && limite > 0 && id>0)
	{
		publi_ordenarPublicacionID(array,limite);
		for(i=0;i<limite;i++)
		{
			if(array[i].isEmpty == FALSE && array[i].IdCliente == id)
			{
				if(array[i].estado==ESTADO_ACTIVA)
				{
					sprintf(strEstado,"Activa");
				}
				else
				{
					sprintf(strEstado,"Pausada");
				}
				printf("Rubro:%d - Texto:%s - Estado:%s\n",
						array[i].rubro,
						array[i].texto,
						strEstado);
				contPublicaciones++;
			}
		}
		if(!contPublicaciones)
		{
			printf("Este cliente no tiene publicaciones.\n");
		}
		ret=0;
	}
	return ret;
}

/**
 * \brief da de baja una Publicacion, se le pasa un id por parametro
 * \param array Array de Publicacion a ser borrada
 * \param limite Limite del array de Publicacion
 * \param indice es la posicion del ID a borrar
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int publi_bajaArrayPublicacion(Publicacion* array,int limite, int idCliente)
{
	int ret = -1;
	int i;
	if(array != NULL && limite > 0 && idCliente > 0)
	{
		for(i=0; i<limite; i++)
		{
			if(array[i].isEmpty==FALSE && array[i].IdCliente == idCliente)
			{
				array[i].isEmpty = TRUE;
			}
		}
		ret=0;
	}
	return ret;
}

/**
 * \brief Imprime el array de Publicaciones activas
 * \param array Array de Publicaciones a ser actualizado
 * \param limite Limite del array de Publicaciones
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int publi_imprimirArrayPublicacionActivas(Publicacion* array,int limite)
{
	int ret = -1;
	int i;
	char strEstado[LENGTH_ESTADO];
	if(array != NULL && limite > 0)
	{
		if(publi_checkListaVacia(array, limite)==-1)
		{
			printf("La lista de Publicaciones esta vacia.");
		}
		else
		{
			publi_ordenarPublicacionID(array,limite);
			for(i=0;i<limite;i++)
			{
				if((array[i].isEmpty == FALSE) && (array[i].estado == ESTADO_ACTIVA))
				{
					if(array[i].estado==ESTADO_ACTIVA)
					{
						sprintf(strEstado,"Activa");
					}
					else
					{
						sprintf(strEstado,"Pausada");
					}
					printf("ID:%d - Rubro:%d - Texto:%s - Estado:%s - IdCliente:%d\n",
							array[i].id,
							array[i].rubro,
							array[i].texto,
							strEstado,
							array[i].IdCliente);
					ret = 0;
				}
			}
		}
	}
	return ret;
}

/**
 * \brief Imprime el array de Publicaciones Pausadas
 * \param array Array de Publicaciones a ser actualizado
 * \param limite Limite del array de Publicaciones
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int publi_imprimirArrayPublicacionPausadas(Publicacion* array,int limite)
{
	int ret = -1;
	int i;
	char strEstado[LENGTH_ESTADO];
	if(array != NULL && limite > 0)
	{
		if(publi_checkListaVacia(array, limite)==-1)
		{
			printf("La lista de Publicaciones esta vacia.");
		}
		else
		{
			publi_ordenarPublicacionID(array,limite);
			for(i=0;i<limite;i++)
			{
				if((array[i].isEmpty == FALSE) && (array[i].estado == ESTADO_PAUSADA))
				{
					if(array[i].estado==ESTADO_ACTIVA)
					{
						sprintf(strEstado,"Activa");
					}
					else
					{
						sprintf(strEstado,"Pausada");
					}
					printf("ID:%d - Rubro:%d - Texto:%s - Estado:%s - IdCliente:%d\n",
							array[i].id,
							array[i].rubro,
							array[i].texto,
							strEstado,
							array[i].IdCliente);
					ret = 0;
				}
			}
		}
	}
	return ret;
}

/**
 * \brief Imprime los datos del Cliente y la cantidad de publicaciones activas
 * \param arrayPubli Array de Publicacion a ser actualizado
 * \param limitePubli Limite del array de Publicacion
 * \param arrayCli Array de Clientes a ser actualizado
 * \param limiteCli Limite del Clientes de Publicacion
 * \param idPublicacion int ID de la Publicacion
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int publi_imprimirCantidadPublicacionesDeClientes(Publicacion* arrayPubli,int limitePubli,Cliente* arrayCli,int limiteCli)
{
	int ret = -1;
	int i;
	int contPublicaciones;
	if(arrayPubli != NULL && limitePubli > 0 && arrayCli != NULL && limiteCli > 0)
	{
		for(i=0;i<limiteCli;i++)
		{
			if(arrayCli[i].isEmpty==FALSE)
			{
				contPublicaciones = publi_contarPublicacionesActivasPorID(arrayPubli, limitePubli, arrayCli[i].id);
				if(contPublicaciones!=0)
				{
					printf("ID:%d - Nombre:%s - Apellido:%s - Cuit:%s - Cantidad de Avisos Activos:%d\n",
							arrayCli[i].id,
							arrayCli[i].nombre,
							arrayCli[i].apellido,
							arrayCli[i].cuit,
							contPublicaciones);
				}
			}
		}
		ret=0;
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
int publi_contarPublicacionesActivasPorID(Publicacion* array, int limite, int id)
{
	int ret = -1;
	int i;
	int contador = 0;
	if(array!=NULL && limite>0 && id>0)
	{
		for(i=0; i<limite; i++)
		{
			if((array[i].IdCliente == id) && (array[i].isEmpty == FALSE) &&
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
 * \brief Cuenta la cantidad de publicaciones que tiene un determinado Cliente, cuyo ID se le pasa por parametro
 * \param array Array de Publicacion a ser actualizado
 * \param limite int del array de Publicacion
 * \param idPublicacion int ID de la Publicacion
 * \return Retorna la cantidad de Publicaciones resultado de la suma o -1 (ERROR)
 */
int publi_contarPublicacionesPorID(Publicacion* array, int limite, int id)
{
	int ret = -1;
	int i;
	int contador = 0;
	if(array!=NULL && limite>0 && id>0)
	{
		for(i=0; i<limite; i++)
		{
			if((array[i].IdCliente == id) && (array[i].isEmpty == FALSE))
			{
				contador++;
			}
		}
		ret = contador;
	}
	return ret;
}












