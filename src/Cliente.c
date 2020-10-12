#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "Cliente.h"
#include "Publicacion.h"
#include "utn.h"

static int cliente_generarNuevoId (void);

/**
 * \brief Genera un nuevo ID cada vez que se da de alta una Cliente
 * \return Retorna el id que se genero.
 */
static int cliente_generarNuevoId (void) {
	static int id = 0;
	id = id+1;
	return id;
}

/**
 * \brief Imprime el array de Clientees
 * \param array Array de Clientees a ser actualizado
 * \param limite Limite del array de Clientees
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 *
 */
int cliente_imprimirArrayCliente(Cliente* array,int limite)
{
	int ret = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		if(cliente_checkListaVacia(array, limite)==-1)
		{
			printf("\nLa lista de Clientes esta vacia.");
		}
		else
		{
			cliente_ordenarClienteID(array,limite);
			for(i=0;i<limite;i++)
			{
				if(array[i].isEmpty == FALSE)
				{
					printf("\nID:%d - Nombre: %s - Apellido: %s - Cuit: %s",
							array[i].id,
							array[i].nombre,
							array[i].apellido,
							array[i].cuit);
				}
			}
			ret = 0;
		}
	}
	return ret;
}

/**
 * \brief Inicializa el array
 * \param array Array de Cliente a ser actualizado
 * \param limite Limite del array de Cliente
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int cliente_inicializarArrayCliente(Cliente* array,int limite)
{
	int ret = -1;
	int i;
	if(array != NULL && limite > 0)
	{
		for(i=0;i<limite;i++)
		{
			array[i].isEmpty = TRUE;
		}
		ret = 0;
	}
	return ret;
}

/**
 * \brief Da de alta un Cliente en una posicion del array
 * \param array Array de Cliente a ser actualizado
 * \param limite Limite del array de Cliente
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int cliente_altaArrayCliente(Cliente* array,int limite)
{
	int ret = -1;
	Cliente bufferCliente;
	int auxIndice;
	if(array != NULL && limite > 0)
	{
		auxIndice = cliente_getEmptyIndexCliente(array,limite);
		if(auxIndice>=0)
		{
			if( !utn_getNombre(bufferCliente.nombre,LENGTH_NOMBRE,"\nIngrese Nombre: ","ERROR, nombre invalido.\n",QTY_REINT) &&
				!utn_getApellido(bufferCliente.apellido,LENGTH_APELLIDO,"Ingrese Apellido: ","ERROR, apellido invalido.\n",QTY_REINT) &&
				!utn_getCuit(bufferCliente.cuit,LENGTH_CUIT,"Ingrese su Cuit [xx-xxxxxxxx-x]: ", "ERROR, cuit invalido.\n",QTY_REINT))
			{
				bufferCliente.id = cliente_generarNuevoId();
				bufferCliente.isEmpty = FALSE;
				array[auxIndice] = bufferCliente;
				printf("El Cliente se dio de alta con exito!!\n");
				cliente_imprimirClientePorID(array, limite, bufferCliente.id);
				ret = 0;
			}
			else
			{
				printf("Se acabaron tus reintentos.\n");
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
 * \brief Actualiza los datos de un Cliente en una posicion del array
 * \param array Array de Cliente a ser actualizado
 * \param limite Limite del array de Cliente
 * \param indice es la posicion del ID a modificar
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int cliente_modificarArrayCliente(Cliente* array,int limite, int indice)
{
	int ret = -1;
	Cliente bufferCliente;;
	if(array != NULL && limite > 0 && indice>=0)
	{
		if(	!utn_getNombre(bufferCliente.nombre,LENGTH_NOMBRE,"Ingrese nuevo Nombre: ","ERROR, nombre invalido.\n",QTY_REINT) &&
			!utn_getApellido(bufferCliente.apellido,LENGTH_APELLIDO,"Ingrese nuevo Apellido: ","ERROR, apellido invalido.\n",QTY_REINT) &&
			!utn_getCuit(bufferCliente.cuit,LENGTH_CUIT,"Ingrese nuevo Cuit [xx-xxxxxxxx-x]: ", "ERROR, cuit invalido.\n",QTY_REINT))
		{
			bufferCliente.id = array[indice].id;
			bufferCliente.isEmpty = FALSE;
			array[indice] = bufferCliente;
			ret = 0;
		}
		else
		{
			printf("No se encontro el ID ingresado.\n");
		}
	}
	return ret;
}

/**
 * \brief Actualiza una posicion del array
 * \param array Array de Cliente a ser actualizado
 * \param limite Limite del array de Cliente
 * \param indice es la posicion del ID a borrar
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int cliente_bajaArrayCliente(Cliente* array,int limite, int indice)
{
	int ret = -1;
	char auxChar;
	if(array != NULL && limite > 0 && indice >=0)
	{
		if(!utn_getCaracterSN(&auxChar,LEN_CHAR,
							  "Esta seguro que desea borrar este Cliente y todas sus publicaciones?[S/N]:",
							  "ERROR\n",QTY_REINT))
		{
			switch(auxChar)
			{
				 case 'S':
				 case 's':
					 array[indice].isEmpty = TRUE;
					 ret = 0;
					break;
				 case 'N':
				 case 'n':
					 break;
			}
		}
	}
	return ret;
}

/**
* \brief Busca un ID en un array y devuelve la posicion en que se encuentra
* \param array Cliente Array de Cliente
* \param limite int Tamaño del array
* \param posicion int* Puntero a la posicion del array donde se encuentra el valor buscado
* \return int Return (-1) si no encuentra el valor buscado o Error [Invalid length or NULL pointer] - (0) si encuentra el valor buscado
*/
int cliente_buscarIdCliente(Cliente* array, int limite, int valorBuscado)
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
 * \param array Array de Cliente
 * \param limite Limite del array de Cliente
 * \return Retorna el incice de la posicion vacia y -1 (ERROR)
 */
int cliente_getEmptyIndexCliente(Cliente* array,int limite)
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
 * \brief Ordenar el array de Cliente por ID ascendente
 * \param array Array de Cliente
 * \param limite Limite del array de Cliente
 * \return Retorna el incice de la posicion vacia y -1 (ERROR)
 */
int cliente_ordenarClienteID(Cliente* array,int limite)
{
	int ret = -1;
	int flagSwap;
	int i;
	Cliente buffer;
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
 * \brief Ordenar el array de Cliente por un doble criterio ascendente o descendente
 * \param array Array de Cliente
 * \param len int Limite del array de Cliente
 * \param orden int [1]-Indica ascendente - [0]-Indica Descendente
 * \return Retorna el incice de la posicion vacia y -1 (ERROR)
 */
int cliente_ordenarClienteDobleCriterio(Cliente* list, int len, int order)
{
	int ret=-1;
	int flagSwap;
	int i;
	Cliente buffer;
	if(list!=NULL && len>0)
	{
		do
		{
			flagSwap = 0;
			for(i=0;i<len-1;i++)
			{
				if(
					(order==1 && strncmp(list[i].nombre,list[i+1].nombre,ARRAY_LEN_NOMBRE)>0) ||
				    ((order==1 && strncmp(list[i].nombre,list[i+1].nombre,ARRAY_LEN_NOMBRE)==0) &&
				    (list[i].id > list[i+1].id)) ||
				    (order==0 && strncmp(list[i].nombre,list[i+1].nombre,ARRAY_LEN_NOMBRE) < 0) ||
				    ((order==0 && strncmp(list[i].nombre,list[i+1].nombre,ARRAY_LEN_NOMBRE) == 0) &&
				    (list[i].id < list[i+1].id)))
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
 * \brief Chequea que la lista de Clientees este cargada
 * \param array Array de Clientees a ser actualizado
 * \param int len longitud del array de entidades
 * \return Retorna 0, si la lista esta con al menos 1 campo y -1 si la lista esta vacia.
 */
int cliente_checkListaVacia(Cliente* list, int len)
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
 * \brief Da de alta una Cliente en una posicion del array
 * \param array Array de Cliente a ser actualizado
 * \param limite Limite del array de Cliente
 * \param indice Posicion a ser actualizada
 * \param id Identificador a ser asignado a la Cliente
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int cliente_mocksCliente(Cliente* array,int limite,char* nombre,char* apellido, char* cuit)
{
	int ret = -1;
	Cliente bufferCliente;
	int auxIndice;
	if(array != NULL && limite > 0)
	{
		auxIndice = cliente_getEmptyIndexCliente(array, limite);
		if(auxIndice>=0)
		{
		    bufferCliente.id = cliente_generarNuevoId();
			strncpy(bufferCliente.nombre,nombre,LENGTH_NOMBRE);
			strncpy(bufferCliente.apellido,apellido,LENGTH_APELLIDO);
			strncpy(bufferCliente.cuit,cuit,LENGTH_CUIT);
			bufferCliente.isEmpty = 0;
			array[auxIndice] = bufferCliente;
			ret = 0;
		}
	}
	return ret;
}

/**
 * \brief Imprime un cliente por su numero de ID que se pasa como parametro
 * \param array Array de Cliente a ser actualizado
 * \param limite Limite del array de Cliente
 * \param id ID a ser buscado
 * \return Retorna 0 (EXITO) y -1 (ERROR)
 */
int cliente_imprimirClientePorID(Cliente* array, int limite,int id)
{
	int ret = -1;
	int i;
	if(array!=NULL && limite>0 && id>0)
	{
		for(i=0;i<limite;i++)
		{
			if(array[i].id == id)
			{
				printf("ID: %d - Nombre: %s - Apellido: %s - Cuit: %s",
						array[i].id,
						array[i].nombre,
						array[i].apellido,
						array[i].cuit);
			}
		}
		ret=0;
	}
	return ret;
}


















