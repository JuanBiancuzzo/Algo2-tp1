
	    [Introducción]

   [Descripción del trabajo]

	El trabajo consiste de crear una libreria para que una persona, en
	este caso Misty, pueda simular su forma de pezcar en el arrecife.

	Para lograr eso leemos de un archivo los peses que habría en el
	arrecife y los ponemos en un arreglo dinamico en el espacio de memoria
	HEAP, y después simulando su pezca vamos transfiriendo pokemones del
	arrecife a su acuario según su forma de pezcar, reduciendo el arreglo
	del arrecife y aumentando el arreglo dinamico del acuario, y mostarndo por
	pantalla los pokemones que todavía quedan en el arrecife, y por último
	se guarda en otro archivo todos los pokemones que terminaron en su
	acuario, y liberar los arreglos dinamicos.

    [Explicación de compilación y ejecución]

    	Para compilarlo usamos la linea:

  	    gcc -g -Wall -Wconversion -Werror -std=c99 *.c -o evento_pesca
  	
	También hice una makefile donde si pones "make build" compila de esa
	forma para que sea mucho más comodo

	Para ejecutarlo usamos la linea:

	    ./evento_pesca [Archivo_arrecife] [Archivo_acuario]

	Pero ninguno de los dos es obligatorios escribirlo, en el caso de no
	poner ninguno de los dos entonces el programa va a suponer que vas a
	usar a pokemon_arrecife.csv y pokemon_acuario.csv

	También en el makefile tenes un caso para esto, pones "make exe" y
	ejecuta el archivo con esos dos archivos que mencioné antes

  Como una nota aparte, también si pones "make limpear_acuario" elimina
  el archivo pokemon_acuario.csv y lo crea de nuevo. Espero que ayude


    [Explicación breve de conceptos]

    	    [Punteros]
		
		Los punteros son variables que se encargan de guardar la
		dirección de otra variable. Se pueden interpretar como si
		tenes un casa, un puntero es el papel que dice cual es la
		dirección de esa casa.

		Estos se expresan como:
		    
		    [tipo_variable]* [Nombre];
	
	    [Aritmética de punteros]

		La aritmética de punteros se refiere a una forma diferente de
		recorrer un arreglo y lo clave a entender esto es entender que
		los arreglos son punteros a un grupo de items que estan
		concatenados.

		Si lo interpretamos como hicimos antes, un arreglo es la
		direccion de un edificio donde cada item es cada piso.
		
		Si queremos ir al segundo piso, siguiendo la analogía,
		la forma que sabíamos era edificio[1]; y con la aritmética
		de punteros podemos escribirlo *(edificio +1); el +1 nos esta
		indicando que se movió un piso.

	    [Punteros a funciones]

	    	Para un cambio, más punteros. Los punteros a función te
		permite mandar como parametro toda una función lo cual permite
		delegar a la persona que va a usar la función que vos estas
		haciendo decidir el funcionamiento de la función que te pasan
		como parametro.

		Es decir, si vos estas haciendo, por ejemplo, un algoritmo de
		ordenamiento para alguien (ese alguien también puede ser uno
		mismo). 

		El tipo de dato que queres ordenar no es simplemente
		que número es mayor, entonces para no complicarte la vida
		intentando saber como quiere comparar los tipos de datos ese
		alguien, lo que podes hacer es pedirle a ese alguien que te
		pase una función, como parametro, que devuelva true si el
		primer tipo de dato es mayor y false si es menor. 

		Ahora ya no tenes que procuparte en como hacer para ver que
		item es mayor o menos, sino que te podes concentrar en el
		algoritmo de ordenamiento.

	   
	   [Malloc y Realloc]

	   	La función malloc() te deja reservar memoria en el HEAP, que
		es un lugar en memoria cuyo proposito (que fancy ese cuyo) es
		guardar grupos de memoria de forma dinamica donde el
		programador tiene todo la libertad de guardar memoria y
		liberar memoria.

		Entonces malloc() te deja guardar una cantidad que
		especifiques de memoria y te devuelve un puntero a esa memoria
		reservada, pero eso no es muy dinamico, entonces para eso esta 
		la función realloc() que pasandole un puntero a una memoria 
		reservada, te permite aumentar, o reducir, el tamaño de la
		memoria reservada.

		Tecnicamente realloc() puede funcionar como malloc() si el
		puntero que le pasas es NULL y como nota aparete también
		podrias liberar esa memoria si al tamaño que le pones a
		realloc() es 0.

