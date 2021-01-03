#include "heap.h" 
#include "testing.h"
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include <stdio.h>

/*
 *Esta funcion compara dos valores transformandolos a enteros y devolviendo
 * otro entero que serà
 *   menor a 0  si  a < b
 *       0      si  a == b
 *   mayor a 0  si  a > b
 */
int comparacion(const void * a, const void * b){
	if (a <  b){
		return -1;
	}
	if (a >  b){
		return 1;
	}
	return 0;
}
typedef struct heap{
	void ** elementos;
	cmp_func_t comparador;
	size_t tamanio;
	size_t cantidad_total;
	bool es_de_array;
}heap_t;

static void crear_a_partir_array(){
	size_t n = 9;
	int *valores = calloc(n , sizeof(int));
	void ** arreglo = malloc(n * sizeof(void*));
	for (int i = 0; i < n; i++){
 		valores[i] = i + 1;
 		arreglo[i] = &valores[i];
 	} 
	heap_t * heap = heap_crear_arr((void*)arreglo, n, comparacion);
	print_test("Heap creado a partir de arreglo", (heap));
	
	print_test("Heap cantidad a partir de arreglo correcta", (heap_cantidad(heap) == 9));
	for (int i = 0; i <= n; i++){
		printf("Elemento %i: %i \n", i, (int)heap->elementos[i] );
	}
	heap_destruir(heap, NULL);
	free(arreglo);
	free(valores);

}





void pruebas_heap_estudiante(){

	crear_a_partir_array();

}


/*
gcc -g -O2 -std=gnu11 -Wall -pedantic -Wformat=2 -Wshadow -Wpointer-arith -Wunreachable-code -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wdiscarded-qualifiers -o pruebas *.c


*/