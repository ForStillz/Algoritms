#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
//estrucutura
struct nombre {
    int id;
    char nombre[20];
    char apellido[20];
};

//declaracion de 
char *nombres[] = {"Juan", "Pedro", "Luis", "Maria", "Ana","John", "Jane", "Bob", "Alice", "Mike", "Mary", "David", "Sarah", "Tom", "Emily"};
char *apellidos[] = {"Garcia", "Perez", "Lopez", "Rodriguez", "Gonzalez","Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor"};

int comparar_id(const void *a, const void *b);
int buscar_persona(struct nombre *personas, int n, int id);
int buscar_personaIND(struct nombre *personas, int n, int id);
int min(int a, int b) {return a < b ? a : b;}
int busqueda_lineal(struct nombre *personas, int size, int numero_aleatorio2);

int main() {
    // iniciamos la función de rand
   srand(time(NULL));

    struct nombre personas[30000];

    int i;
    for (i = 0; i < 25000; i++) {
        personas[i].id = i + 1;
        strcpy(personas[i].nombre, nombres[rand() % 15]);
        strcpy(personas[i].apellido, apellidos[rand() % 15]);
    }

    for (i = 25000; i < 30000; i++) {
        personas[i].id = i + 1;
        strcpy(personas[i].nombre, "Sin asignar");
        strcpy(personas[i].apellido, "");
    }


    // ordenamos la matriz por ID utilizando la función qsort de la librería standard de C
    qsort(personas, 30000, sizeof(struct nombre), comparar_id);

    // generamos un número aleatorio entre 1 y 30000
    int numero_aleatorio = rand() % 30000 + 1;
	int numero_aleatorio3 = rand () % 30001;
    // buscamos la persona aleatoria por su ID utilizando la búsqueda binaria
    int indice_persona = buscar_persona(personas, 30000, numero_aleatorio);
    if (indice_persona != -1) {
        printf("Felicidades, has ganado la rifa: %s %s\nID: %d\n", personas[indice_persona].nombre, personas[indice_persona].apellido, personas[indice_persona].id);
    } else {
        printf("Error: no se encontró la persona con ID %d\n", numero_aleatorio);
    }

 indice_persona = buscar_personaIND(personas, 30000, numero_aleatorio3);
    if (indice_persona != -1) {
        printf("Felicidades, has ganado la rifa: %s %s\nID: %d\n", personas[indice_persona].nombre, personas[indice_persona].apellido, personas[indice_persona].id);
    } else {
        printf("Error: no se encontró la persona con ID %d\n", numero_aleatorio3);
    }
    int numero_aleatorio2 = rand() % 30000 + 1;
    int indiceEncontrado;
    int size;
    size=30001;

  indiceEncontrado = busqueda_lineal(personas, size, numero_aleatorio2);

  if (indiceEncontrado != -1) {
printf("Felicidades, has ganado la rifa: %s %s\nID: %d\n", personas[indiceEncontrado].nombre,personas[indiceEncontrado].apellido,personas[indiceEncontrado].id);    
  } else {
    printf("Estudiante no encontrado\n");
  }

    return 0;
}

//funciones


//comparar 
int comparar_id(const void *a, const void *b) {
    struct nombre *persona_a = (struct nombre*)a;
    struct nombre *persona_b = (struct nombre*)b;
    return persona_a->id - persona_b->id;
}



//busqueda binaria 
int buscar_persona(struct nombre *personas, int n, int id) {
    int izquierda = 0, derecha = n-1, medio;
    while (izquierda <= derecha) {
        medio = (izquierda + derecha) / 2;
        if (personas[medio].id == id) {
            return medio;
        } else if (personas[medio].id < id) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }
    return -1;
}
//indexada
int buscar_personaIND(struct nombre *personas, int n, int id) {
int salto = sqrt(n);
int i = 0;
while (i < n && personas[i].id < id) {
i += salto;
}
int izquierda = i - salto;
int derecha = min(i, n-1);
while (izquierda <= derecha) {
if (personas[izquierda].id == id) {
return izquierda;
} else {
izquierda++;
}
}
return -1;
}

int busqueda_lineal(struct nombre *personas,int size, int numero_aleatorio2)
 {
    int i;
    for (i = 0; i < size; i++) {
        if (personas[i].id == numero_aleatorio2) {
            return i; // Si se encuentra el valor, retornamos su índice
        }
    }
    return -1; // Si no se encuentra el valor, retornamos -1
}

