#ifndef INFORMES_H_
#define INFORMES_H_

#define LENGTH_RUBROS 60

typedef struct
{
	int rubro;
	int isEmpty;
}Rubro;

int info_calculaCantidadDePublicacionesPausadas(Publicacion* array, int limite);
int info_DevolverCantMayorPublicaciones(Publicacion* arrayPubli,int limitePubli,Cliente* arrayCli,int limiteCli, int id);
int info_calculaClientesConMasAvisos(Publicacion* arrayPubli,int limitePubli,Cliente* arrayCli,int limiteCli);
int info_inicializarRubro(Rubro* array,int limite);
int info_imprimirListaRubros(Rubro* array, int limite);
int info_estaEnMiListaDeRubros(Rubro* array,int limite,int rubro);
int info_generarListaDeRubros(Rubro* arrayRubro,int limiteRubro,Publicacion* arrayPubli, int limitePubli);
int info_calculaRubrosConMasAvisos(Publicacion* arrayPubli,int limitePubli,Rubro* arrayRubro,int limiteRubro);
int info_contarPublicacionesPorRubro(Publicacion* array, int limite, int rubro);
int info_DevolverCantMayorPublicacionesPorRubros(Publicacion* arrayPubli,int limitePubli,Rubro* arrayRubro,int limiteRubro, int rubro);
int info_devolverPrimerAvisoContado(Publicacion* array, int limite, int id);
int info_devolverPrimerCantPublicacionesPorRubro(Publicacion* array, int limite, int rubro);

#endif /* INFORMES_H_ */
