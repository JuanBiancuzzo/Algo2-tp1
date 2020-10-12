#include <stdlib.h>

#include "evento_pesca.h"

#define FORMATO "%[^;];%i;%i;%[^;]"

int leer_pokemon(FILE* archivo, pokemon_t* pokemon) {
	return fscanf(archivo, FORMATO, pokemon->especie, &(pokemon->velocidad), &(pokemon->peso), pokemon->color);
} 

arrecife_t* crear_arrecife(const char* ruta_archivo) {
	
	arrecife_t* arrecife = malloc(sizeof(arrecife_t));
	pokemon_t* p_pokemon = NULL;
	pokemon_t pokemon_aux;

	if (arrecife == NULL)
		return NULL;

	FILE* archivo = fopen(ruta_archivo, "r");

	if (archivo == NULL)
		return NULL;
	
	int leido = leer_pokemon(archivo, &pokemon_aux);

	while (leido == 4) {

		p_pokemon = realloc(arrecife->pokemon, (size_t) (arrecife->cantidad_pokemon + 1) * sizeof(pokemon_t));

		if (p_pokemon == NULL) { 
			fclose(archivo);
			return arrecife;
		}

		arrecife->pokemon = p_pokemon;
		(*(arrecife->pokemon + arrecife->cantidad_pokemon)) = pokemon_aux;
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

	acuario->pokemon = malloc(sizeof(pokemon_t));

	if (acuario->pokemon == NULL)
		return NULL;

	return acuario;
}

int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion) {
	return 0;
}

void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)) {}

int guardar_datos_acuario(acuario_t* acuario, const char* nombre_archivo) {
	return 0;
}

void liberar_acuario(acuario_t* acuario) {}

void liberar_arrecife(arrecife_t* arrecife) {}

