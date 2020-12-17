#include "heap.h" 
#include <stdbool.h> 

#define TAMANIO_INICIAL 20 
#define FACTOR_REDUCCION 0.25 
#define FACTOR_REDIMENSION 2 


//Cabe aclarar que este heap es un heap de Màximos =)


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
	cmp_func_t comparador;
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
		heap->comparador = cmp;
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
		heap->comparador = cmp;
	}
	return heap;
}

/* Elimina el heap, llamando a la función dada para cada elemento del mismo.
 * El puntero a la función puede ser NULL, en cuyo caso no se llamará.
 * Post: se llamó a la función indicada con cada elemento del heap. El heap
 * dejó de ser válido. */
void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){	
	if (destruir_elemento != NULL){
		size_t i = heap->cantidad_total;
		while(!heap_esta_vacio(heap)){
			destruir_elemento(heap->elementos[i]);
			i--;
		}
	}
	free(heap->elementos);
	free(heap);
}

/* Devuelve la cantidad de elementos que hay en el heap. */
size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad_total;
}
/* Devuelve true si la cantidad de elementos que hay en el heap es 0, false en
 * caso contrario. 
 */
bool heap_esta_vacio(const heap_t *heap){
	return(heap->cantidad_total == 0);
}

/*
 *Funcion que aplica upheap al vector de elementos
 * Pre: Recibe un vector de elementos, la cantidad de elementos, la posicion actual a redimensionar
 * y una funcion de comparacion de elementos previamente vàlidos
 */
void upheapear(void ** elementos, size_t cantidad_elementos, cmp_func_t cmp){

}

/*
 *Funcion que aplica downheap al vector de elementos
 * Pre: Recibe un vector de elementos, la cantidad de elementos, la posicion actual a redimensionar
 * y una funcion de comparacion de elementos previamente vàlidos
 *
 */
void downheapear(void ** elementos, cmp_func_t cmp, size_t cantidad_elementos, size_t posicion_act){
}

/*
 *Devuelve verdadero si hay que redimensionar a un mayor tamaño el heap
 */
bool hay_que_agrandar(const heap_t * heap){
	return ((heap->cantidad_elementos + 1) == heap_tamanio);
}

/*
 * Devuelve verdadero si hay que redimensionar a un menor tamaño el heap
 */
bool hay_que_achicar(const heap_t * heap){
	return ((heap->cantidad_elementos/heap->tamanio <= FACTOR_REDUCCION) && heap->tamanio > TAMANIO_INICIAL);

}

/*
 * Recibe un heap y el proximo tamaño a redimensionar
 * Devuelve un puntero a un nuevo vector de elementos con el proximo tamaño
 */
void * redimensionar(heap_t * heap, size_t nuevo_tamanio){
	void * datos = realloc(heap->elementos, sizeof(void *) *nuevo_tamanio);
	return datos;
}

/* Agrega un elemento al heap. El elemento no puede ser NULL.
 * Devuelve true si fue una operación exitosa, o false en caso de error.
 * Pre: el heap fue creado.
 * Post: se agregó un nuevo elemento al heap.
 */
bool heap_encolar(heap_t *heap, void *elem){
	if(hay_que_agrandar(heap)){
		void * nuevo_vector = redimensionar(heap, heap->tamanio * FACTOR_REDIMENSION);
		if (!nuevo_vector){
			return false;
		}
		heap->tamanio = (heap->tamanio * FACTOR_REDIMENSION);
		heap->elementos = nuevo_vector;		
	}
	heap->elementos[heap->cantidad_total] = elem;
	heap->cantidad_total++;
	upheapear(heap->elementos, heap->cantidad_total, heap->comparador);
	return true;
}

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


/*
 * Esta funcion intercambia de lugar dos valores
 * Esta funcion es practicamente identica a la del TP0
 */
void intercambio(void *x, void *y) {
	void* auxiliar = *y;
	*y = *x;
	*x = auxiliar; 
}

/* Elimina el elemento con máxima prioridad, y lo devuelve.
 * Si el heap esta vacío, devuelve NULL.
 * Pre: el heap fue creado.
 * Post: el elemento desencolado ya no se encuentra en el heap.
 */
void *heap_desencolar(heap_t *heap){
	if(heap_esta_vacio(heap)){
		return NULL;
	}
	void * dato = heap->elementos[0];
	heap->cantidad_total--:
	if (!heap_esta_vacio){
		intercambio(heap->elementos[0], heap->elementos[heap->cantidad_total]);
		downheapear(heap->elementos, heap->comparador, heap->cantidad_total, 0);
	}
	if (hay_que_achicar(heap)){
		void * nuevos_datos = redimensionar(heap, heap->tamanio / FACTOR_REDIMENSION);
		if(!nuevos_datos){
			return NULL;
		}
		heap->elementos = nuevos_datos;
	}
	return dato;
}

// -----------------------------------------------------------------------------//

/* Función de heapsort genérica. Esta función ordena mediante heap_sort
 * un arreglo de punteros opacos, para lo cual requiere que se
 * le pase una función de comparación. Modifica el arreglo "in-place".
 * Nótese que esta función NO es formalmente parte del TAD Heap.
 */
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp);
