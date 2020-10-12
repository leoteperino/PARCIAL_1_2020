#ifndef CLIENTE_H_
#define CLIENTE_H_

#define LENGTH_NOMBRE 30
#define LENGTH_APELLIDO 50
#define LENGTH_CUIT 14
#define LENGTH_CLIENTE 100
#define TRUE 1
#define FALSE 0
#define QTY_REINT 2
#define MIN_OPTION_MENU 1
#define MAX_OPTION_MENU 8
#define MAX_OPTION_MENU_INFO 4
#define MIN_ID 1
#define MAX_ID 999999999

typedef struct
{
	int id;
	char nombre[LENGTH_NOMBRE];
	char apellido[LENGTH_APELLIDO];
	char cuit[LENGTH_CUIT];
	int isEmpty;
}Cliente;

int cliente_imprimirArrayCliente(Cliente* array,int limite);
int cliente_inicializarArrayCliente(Cliente* array,int limite);
int cliente_altaArrayCliente(Cliente* array,int limite);
int cliente_modificarArrayCliente(Cliente* array,int limite, int indice);
int cliente_bajaArrayCliente(Cliente* array,int limite, int indice);
int cliente_buscarIdCliente(Cliente* array, int limite, int valorBuscado);
int cliente_getEmptyIndexCliente(Cliente* array,int limite);
int cliente_ordenarClienteID(Cliente* array,int limite);
int cliente_ordenarClienteDobleCriterio(Cliente* list, int len, int order);
int cliente_checkListaVacia(Cliente* list, int len);
int cliente_mocksCliente(Cliente* array,int limite,char* nombre,char* apellido, char* cuit);
int cliente_imprimirClientePorID(Cliente* array, int limite,int id);

#endif /* CLIENTE_H_ */
