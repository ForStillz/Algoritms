#include "Funciones_lista.h"

int main(){
	lista Musica;

	crearLista(&Musica);

	menu(Musica);

	destruirLista(&Musica);
	return 0;
}
