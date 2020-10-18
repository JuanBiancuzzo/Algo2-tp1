#include <stdlib.h>
#include <string.h>

#include "evento_pesca.h"

int leer_pokemon(FILE* archivo, pokemon_t* pokemon) {
	return fscanf(archivo, "%50[^;];%i;%i;%50[^\n]\n", pokemon->especie, &(pokemon->velocidad), &(pokemon->peso), pokemon->color);
}

int escribir_pokemon(FILE* archivo, pokemon_t* pokemon) {
	return fprintf(archivo, "%s;%i;%i;%s\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
}

arrecife_t* crear_arrecife(const char* ruta_archivo) {

	arrecife_t* arrecife;
<<<<<<< HEAD
<<<<<<< HEAD
  pokemon_t* p_pokemon;
  pokemon_t pokemon_aux;
=======
 	pokemon_t* p_pokemon;
	pokemon_t pokemon_aux;
>>>>>>> origin/master
=======
 	pokemon_t* p_pokemon;
	pokemon_t pokemon_aux;
>>>>>>> a001599c2f597723c2c4b24ecf7d5cf7d8d69ddf

	FILE* archivo = fopen(ruta_archivo, "r");

	if (archivo == NULL) 
		return NULL;

	int leido = leer_pokemon(archivo, &pokemon_aux);

<<<<<<< HEAD
<<<<<<< HEAD
  if (leido != 4) {
    fclose(archivo);
    return NULL;
  }
=======
=======
>>>>>>> a001599c2f597723c2c4b24ecf7d5cf7d8d69ddf
  	if (leido != 4) {
    		fclose(archivo);
    		return NULL;
  	}

  	arrecife = malloc(sizeof(arrecife_t));

	if (arrecife == NULL)
		return NULL;

	arrecife->pokemon = NULL;
	arrecife->cantidad_pokemon = 0;
<<<<<<< HEAD
>>>>>>> origin/master

  arrecife = malloc(sizeof(arrecife_t));

	if (arrecife == NULL) {
    fclose(archivo);
		return NULL;
  }

	arrecife->pokemon = NULL;
	arrecife->cantidad_pokemon = 0;
=======
>>>>>>> a001599c2f597723c2c4b24ecf7d5cf7d8d69ddf

	while (leido == 4) {

		p_pokemon = realloc(arrecife->pokemon, (size_t)(arrecife->cantidad_pokemon + 1) * sizeof(pokemon_t));

		if (p_pokemon == NULL) {
			fclose(archivo);
			return arrecife;
		}

		arrecife->pokemon = p_pokemon;

<<<<<<< HEAD
<<<<<<< HEAD
    strcpy(arrecife->pokemon[arrecife->cantidad_pokemon].especie, pokemon_aux.especie);
    arrecife->pokemon[arrecife->cantidad_pokemon].velocidad = pokemon_aux.velocidad;
    arrecife->pokemon[arrecife->cantidad_pokemon].peso = pokemon_aux.peso;
    strcpy(arrecife->pokemon[arrecife->cantidad_pokemon].color, pokemon_aux.color);
=======
=======
>>>>>>> a001599c2f597723c2c4b24ecf7d5cf7d8d69ddf
    		strcpy(arrecife->pokemon[arrecife->cantidad_pokemon].especie, pokemon_aux.especie);
    		arrecife->pokemon[arrecife->cantidad_pokemon].velocidad = pokemon_aux.velocidad;
    		arrecife->pokemon[arrecife->cantidad_pokemon].peso = pokemon_aux.peso;
    		strcpy(arrecife->pokemon[arrecife->cantidad_pokemon].color, pokemon_aux.color);
<<<<<<< HEAD
>>>>>>> origin/master
=======
>>>>>>> a001599c2f597723c2c4b24ecf7d5cf7d8d69ddf

		(arrecife->cantidad_pokemon)++;

		leido = leer_pokemon(archivo, &pokemon_aux);
	}

	fclose(archivo);
	return arrecife;
}

acuario_t* crear_acuario() {

	acuario_t* acuario = malloc(sizeof(acuario_t));

	if (acuario == NULL)
		return NULL;

	acuario->pokemon = NULL;
	acuario->cantidad_pokemon = 0;

	return acuario;
}

int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion) {

	int transladables = 0;

	for (int i = 0; i < arrecife->cantidad_pokemon; i ++) {
		if (seleccionar_pokemon(arrecife->pokemon + i))
			transladables++;
	}

	if (transladables < cant_seleccion)
		return -1;

	int i = 0;
	transladables = 0;


	while (i < arrecife->cantidad_pokemon && transladables < cant_seleccion) {

		if (seleccionar_pokemon(arrecife->pokemon + i)) {

			pokemon_t* aux;
			aux = realloc(acuario->pokemon, (size_t) (acuario->cantidad_pokemon + 1) * sizeof(pokemon_t));

			if (aux == NULL)
				return -1;
			(acuario->pokemon) = aux;

			*(acuario->pokemon + acuario->cantidad_pokemon) = *(arrecife->pokemon + i);
			acuario->cantidad_pokemon++;

			for (int j = i; j < arrecife->cantidad_pokemon - 1; j++) 
<<<<<<< HEAD
<<<<<<< HEAD
				arrecife->pokemon[j] = arrecife->pokemon[j + 1]; 
=======
=======
>>>>>>> a001599c2f597723c2c4b24ecf7d5cf7d8d69ddf
				*(arrecife->pokemon + j) = *(arrecife->pokemon + j + 1); 
>>>>>>> origin/master
			aux = realloc(arrecife->pokemon, (size_t) (arrecife->cantidad_pokemon + 1) * sizeof(pokemon_t));

			if (aux == NULL)
				return -1;

			(arrecife->pokemon) = aux;

			(arrecife->cantidad_pokemon)--;
			transladables++;
		} else {
			i++;
		}
	}
	return 0;
}

void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)) {
	for (int i = 0; i < arrecife->cantidad_pokemon; i++) 
		mostrar_pokemon(arrecife->pokemon + i);
}

int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo) {

	FILE* archivo = fopen(nombre_archivo, "w");

	if (archivo == NULL)
		return -1;

	for (int i = 0; i < acuario->cantidad_pokemon; i++)
		escribir_pokemon(archivo, (acuario->pokemon + i));

	fclose(archivo);
	return 0;
}

void liberar_acuario(acuario_t* acuario) {
	if (acuario != NULL) {
		if (acuario->cantidad_pokemon > 0)
			free(acuario->pokemon);
		free(acuario);
	}
}

void liberar_arrecife(arrecife_t* arrecife) {
	if (arrecife != NULL) {
		if (arrecife->cantidad_pokemon > 0)
			free(arrecife->pokemon);
		free(arrecife);
	}
}

