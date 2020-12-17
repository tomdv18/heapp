#include "heap.h" 


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



void pruebas_creado(){
	heap_t * heap = heap_crear(comparacion);
    print_test("Prueba crear heap vacio", heap);
	print_test("Prueba cantidad cero", heap_cantidad(heap) == 0);
	print_test("Prueba es un heap vacio", heap_esta_vacio(heap));
	print_test("No se puede desencolar un heap vacio", !heap_desencolar(heap));
	heap_destruir(heap, NULL);

}


void  pruebas_heap_estudiante(){
	pruebas_creado();
}