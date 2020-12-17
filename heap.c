#include "heap.h" 
#include <stdbool.h> 

#define TAMANIO_INICIAL 20 





/*
 * Implementación de un TAD cola de prioridad, usando un max-heap.
 *
 * Notar que al ser un max-heap el elemento mas grande será el de mejor
 * prioridad. Si se desea un min-heap, alcanza con invertir la función de
 * comparación.
 */

/* Tipo utilizado para el heap. */
typedef struct heap{
	void ** elementos;
	size_t tamanio;
	size_t cantidad_total;
}heap_t;

/* Crea un heap. Recibe como único parámetro la función de comparación a
 * utilizar. Devuelve un puntero al heap, el cual debe ser destruido con
 * heap_destruir().
 */
heap_t *heap_crear(cmp_func_t cmp){
	if (cmp == NULL){
		return NULL;
	}
	heap_t * heap = malloc(sizeof(heap_t));
	if (heap){
		heap->elementos = malloc(TAMANIO_INICIAL * sizeof(void*));
		if (!heap->elementos){
			free(heap);
			return NULL;
		}
		heap->cmp = cmp;
		heap->cantidad_total = 0;
		heap->tamanio = TAMANIO_INICIAL;
	}
	return heap;
}
/*
 * Constructor alternativo del heap. Además de la función de comparación,
 * recibe un arreglo de valores con que inicializar el heap. Complejidad
 * O(n).
 *
 * Excepto por la complejidad, es equivalente a crear un heap vacío y encolar
 * los valores de uno en uno
*/
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
		if (cmp == NULL){
		return NULL;
	}
	heap_t * heap = malloc(sizeof(heap_t));
	if (heap){
		heap->elementos = malloc(n * sizeof(void*));
		if (!heap->elementos){
			free(heap);
			return NULL;
		}
		heap_sort(arreglo, n, cmp);
		memcpy(heap->elementos, arreglo, n* sizeof(void*));
		heap->cantidad_total = n;
		heap->tamanio = heap->cantidad_total;
		heap->cmp = cmp;
	}
	return heap;
}

/* Elimina el heap, llamando a la función dada para cada elemento del mismo.
 * El puntero a la función puede ser NULL, en cuyo caso no se llamará.
 * Post: se llamó a la función indicada con cada elemento del heap. El heap
 * dejó de ser válido. */
void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e));

/* Devuelve la cantidad de elementos que hay en el heap. */
size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad;
}
/* Devuelve true si la cantidad de elementos que hay en el heap es 0, false en
 * caso contrario. */
bool heap_esta_vacio(const heap_t *heap){
	return(heap->cantidad == 0);
}

/* Agrega un elemento al heap. El elemento no puede ser NULL.
 * Devuelve true si fue una operación exitosa, o false en caso de error.
 * Pre: el heap fue creado.
 * Post: se agregó un nuevo elemento al heap.
 */
bool heap_encolar(heap_t *heap, void *elem);

/* Devuelve el elemento con máxima prioridad. Si el heap esta vacío, devuelve
 * NULL.
 * Pre: el heap fue creado.
 */
void *heap_ver_max(const heap_t *heap){
	if (heap_esta_vacio(heap)){
		return NULL;
	}
	return heap->elementos[0];
}

/* Elimina el elemento con máxima prioridad, y lo devuelve.
 * Si el heap esta vacío, devuelve NULL.
 * Pre: el heap fue creado.
 * Post: el elemento desencolado ya no se encuentra en el heap.
 */
void *heap_desencolar(heap_t *heap);

// -----------------------------------------------------------------------------//

/* Función de heapsort genérica. Esta función ordena mediante heap_sort
 * un arreglo de punteros opacos, para lo cual requiere que se
 * le pase una función de comparación. Modifica el arreglo "in-place".
 * Nótese que esta función NO es formalmente parte del TAD Heap.
 */
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp);
