#include <stdio.h>

int main() {
    int array1[5] = {1, 2, 3, 4, 5};
    int array2[5] = {1, 2, 3, 4, 5};
    int i;
    
    for (i = 0; i < 5; i++) {
        if (array1[i] == array2[i]) {
            printf("Los elementos de la posición %d son iguales.\n", i);
        }
    }
    
    return 0;
}