#ifndef PUBLICACION_H_
#define PUBLICACION_H_

#define LENGTH_PUBLI 1000
#define LENGTH_TEXTO 64
#define LENGTH_ESTADO 8
#define ESTADO_ACTIVA 1
#define ESTADO_PAUSADA 0
#define MIN_RUBRO 1
#define MAX_RUBRO 60

typedef struct
{
	int id;
	int rubro;
	char texto[LENGTH_TEXTO];
	int estado;
	int IdCliente;
	int isEmpty;
}Publicacion;

int publi_imprimirArrayPublicacion(Publicacion* array,int limite);
int publi_inicializarArrayPublicacion(Publicacion* array,int limite);
int publi_altaArrayPublicacion(Publicacion* arrayPublicacion,int limitePublicacion,Cliente* arrayCliente, int limiteCliente);
int publi_buscarIdPublicacion(Publicacion* array, int limite, int valorBuscado);
int publi_getEmptyIndexPublicacion(Publicacion* array,int limite);
int publi_ordenarPublicacionID(Publicacion* array,int limite);
int publi_mocksPublicacion(Publicacion* array,int limite,int rubro,char* texto,int idCliente);
int publi_ordenarPublicacionDobleCriterio(Publicacion* list, int len, int order);
int publi_checkListaVacia(Publicacion* list, int len);
int publi_ActivarArrayPublicacion(Publicacion* array,int limite);
int publi_imprimirArrayPublicacionPorIDCliente(Publicacion* array,int limite,int id);
int publi_bajaArrayPublicacion(Publicacion* array,int limite, int idCliente);
int publi_imprimirArrayPublicacionPorID(Publicacion* array,int limite, int id);
int publi_imprimirClientexIdPublicacion(Publicacion* arrayPubli,int limitePubli,Cliente* arrayCli,int limiteCli, int idPublicacion);
int publi_PausarPublicacion(Publicacion* array, int limite, int id);
int publi_imprimirArrayPublicacionActivas(Publicacion* array,int limite);
int publi_imprimirArrayPublicacionPausadas(Publicacion* array,int limite);
int publi_ActivarPublicacion(Publicacion* array, int limite, int id);
int publi_imprimirCantidadPublicacionesDeClientes(Publicacion* arrayPubli,int limitePubli,Cliente* arrayCli,int limiteCli);
int publi_contarPublicacionesActivasPorID(Publicacion* array, int limite, int id);
int publi_devolverIdClientePorIdPublicacion(Publicacion* array, int limite, int idPublicacion);
int publi_contarPublicacionesPorID(Publicacion* array, int limite, int id);

#endif /* PUBLICACION_H_ */
