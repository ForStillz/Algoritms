#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//empezamos con la estructura de datos 
struct nodo{
	char artista[200];
	char album[200];
	char titulo[200];
	struct nodo* sig;
};
//estrucutura para la cabezera
struct cabecera{
	struct nodo* I;
	int ne;
};

/*Para el siguiente programa usaremos las funciones basicas de una lista ademas de unas agregadas las cuales 
son cruciales para el funcionamiento correcto de la practica ademas, entre estas seran las siguientes:
creacion: crear_lista, crecar_nodo.
verificar: lista_vacia:
edicion: borrar, limpiar, destruir, copiar, agregar.
vista: leer, ver, buscar.



*/
//definimos los tipo que utilizaremos
typedef struct nodo NODO;
typedef struct cabecera CABECERA;
typedef NODO* n;
typedef CABECERA* lista;
typedef enum b{FALSO, REAL} booleano;
typedef enum m{NO_MEMORY, OK, POS_INV} mensaje;


mensaje crearNodo(n *nodo){
	n temp;
	temp = (n)malloc(sizeof(NODO));

	if(temp==NULL){
		return NO_MEMORY;
	}

	*nodo = temp;
	return OK;
}

//verificamos el estado en el que esta la lista
booleano vacia(lista L){
	if(L!=NULL && L->ne==0){
		return REAL;
	}

	return FALSO;
}

booleano vaciaNo(n E){
	if(E!=NULL){
		return REAL;
	}
	return FALSO;
}

//funciones para edicion en el ambito de clean 
mensaje borrar(lista L, int p){
	n aux, temp;
	int i;

	if(!(p>0 && p<=L->ne)){
		return POS_INV;
	}

	temp=(n)malloc(sizeof(NODO));

	if(p==1){
		aux=L->I->sig;
		free(L->I);
		L->I=aux;
	}
	else{
		for(i=1, aux=L->I; i<p-1; i++,aux=aux->sig);

		temp=aux->sig->sig;
		free(aux->sig);
		aux->sig=temp;
	}
	L->ne--;
	return OK;
}

void limpiarLista(lista L){
	while(!vacia(L)){
		borrar(L,1);
	}
}

void destruirLista(lista *L){
	limpiarLista(*L);
	free(*L);
	*L=NULL;
}

//funcion para poder copiar los elementos de la lista
void copia(n D, NODO e){
	strcpy(D->artista, e.artista);
	strcpy(D->album,e.album);
	strcpy(D->titulo, e.titulo);
}

//funciones de edicion de la lista
mensaje agregar(lista L, int p, NODO E){
	n temp, aux, aux2;
	int i;

	if(!(p>0 && p<=L->ne)){
		return POS_INV;
	}

	crearNodo(&temp);
	
	for(i=1, aux=L->I; i<p-1; i++,aux=aux->sig);


	copia(temp, E);
	aux2 = aux->sig;
	aux->sig = temp;
	temp->sig = aux2;
	L->ne++;
	return OK;
}

//funcion para poder leer la lista
mensaje leer(lista L, int p, n D){
	n aux;
	int i;

	if(!(p>0 && p<=L->ne)){
		return POS_INV;
	}

	for(i=1, aux=L->I; i<p-1; i++,aux=aux->sig);

	copia(D, *aux);
	return OK;	
}


//funcion para mostrar en pantalla
void mostrar(lista L){
	int cont = 1;
	n aux;
	aux = L->I;

	while(vaciaNo(aux)){
		printf("%d.- %s - %s - %s\n", cont, aux->titulo, aux->album, aux->artista);
		cont++;
		aux = aux->sig;
	}
}

//busqueda de los elementos dentro de la lista
void buscador(lista L, char* buscando, int tipo) {
    n aux, temp;
    int encontrado = 0;
    int cont =1;

    aux = L->I;
    printf("Resultados de la busqueda:\n");

    if(tipo==1){
    	while (vaciaNo(aux)) {
      	if (strncmp(aux->titulo, buscando, strlen(buscando)) == 0) {
          printf("%s - %s - %s\n", aux->titulo, aux->album, aux->artista);
          encontrado = 1;
        }
        cont++;
        aux = aux->sig;
    	}
  	}
  	else if(tipo==2){
			while (vaciaNo(aux)) {
      	if (strncmp(aux->album, buscando, strlen(buscando)) == 0) {
          printf("%s - %s - %s\n", aux->titulo, aux->album, aux->artista);
          encontrado = 1;
        }
        cont++;
        aux = aux->sig;
    	}  		
  	}
  	else if(tipo==3){
  		while (vaciaNo(aux)) {
      	if (strncmp(aux->artista, buscando, strlen(buscando)) == 0) {
          printf("%s - %s - %s\n", aux->titulo, aux->album, aux->artista);
          encontrado = 1;
        }
        cont++;
        aux = aux->sig;
    	} 
  	}

    if (!encontrado) {
        printf("No se encontraron coincidencias.\n");
    }
}
//funcion para poder agregar el archivo txt
mensaje cargarDesdeArchivo(lista L, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        return NO_MEMORY;
    }

    NODO nuevo;
    while (fgets(nuevo.artista, sizeof(nuevo.artista), archivo) != NULL) {
        fgets(nuevo.album, sizeof(nuevo.album), archivo);
        fgets(nuevo.titulo, sizeof(nuevo.titulo), archivo);
        // Eliminar el carácter de nueva línea del final
        nuevo.artista[strcspn(nuevo.artista, "\n")] = '\0';
        nuevo.album[strcspn(nuevo.album, "\n")] = '\0';
        nuevo.titulo[strcspn(nuevo.titulo, "\n")] = '\0';
        agregar(L, L->ne + 1, nuevo);
    }

    fclose(archivo);
    return OK;
}

//empezamos con las funciones para poder crear, el cual se dara en mensajes
mensaje crearLista(lista *L){
	lista temp;
	temp=(lista)malloc(sizeof(CABECERA));

	if(temp == NULL){
		return NO_MEMORY;
	}

	temp->ne = 0;
	temp->I = NULL;
	*L = temp;
	cargarDesdeArchivo(*L, "ac.txt"); 
	return OK;
}
//menu en el cual podremos modificar los elementos en pantalla
void menu(lista L){
	int opcion, respuesta;
	NODO nuevo;
	char bus[200];
	do{
		printf("Seleccione una opcion: \n");
		printf("\t1- Mostrar lista\n\t2- Buscar\n\t3- Configuracion\n\t4- reproducir\n\t5- Salir\n\t\t");
		scanf("%d", &opcion);
		switch(opcion){
		case 1:
			//Muestra todas las canciones
			mostrar(L);

			break;
		case 2:
			//Busqueda parcial o exacta
			printf("Buscar por:\n");
			printf("\t1- Cancion\n\t2- Album\n\t3- Artista\n\t\t");
			scanf("%d", &respuesta);

			printf("Buscar:");
			fflush(stdin);
			scanf("%[^\n]", &bus);
			fflush(stdin);

			buscador(L, bus, respuesta);

			break;
		case 3:
			printf("Configuracion:\n");
			printf("\t1- Agregar\n\t2- Modificar\n\t3-Eliminar\n\t\t");
			scanf("%d", &respuesta);

			

			break;
		case 4:
			//Reproductor
			printf("Ponga el numero de la Cancion:\n\t");
			scanf("%d", &respuesta);

			leer(L, respuesta, &nuevo);

			printf("Se esta reproducciendo: %s de %s", nuevo.titulo, nuevo.artista);
			break;
		default:
			if(opcion!=5){
				printf("opcion invalida\n");
			}
		}
	}while(opcion!=5);
}

