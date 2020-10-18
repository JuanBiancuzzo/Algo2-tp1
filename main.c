#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "evento_pesca.h"

#define FUNCIONES_SELEC 5
#define FUNCIONES_MOSTAR 5

bool selec_pokemon_0(pokemon_t* pokemon) {
	return (strlen(pokemon->especie) > 7);
}

bool selec_pokemon_1(pokemon_t* pokemon) {
	return ((10 < pokemon->velocidad) && (pokemon->velocidad < 50));
}

bool selec_pokemon_2(pokemon_t* pokemon) {
	return (pokemon->peso > 25);
}

bool selec_pokemon_3(pokemon_t* pokemon) {
	return (strlen(pokemon->color) < 5);
}

bool selec_pokemon_4(pokemon_t* pokemon) {
	return ((50 < pokemon->velocidad) && (pokemon->peso < 20));
}

void mostrar_arrecife_0(pokemon_t* pokemon) {

	printf("\n\tEspecie: %s\n", pokemon->especie);
	printf("\tVelocidad: %i\n", pokemon->velocidad);
	printf("\tPeso: %i\n", pokemon->peso);
	printf("\tColor: %s\n", pokemon->color);
	for (int i = 0; i < 30; i++) 
		printf("-");
}

void mostrar_arrecife_1(pokemon_t* pokemon) {

	printf("\n\tEspecie: %s,", pokemon->especie);
	printf("\tVelocidad: %i,", pokemon->velocidad);
	printf("\tPeso: %i,", pokemon->peso);
	printf("\tColor: %s\n", pokemon->color);
	for (int i = 0; i < 80; i++) 
		printf("-");
}

void mostrar_arrecife_2(pokemon_t* pokemon) {

	printf("\n\tEspecie: %s,     Velocidad: %i\n", pokemon->especie, pokemon->velocidad);
	printf("\tColor: %s,     Peso: %i\n", pokemon->color, pokemon->peso);
	for (int i = 0; i < 50; i++) 
		printf("-");
}

void mostrar_arrecife_3(pokemon_t* pokemon) {

	printf("\n\tE: %s, V: %i, P: %i, C: %s\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
	for (int i = 0; i < 55; i++) 
		printf("-");
}

void mostrar_arrecife_4(pokemon_t* pokemon) {

	printf("\n\tE: %s, V: %i\n\tP: %i, C: %s\n", pokemon->especie, pokemon->velocidad, pokemon->peso, pokemon->color);
	for (int i = 0; i < 35; i++) 
		printf("-");
}

void informacion_entrada (int argc, char* argv[]) {
	if (argc < 1)
		strcpy(argv[1], "pokemon_arrecife.csv");
	if (argc < 2)
		strcpy(argv[2], "pokemon_acuario.csv");
	argc = 2;
}

int main(int argc, char* argv[]) {

	informacion_entrada(argc, argv);

	arrecife_t* arrecife = crear_arrecife(argv[1]);
	acuario_t* acuario = crear_acuario();

	int iteraciones = 5;
	int cant_seleccion = 5;

	bool (*seleccionar_pokemon [FUNCIONES_SELEC]) (pokemon_t*);

	seleccionar_pokemon[0] = selec_pokemon_0;
	seleccionar_pokemon[1] = selec_pokemon_1;
	seleccionar_pokemon[2] = selec_pokemon_2;
	seleccionar_pokemon[3] = selec_pokemon_3;
	seleccionar_pokemon[4] = selec_pokemon_4;

	void (*mostrar_pokemon[FUNCIONES_MOSTAR]) (pokemon_t*);

	mostrar_pokemon[0] = mostrar_arrecife_0;
	mostrar_pokemon[1] = mostrar_arrecife_1;
	mostrar_pokemon[2] = mostrar_arrecife_2;
	mostrar_pokemon[3] = mostrar_arrecife_3;
	mostrar_pokemon[4] = mostrar_arrecife_4;

	for (int i = 0; i < iteraciones; i++) {
    if (arrecife != NULL && acuario != NULL) {
			trasladar_pokemon(arrecife, acuario, seleccionar_pokemon[i%FUNCIONES_SELEC], cant_seleccion);
			censar_arrecife(arrecife, mostrar_pokemon[i%FUNCIONES_MOSTAR]);
			printf("\n\n");
		}
	}
  if (arrecife != NULL && acuario != NULL) {
    guardar_datos_acuario(acuario, argv[2]);
  }

	liberar_arrecife(arrecife);
	liberar_acuario(acuario);

	printf("\n");

	return 0;
}
