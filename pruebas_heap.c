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
	if ((int)a < (int) b){
		return -1;
	}
	if ((int)a > (int) b){
		return 1;
	}
	return 0;
}



static void pruebas_creado(){
	heap_t * heap = heap_crear(comparacion);
    print_test("Prueba crear heap vacio", heap);
	print_test("Prueba cantidad cero", heap_cantidad(heap) == 0);
	print_test("Prueba es un heap vacio", heap_esta_vacio(heap));

	print_test("No se puede desencolar un heap vacio", !heap_desencolar(heap));
	heap_destruir(heap, NULL);

}

static void prueba_crear_sin_funcion_comparacion(){
	heap_t* heap = heap_crear( NULL);
    print_test("No se puede crear un heap sin funcion de comparacion", !heap);
}


static void prueba_encolado_desencolado_un_elemento(){
	heap_t * heap = heap_crear(comparacion);
   	int *elemento = malloc(sizeof(int*));
	
	print_test("Insertar un elemento", heap_encolar(heap, elemento));
	print_test("Prueba cantidad correcta", heap_cantidad(heap) == 1);
	print_test("Prueba NO es un heap vacio", !heap_esta_vacio(heap));
	void * elemento_desencolado =  heap_desencolar(heap);
	print_test("Desencolado correcto", (elemento == elemento_desencolado));
	print_test("Prueba cantidad cero", heap_cantidad(heap) == 0);
	heap_destruir(heap, NULL);
	free(elemento);
}
/*
 * A diferencia de la anterior, esta funcion prueba que se libere la memoria
 * Cuando se destruye un heap con elementos dentro
 */
static void prueba_encolado_un_elemento(){
	heap_t * heap = heap_crear(comparacion);
   	int *elemento = malloc(sizeof(int*));
	
	print_test("Insertar un elemento", heap_encolar(heap, elemento));
	print_test("Prueba cantidad correcta", heap_cantidad(heap) == 1);
	print_test("Prueba NO es un heap vacio", !heap_esta_vacio(heap));
	heap_destruir(heap, free);
}

static void prueba_reemplazo_mayor(){
	int primero = 88;
	int segundo = 100;

	int * pt1 = &primero;
	int * pt2 = &segundo;
	heap_t * heap = heap_crear(comparacion);
	heap_encolar(heap, pt2);
	print_test("Prueba cantidad correcta", heap_cantidad(heap) == 1);
	void * desen = heap_ver_max(heap);
	
	print_test("Maximo correcto", (pt2  == desen));
	print_test("Insertar otro elemento", heap_encolar(heap, pt1));
	desen = heap_ver_max(heap);
	print_test("Maximo correcto", (pt1 == desen));
	heap_destruir(heap, NULL);


}

void  pruebas_heap_estudiante(){
	pruebas_creado();
	prueba_crear_sin_funcion_comparacion();
	prueba_encolado_desencolado_un_elemento();
	prueba_encolado_un_elemento();
	prueba_reemplazo_mayor();
}