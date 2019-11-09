#include <stdlib.h>
#include <string.h>
#include "sac_servidor.h"

/*
ptrGBloque determine_nodo(const char* path){

	// If it is the root directory, it returns 0
	if(!strcmp(path, "/")) return 0;

	int i, nodo_anterior, err = 0;

	// Super_path used to get the top of the path, without the name.
	char *super_path = (char*) malloc(strlen(path) +1), *nombre = (char*) malloc(strlen(path)+1);
	char *start = nombre, *start_super_path = super_path; //Pointers used to free memory.
	struct sac_server_gfile *node;
	unsigned char *node_name;

	split_path(path, &super_path, &nombre);

	nodo_anterior = determine_nodo(super_path);


	pthread_rwlock_rdlock(&rwlock); //Takes a lock for read
	log_lock_trace(logger, "Determinar_nodo: Toma lock lectura. Cantidad de lectores: %d", rwlock.__data.__nr_readers);
	node = node_table_start;

	// Search the node where is the name
	node_name = &(node->fname[0]);
	for (i = 0; ( (node->parent_dir_block != nodo_anterior) | (strcmp(nombre, (char*) node_name) != 0) | (node->state == 0)) &  (i < GFILEBYTABLE) ; i++ ){
		node = &(node[1]); // next node position
		node_name = &(node->fname[0]);
	}

	// Close connections and free memory. Contemplate error cases.
	pthread_rwlock_unlock(&rwlock);
	log_lock_trace(logger, "Determinar_nodo: Libera lock lectura. Cantidad de lectores: %d", rwlock.__data.__nr_readers);
	free(start);
	free(start_super_path);
	if (err != 0) return err;
	if (i >= GFILEBYTABLE) return -1;

	return (i); // +1?
}
*/

char **splitPath(char *path, int *size){
    char *tmp;
    char **splitted = NULL;
    int i, length;

    if (!path){
    	*size = 0;
    	return NULL;
    }

    tmp = strdup(path);
    length = strlen(tmp);

    *size = 1;
    for (i = 0; i < length; i++) {
        if (tmp[i] == '/') {
            tmp[i] = '\0';
            (*size)++;
        }
    }

    splitted = (char **)malloc(*size * sizeof(*splitted));
    if (!splitted) {
        free(tmp);
        *size = 0;
        return NULL;
    }

    for (i = 0; i < *size; i++) {
        splitted[i] = strdup(tmp);
        tmp += strlen(splitted[i]) + 1;
    }
    return splitted;
}

bool esElNodoBuscado(int nodo, char* filename, ptrGBloque nodoPadre){

	 return tablaDeNodos[nodo].state != 0 &&
		    tablaDeNodos[nodo].parent_dir_block == nodoPadre &&
		    tablaDeNodos[nodo].fname == filename;

}

int buscar_nodo_por_nombre(char *filenameBuscado, ptrGBloque nodoPadre){
	int currNode = 0;

	while(esElNodoBuscado(currNode, filenameBuscado, nodoPadre) && currNode < MAX_NUMBER_OF_FILES){
		currNode++;
	}

	return currNode;
}

int determine_nodo(char *path){
	int nodoUltimoPadre = 0; //el nodo de "/"
	char *filenameBuscado;

	int dimListaSpliteada, i;
	char **listaSpliteada;

	listaSpliteada = splitPath(path, &dimListaSpliteada);

	for(i=0 ; i<dimListaSpliteada; i++){

		filenameBuscado = listaSpliteada[i];

		nodoUltimoPadre = buscar_nodo_por_nombre(filenameBuscado, nodoUltimoPadre);

	}

	return nodoUltimoPadre;
}
