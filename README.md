
# Evento de pesca
 
## Descripción del trabajo

Esta librería permite crear tanto un arrecife como un acuario, el arrecife se carga de pokemones 
a partir de un archivo. Permite transferir los pokemones del arrecife al acuario según el criterio
del usuario, y permite guardar los pokemones que estan en el acuario en un archivo.

### Puntos importantes

* Cuando se crea el arrecife se reserva un espacio de memoria en el heap, cuando se carga los 
pokemones a partir de un archivo, en el caso que no se encuentre el archivo o haya algún otro 
error en la lectura del archivo se libera el espacio de memoria reservado para el arrecife. Esto
lo hacemos para que no se tenga que llamar a la función liberar de forma obligatoria.
En el caso que ocurra algún error en el medio del archivo ya sea porque hay un error de tipeo o 
algún error inesperado, se devuelve el arrecife con la lista de pokemones que se hayan guardado
hasta ese momento.

* Cuando se transfiere los pokemones del arrecife al acuario, estos pasarán si cumplen con la 
condición que el programador desee y si en el arrecife hay una cierta cantidad de pokemones que
la cumplan. Para lograr esto primero confirmamos que haya la suficiente cantidad de pokemones en
el arrecife para que ocurra el translado y después, aumentando el espacio, agregamos el pokemon 
en el acuario y reducimos el espacio del arrecife. 
Aunque pasemos dos veces por el arreglo de pokemones, preferímos hacerlo de esta forma ya que nos
fácilita la validación la transferencia y el restaurar el arrecife si esta no es cumplida

* La liberación tanto del arrecife como del acuario estan hechas para que si se liberó o el
arreglo y/o el arrecife/acuerio, no haya problema en dobles liberado o perdida de memoria. Esto 
hace más fácil el proceso y sin tener que procuparse por si se liberó en el proceso de 
transferencia.

## Explicación de compilación y ejecución

### Compilación

Para la compilación se tiene que usar la línea 

``` bash
gcc -g -Wall -Wconversion -Werror -std=c99 *c -o evento_pesca
```

También se puede usar make de esta forma: 

``` bash
make build
```

### ejecución

Para ejecutarlo se tiene que usar la línea

``` bash
./evento_pesca [archivo_arrecife] [archivo_acuario]
``` 

Ninguno de los dos parametros de los archivos son necesario, ya que si no se usan se asume que 
se utilizará los archivos pokemon_arrecife.csv o pokemon_acuario.csv. También esta la posibilidad
de ejecutar este comando con make de esta forma:

``` bash
make exe
``` 

Como nota aparte, hay un comando make que esta hecho para eliminar y crear el archivo 
correspondiente al acuario para que sea más fácil el uso de este archivo.

``` bash
make limpear_acuario
``` 

## Explicación de conceptos

### Punteros

Los punteros son variables que se encargan de guardar la dirección de memoria de otra variable. 
Se puede pensar como si uno tiene una casa, un puntero sería el equivalente tener cual es la 
dirección de esa casa. Esta se declara de esta forma:

``` c
[tipo_variable]* [Nombre];
```

y podemos ver el valor de la variable que guardamos su dirección, si escribimos:

``` c 
*[Nombre];
```

si volvemos a la interpretación de antes, esto equivaldría a usar la dirección de la casa para 
llegar y ver el contenido de la casa.

### Aritmética de punteros

La aritmética de punteros se refiere a una forma diferente de recoorer un arreglo y lo importante
esta en entender que los arreglos son un puntero a un grupo de items que guardan.
Si lo interpretamos con la analogía de antes, un arreglo es la dirección de un edificio donde cada
item es un piso.

Si queremos ir al primer piso (estamos suponiendo que tien planta baja este edificio), la forma
que lo haríamos antes es 
``` c 
edificio[1];
```

pero con la aritmética de punteros podemos escribirlo así
``` c 
*(edificio + 1);
```

Si intentamos entender como es que esta notación funciona, desarmemos la escritura. Primero vemos
que tenemos *edificio* que es un puntero, como dije antes, al grupo de items que guarda, en este
caso un edificio tiene tipos. Entonces cuando ponemos "edificio" estamos yendo a la planta baja
de nuestro edificio.
También tenemos un *+1* (que podría ser cualquier número) y eso nos dice cuantos items nos 
desplazamos. Sería ir al ascensor y apretar el número del piso que queres ir.
Por último tenemos el *** que nos índica que tenemos que usar el valor que esta en esa dirección,
y esto sería el equivalente a entrar al departamento.

### Punteros a funciones

Para un cambio, más punteros. Los punteros a función te permite mandar como parametro toda una 
función lo cual te ayuda a delegar parte del funcionamiento que es especifico a la persona que
termine usando tu código.

Es decir, si vos estas haciendo, por ejemplo, un algoritmo de ordenamiento para alguien que te
impone usar un tipo de dato particula, y sorpresa, ese tipo de dato no es fácil de indentificar
si un dato es mayor que otro. Por ejemplo, si tenes un struct de personas, donde tienen la edad,
la altura, el color de pelo, etc. uno no pude decir, de forma objetiva, que una persona es mayor
que la otra.
Entonces lo que podes hacer es pedirle a esa persona que te pase una función, como parametro, que
clasifique que persona es mayor que otra. Y ahora te podes concentrar en desarrollar el algoritmo
de ordenamiento.

En cuanto a la escritura es mucho mejor ver un ejemplo, si tenemos la función:
``` c 
bool clasificador_numeros (int numero_1, int numero_2);
```
y queremos hacer un puntero a esa función, lo escribimos así:
``` c
bool (*clasificador) (int, int) = &clasificador_numeros;
```

Cosas a tener en cuenta, hay que notar que el tipo que devuelve la función tiene que ser igual en 
el puntero a esa función. También que la cantidad de parametros que hay en la función original es
la misma que en el puntero, y que no en necesario poner los nombres.
Si queremos usar ese puntero podemos escribirlo así:
``` c
int pri_numero = 5;
int seg_numero = 6;

(*clasificador) (pri_numero, seg_numero);
```

### Malloc y Realloc

La función malloc() te deja reservar memoria en el HEAP, que es un lugar en memoria cuyo proposito
(que fancy ese cuyo) es guardar grupos de memoria de forma dinamica donde el programador tiene 
toda la libertad de reservar y liberar memoria.

Entonces malloc() te deja guardar una cantidad que especifiques de memoria y te devuelve un 
puntero a esa memoria reservada, pero eso no es muy dinamico, entonces para eso esta la función 
realloc() que pasandole un puntero a una memoria reservada, te permite aumentar o reducir el
tamaño de la memoria reservada.

Si volvemos a la analogía del edificio, malloc() sería el equivalente de comprar un edificio de
los pisos que vos quieras y te devuelve la dirección de ese edificio que compraste. Realloc() 
sería el equivalente a construir o destruir pisos de tu edificio que compraste. 
Esto es muy útil porque te deja tener un arreglo dinamico que depende de cuantas cosas queres 
guardar. Por ejemplo, pensemos que el edificio es un hotel y solo queres tener los pisos que 
esten ocupados, así no desperdicias electricidad para los pisos que no hay gente. Pero otra 
persona llega y quiere estar en tu hotel entonces, a una velocidad sobrehumana, creas un piso más
para esa persona. Y ahora una persona quiere irse de tu hotel entonces, que el poder de los 
dioses, destruis un piso. De esta forma siempre tenes ocupando espacio las personas que necesitan.

En cuanto a la escritura, no hay mucho nuevo, se escriben así:

``` c
malloc(void* puntero, size_t tamaño);
realloc(void* puntero, size_t tamaño_nueva);
```

Lo más importante es tener cuidado con lo que devuelven, porque en caso que no puedan reservar la
memoria que querías estas devuelven NULL y no deverías acceder a esa memoria.
En el caso de realloc() hay que tener en cuenta que puede devolver cosas diferentes dependiendo de
lo que haya logrado. Es decir, puede devolver el puntero original que pasaste pero con el tamaño
nuevo, o te puede devolver otro puntero nuevo con el tamaño nuevo que significa que ya no podes
usar el puntero anterior.
