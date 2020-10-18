#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "evento_pesca.h"

int leer_pokemon(FILE* archivo, pokemon_t* pokemon) {
	return fscanf(archivo, "%50[^;];%i;%i;%50[^\n]\n", pokemon->especie, &(pokemon->velocidad), &(pokemon->peso), pokemon->color);
}

int escribir_pokemon(FILE* archivo, pokemon_t* pokemon) {
	return fprintf(archivo, "%s;%i;%i;%s\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
}

/*
 * Se encargará de copiar todos los campos del pokemon_secundario al principal
 */
void copiar_pokemon(pokemon_t* pokemon_principal, pokemon_t pokemon_secundario) {

  strcpy(pokemon_principal->especie, pokemon_secundario.especie);
  pokemon_principal->velocidad = pokemon_secundario.velocidad;
  pokemon_principal->peso = pokemon_secundario.peso;
  strcpy(pokemon_principal->color, pokemon_secundario.color);

}

/*
 * A partir de una lista de pokemones eliminará al pokemon que esta en la posición pasada y moverá
 * al resto un lugar para atras
 */
void eliminar_pokemon(int posicion_actual, int* tope, pokemon_t* lista_pokemones) {

  for (int i = posicion_actual; i < (*tope) - 1; i++)
    lista_pokemones[i] = lista_pokemones[i + 1];
  (*tope)--;
}

/*
 * Agrega un pokemon al final de la lista de pokemones
 */
void agregar_pokemon (pokemon_t pokemon, int* tope, pokemon_t* lista_pokemones) {
  copiar_pokemon((lista_pokemones + (*tope)), pokemon);
  (*tope)++;
}

/*
 * Devuelve true si hay suficientes pokemones que cumplan la condición pasada por parametro, en caso
 * que no se cumpla devolverá false
 */
bool cantidad_suficiente(pokemon_t* lista_pokemones, int tope, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion) {

  int transladable = 0;

  for (int i = 0; i < tope; i ++) {
    if (seleccionar_pokemon(lista_pokemones + i))
      transladable++;
  }

  return (transladable >= cant_seleccion);
}

arrecife_t* crear_arrecife(const char* ruta_archivo) {

	arrecife_t* arrecife;
 	pokemon_t* p_pokemon;
	pokemon_t pokemon_aux;
  bool valido = true;

	FILE* archivo = fopen(ruta_archivo, "r");

	if (archivo == NULL)
		return NULL;

	int leido = leer_pokemon(archivo, &pokemon_aux);

 	if (leido != 4) {
   		fclose(archivo);
   		return NULL;
 	}

 	arrecife = malloc(sizeof(arrecife_t));

	if (arrecife == NULL)
    valido = false;

  arrecife->pokemon = NULL;
  arrecife->cantidad_pokemon = 0;

	while (leido == 4 && valido) {

		p_pokemon = realloc(arrecife->pokemon, (size_t)(arrecife->cantidad_pokemon + 1) * sizeof(pokemon_t));

		if (p_pokemon == NULL) {
      valido = false;
		} else {

      arrecife->pokemon = p_pokemon;
      copiar_pokemon(&(arrecife->pokemon[arrecife->cantidad_pokemon]), pokemon_aux);
      (arrecife->cantidad_pokemon)++;

      leido = leer_pokemon(archivo, &pokemon_aux);

    }
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

	int transladables = 0, i = 0;
  bool valido = true;

	if (!cantidad_suficiente(arrecife->pokemon, arrecife->cantidad_pokemon, seleccionar_pokemon, cant_seleccion))
    valido = false;

	while (i < arrecife->cantidad_pokemon && transladables < cant_seleccion && valido) {

		if (seleccionar_pokemon(arrecife->pokemon + i)) {

			pokemon_t* aux;
			aux = realloc(acuario->pokemon, (size_t) (acuario->cantidad_pokemon + 1) * sizeof(pokemon_t));

			if (aux == NULL) {
        valido = false;
      } else {

        (acuario->pokemon) = aux;
        agregar_pokemon(arrecife->pokemon[i], &(acuario->cantidad_pokemon), acuario->pokemon);

        eliminar_pokemon(i, &(arrecife->cantidad_pokemon), arrecife->pokemon);

        aux = realloc(arrecife->pokemon, (size_t) (arrecife->cantidad_pokemon) * sizeof(pokemon_t));

        if (aux == NULL) {
          valido = false;
        } else {
          (arrecife->pokemon) = aux;
          transladables++;
        }

      }

		} else {
			i++;
		}
	}

  if (!valido)
    return -1;
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

