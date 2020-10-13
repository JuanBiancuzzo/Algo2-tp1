#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "evento_pesca.h"

bool seleccionar_pokemon_0(pokemon_t* pokemon) {
	return (strlen(pokemon->especie) > 7);
}

bool seleccionar_pokemon_1(pokemon_t* pokemon) {
	return ((25 < pokemon->velocidad) && (pokemon->velocidad < 50));
}

bool seleccionar_pokemon_2(pokemon_t* pokemon) {
	return (pokemon->peso > 25);
}

bool seleccionar_pokemon_3(pokemon_t* pokemon) {
	return (strlen(pokemon->color) < 5);
}

bool seleccionar_pokemon_4(pokemon_t* pokemon) {
	return ((50 < pokemon->velocidad) && (pokemon->peso < 20));
}

int main(int argc, char* argv[]) {

	arrecife_t* arrecife = crear_arrecife(argv[1]);
	acuario_t* acuario = crear_acuario();

	bool (*seleccion_0) (pokemon_t*) = seleccionar_pokemon_0;

	int i = trasladar_pokemon(arrecife, acuario, seleccion_0, 5);

	printf("%i", i);

	liberar_arrecife(arrecife);
	liberar_acuario(acuario);

}
