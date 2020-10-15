/*
 ============================================================================
 Name        : Parcial1_2020.c
 Author      : Leandro Teperino
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio_ext.h>
#include "Cliente.h"
#include "Publicacion.h"
#include "utn.h"
#include "Informes.h"

int main(void) {
	//Declaracion de variables y arrays
	Cliente clientes[LENGTH_CLIENTE];
	Publicacion publicaciones[LENGTH_PUBLI];
	Rubro rubros[LENGTH_RUBROS];
	int optionMenu;
	int auxId;
	int auxIndice;
	int cantAvisosPausados;
	//Inicalizacion
	cliente_inicializarArrayCliente(clientes,LENGTH_CLIENTE);
	publi_inicializarArrayPublicacion(publicaciones, LENGTH_PUBLI);
	info_inicializarRubro(rubros, LENGTH_RUBROS);
	//Mocks Fantasmas
	cliente_mocksCliente(clientes, LENGTH_CLIENTE,"Cliente1", "Apellido1", "00-00000000-1");
	cliente_mocksCliente(clientes, LENGTH_CLIENTE,"Cliente2", "Apellido2", "00-00000000-2");
	cliente_mocksCliente(clientes, LENGTH_CLIENTE,"Cliente3", "Apellido3", "00-00000000-3");
	cliente_mocksCliente(clientes, LENGTH_CLIENTE,"Cliente4", "Apellido4", "00-00000000-4");
	cliente_mocksCliente(clientes, LENGTH_CLIENTE,"Cliente5", "Apellido5", "00-00000000-5");
	//Mocks Publicaciones
	publi_mocksPublicacion(publicaciones,LENGTH_PUBLI,1,"Texto 1",4);
	publi_mocksPublicacion(publicaciones,LENGTH_PUBLI,2,"Texto 2",3);
	publi_mocksPublicacion(publicaciones,LENGTH_PUBLI,3,"Texto 3",4);
	publi_mocksPublicacion(publicaciones,LENGTH_PUBLI,4,"Texto 4",1);
	publi_mocksPublicacion(publicaciones,LENGTH_PUBLI,6,"Texto 5",1);
	publi_mocksPublicacion(publicaciones,LENGTH_PUBLI,6,"Texto 6",1);
	//Menu Principal
	do
	{
		if(!utn_getNumero(   &optionMenu,
							"\n*****Menu de Opciones*****\n"
							"1 - Alta de clientes\n"
							"2 - Modificar datos de cliente\n"
							"3 - Baja de un cliente\n"
							"4 - Publicar\n"
							"5 - Pausar publicacion\n"
							"6 - Reanudar publicacion\n"
							"7 - Imprimir clientes\n"
							"8 - Informar\n"
							"-----------------------------\n"
							"Elija una opcion del menu: ",
							"ERROR",MIN_OPTION_MENU,MAX_OPTION_MENU,QTY_REINT))
		{
			switch(optionMenu)
			{
				case 1:
					printf("\n***************************************\n");
					printf("Alta de Clientes:");
					cliente_altaArrayCliente(clientes, LENGTH_CLIENTE);
					printf("\n***************************************\n");
					break;
				case 2:
					printf("\n***************************************\n");
					printf("Modificar datos del Cliente");
					if(cliente_checkListaVacia(clientes, LENGTH_CLIENTE)==-1)
					{
						printf("\nLa lista de clientes esta vacia.\n");
					}
					else
					{
						cliente_imprimirArrayCliente(clientes, LENGTH_CLIENTE);
						if(!utn_getNumero(&auxId,"\nSeleccione el ID del cliente a modificar: ","ERROR",
						   MIN_ID,MAX_ID,QTY_REINT))
						{
							auxIndice = cliente_buscarIdCliente(clientes,LENGTH_CLIENTE,auxId);
							if(auxIndice>=0)
							{
								if(!cliente_modificarArrayCliente(clientes,LENGTH_CLIENTE,auxIndice))
								{
									printf(	"El cliente se modifico con exito!!\n"
											"Lista actualizada de Clientes:");
									        cliente_imprimirArrayCliente(clientes, LENGTH_CLIENTE);
								}
							}
							else
							{
								printf("No se encontro el ID ingresado.\n");
							}
						}
						else
						{
							printf("Se acabaron tus reintentos.\n");
						}
					}
					printf("\n***************************************\n");
					break;
				case 3:
					printf("\n***************************************\n");
					printf("Baja de Cliente:\n");
					if(cliente_checkListaVacia(clientes, LENGTH_CLIENTE)==-1)
					{
						printf("La lista de clientes esta vacia.\n");
					}
					else
					{
						printf("Lista de Clientes:");
						cliente_imprimirArrayCliente(clientes, LENGTH_CLIENTE);
						if(!utn_getNumero(&auxId,"\nIngrese el ID del cliente a dar de baja: ","ERROR",MIN_ID,MAX_ID,QTY_REINT))
						{
							auxIndice = cliente_buscarIdCliente(clientes,LENGTH_CLIENTE,auxId);
							if(auxIndice>=0)
							{
								printf("Las publicaciones del cliente seleccionado son las siguientes:\n");
								if(!publi_imprimirArrayPublicacionPorIDCliente(publicaciones, LENGTH_PUBLI, auxId))
								{
									if(!cliente_bajaArrayCliente(clientes, LENGTH_CLIENTE, auxIndice))
									{
										if(!publi_bajaArrayPublicacion(publicaciones,LENGTH_PUBLI,auxId))
										{
											printf("El cliente se dio de baja con Exito!!\n"
												   "Lista de Clientes actualizada:");
											cliente_imprimirArrayCliente(clientes, LENGTH_CLIENTE);
											printf("\nLista de Publicaciones actualizada:\n");
											publi_imprimirArrayPublicacion(publicaciones, LENGTH_PUBLI);
										}
									}
								}
								else
								{
									printf("Este cliente no tiene publicaciones.\n");
								}
							}
							else
							{
								printf("No se encuentra el ID seleccionado.\n");
							}
						}
						else
						{
							printf("Se acabaron tus reintentos.\n");
						}
					}
					printf("\n***************************************\n");
					break;
				case 4:
					printf("\n***************************************\n");
					printf("Publicar un aviso:");
					if(cliente_checkListaVacia(clientes,LENGTH_CLIENTE)==-1)
					{
						printf("\nLa lista de clientes esta vacia.\n");
					}
					else
					{
						publi_altaArrayPublicacion(publicaciones,LENGTH_PUBLI,clientes,LENGTH_CLIENTE);
					}
					printf("\n***************************************\n");
					break;
				case 5:
					printf("\n***************************************\n");
					printf("Pausar Publicacion:\n");
					printf("Lista de publicaciones activas:\n");
					if(publi_checkListaVacia(publicaciones,LENGTH_PUBLI))
					{
						printf("La lista de Publicaciones esta vacia.\n");
					}
					else
					{
						if(!publi_imprimirArrayPublicacionActivas(publicaciones, LENGTH_PUBLI))
						{
							if(!utn_getNumero(&auxId,"Ingrese el ID de la publicacion a pausar:","ERROR",MIN_ID,MAX_ID,QTY_REINT))
							{
								auxIndice = publi_buscarIdPublicacion(publicaciones,LENGTH_PUBLI,auxId);
								if(auxIndice>=0)
								{
									printf("Cliente al que pertenece la publicacion:\n");
									if(!publi_imprimirClientexIdPublicacion(publicaciones,LENGTH_PUBLI,clientes,LENGTH_CLIENTE,auxId))
									{
										if(!publi_PausarPublicacion(publicaciones,LENGTH_PUBLI,auxId))
										{
											printf("Lista actualizada de Publicaciones:\n");
											publi_imprimirArrayPublicacion(publicaciones, LENGTH_PUBLI);
										}
									}
								}
								else
								{
									printf("No se encontro el ID ingresado.\n");
								}
							}
							else
							{
								printf("Se acabaron tus reintentos.\n");
							}
						}
						else
						{
							printf("No hay publicaciones Activas.\n");
						}
					}
					printf("\n***************************************\n");
					break;
				case 6:
					printf("\n***************************************\n");
					printf("Reanudar Publicacion\n");
					printf("Lista de publicaciones pausadas:\n");
					if(publi_checkListaVacia(publicaciones,LENGTH_PUBLI))
					{
						printf("La lista de Publicaciones esta vacia.\n");
					}
					else
					{
						if(!publi_imprimirArrayPublicacionPausadas(publicaciones, LENGTH_PUBLI))
						{
							if(!utn_getNumero(&auxId,"Ingrese el ID de la publicacion a Activar:","ERROR",MIN_ID,MAX_ID,QTY_REINT))
							{
								auxIndice = publi_buscarIdPublicacion(publicaciones,LENGTH_PUBLI,auxId);
								if(auxIndice>=0)
								{
									printf("Cliente al que pertenece la publicacion:\n");
									if(!publi_imprimirClientexIdPublicacion(publicaciones,LENGTH_PUBLI,clientes,LENGTH_CLIENTE,auxId))
									{
										if(!publi_ActivarPublicacion(publicaciones,LENGTH_PUBLI,auxId))
										{
											printf("Lista actualizada de Publicaciones:\n");
											publi_imprimirArrayPublicacion(publicaciones, LENGTH_PUBLI);
										}
									}
								}
								else
								{
									printf("No se encontro el ID ingresado.\n");
								}
							}
							else
							{
								printf("Se acabaron tus reintentos.\n");
							}
						}
						else
						{
							printf("No hay publicaciones Pausadas.\n");
						}
					}
					printf("\n***************************************\n");
					break;
				case 7:
					printf("\n***************************************\n");
					printf("Imprimir clientes:\n");
					if(cliente_checkListaVacia(clientes,LENGTH_CLIENTE))
					{
						printf("La lista de Clientes esta vacia.\n");
					}
					else
					{
						publi_imprimirCantidadPublicacionesDeClientes(publicaciones, LENGTH_PUBLI, clientes, LENGTH_CLIENTE);
					}
					printf("\n***************************************\n");
					break;
				case 8:
					printf("\n***************************************\n");
					do
					{
						if(!utn_getNumero(	&optionMenu,
											"\n*****Informar*****\n"
											"1-Cliente con mas avisos\n"
											"2-Cantidad de avisos pausados\n"
											"3-Rubro con mas avisos\n"
											"4-Volver al Menu Principal.\n"
											"-----------------------------\n"
											"Elija una Opcion del Menu: ",
											"ERROR",MIN_OPTION_MENU,MAX_OPTION_MENU_INFO,QTY_REINT))
						{
							switch(optionMenu)
							{
								case 1:
									printf("\n***************************************\n");
									printf("1-Cliente con mas avisos\n");
									if(cliente_checkListaVacia(clientes,LENGTH_CLIENTE)==-1)
									{
										printf("La lista de clientes esta vacia.\n");
									}
									else
									{
										printf("El cliente con mayor cantidad de avisos es:\n");
										info_calculaClientesConMasAvisos(publicaciones,LENGTH_PUBLI,clientes,LENGTH_CLIENTE);
									}
									printf("\n***************************************\n");
									break;
								case 2:
									printf("\n***************************************\n");
									printf("2-Cantidad de avisos pausados\n");
									if(publi_checkListaVacia(publicaciones, LENGTH_PUBLI)==-1)
									{
										printf("La lista de avisos esta vacia.\n");
									}
									else
									{
										cantAvisosPausados = info_calculaCantidadDePublicacionesPausadas(publicaciones, LENGTH_PUBLI);
										if(cantAvisosPausados>0)
										{
											printf("la cantidad de avisos pausados es: %d\n"
													"Lista de avisos pausados:\n",
													cantAvisosPausados);
											publi_imprimirArrayPublicacionPausadas(publicaciones, LENGTH_PUBLI);
										}
										else
										{
											printf("No hay avisos pausados en este momento.\n");
										}
									}
									printf("\n***************************************\n");
									break;
								case 3:
									printf("\n***************************************\n");
									printf("3-Rubro con mas avisos\n");
									if(publi_checkListaVacia(publicaciones, LENGTH_PUBLI)==-1)
									{
										printf("La lista de avisos esta vacia.\n");
									}
									else
									{
										printf("El rubro con mas avisos es:\n");
										info_generarListaDeRubros(rubros,LENGTH_RUBROS,publicaciones,LENGTH_PUBLI);
										info_calculaRubrosConMasAvisos(publicaciones, LENGTH_PUBLI, rubros, LENGTH_RUBROS);
									}
									printf("\n***************************************\n");
									break;
							}
						}
					}while(optionMenu!=4);
				printf("\n***************************************\n");
				break;
			}
		}
	}while(optionMenu);
	return EXIT_SUCCESS;
}
