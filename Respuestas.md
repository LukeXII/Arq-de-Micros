
---

# Preguntas orientadoras

1. Describa brevemente los diferentes perfiles de familias de
microprocesadores/microcontroladores de ARM. Explique alguna de sus diferencias
características.

Los principales perfiles de familias de microprocesadores/microcontroladores de ARM se denominan A, R y M. Cada uno de ellos está diseñado para distintas aplicaciones:
* El perfil A (application) consta de procesadores de alta performance y está orientado a la implementación de sistemas operativos. A diferencia de los otros perfiles, estos incluyen una MMU (memory management unit).
* El perfil R (real time) está optimizado para aplicaciones de tiempo real y de seguridad crítica.
* El perfil M (microcontrollers) está orientado para dispositivos de consumo masivo, bajo costo y bajo consumo de energía.

---

# Cortex M

1. Describa brevemente las diferencias entre las familias de procesadores Cortex M0, M3 y M4.

Una de las principales diferencias entre estos tres tipos de procesadores es el largo de las instrucciones de su set de instrucciones. El M0 cuenta con instrucciones en su mayoría de 16 bits y algunas de 32 bits (instrucciones de salto). el M3 con instrucciones de 16, 32 y 
El M0 es un procesador de bajo consumo, bajo costo pero no está preparado para correr un RTOS.

2. ¿Por qué se dice que el set de instrucciones Thumb permite mayor densidad de código? Explique.

El set de instrucciones Thumb es de mayor densidad de código (en comparación con el set ARM) ya que este es un subset del set ARM y sus instrucciones son de 16 bits de largo, a diferencia del set ARM cuyas instrucciones son de 32 bits. Por lo tanto, en el espacio que ocupa una instruccion del set ARM caben dos instrucciones del set Thumb.

Las instrucciones Thumb operan con la misma configuración de registros que ARM por lo que hay completa interoperabilidad entre estos dos sets. En tiempo de ejecución las instrucciones Thumb de 16 bits son descomprimidas a instrucciones ARM de 32 bits sin pérdida de performance.

Un código escrito en Thumb ocupa aproximadamente el 65% que un código escrito con el set ARM por lo tanto hace que el core ARM 7 sea ideal para aplicaciones embebidas con memoria limitada, donde la densidad de código es importante.

3. ¿Qué entiende por arquitectura load-store? ¿Qué tipo de instrucciones no posee este tipo de arquitectura?

Una arquitectura load-store implica que el set de instrucciones del microcontrolador está compuesto por dos tipos de instrucciones: instrucciones de acceso a memoria e instrucciones de operaciones de la ALU. 
Las de acceso a memoria cargan datos desde la memoria a los registros internos del procesador (lectura) y también desde estos registros hacia la memoria (escritura).
Las instrucciones de operaciones de la ALU tienen como operandos solo registros del procesador. Por lo tanto, para ejecutar operaciones entre posiciones de memoria primero se deben cargar estas en los registros del procesador, no existen instrucciones que ejecuten operaciones de la ALU directamente en memoria.

4. ¿Cómo es el mapa de memoria de la familia?
5. ¿Qué ventajas presenta el uso de los “shadowed pointers” del PSP y el MSP?
6. Describa los diferentes modos de privilegio y operación del Cortex M, sus relaciones y
como se conmuta de uno al otro. Describa un ejemplo en el que se pasa del modo
privilegiado a no priviligiado y nuevamente a privilegiado.
7. ¿Qué se entiende por modelo de registros ortogonal? Dé un ejemplo.
8. ¿Qué ventajas presenta el uso de instrucciones de ejecución condicional (IT)? Dé un
ejemplo.
9. Describa brevemente las excepciones más prioritarias (reset, NMI, Hardfault).
10. Describa las funciones principales de la pila. ¿Cómo resuelve la arquitectura el llamado
a funciones y su retorno?

Las principales funciones de la pila son:
* **Push**: copia el valor de un registro en la posición apuntada por la pila. El puntero pasa a apuntar a la siguiente posición disponible (siguiente posición mas baja en el mapa de memoria).
* **Pop**: copia el valor de la posición anterior a la posición apuntada por la pila en un registro. El puntero queda apuntando a la siguiente posición disponible en la pila.

El stack pointer también tiene otras funciones como peek, swap, duplicate y rotate. En la primera se recupera el proximo valor del stack en un registro al igual que en la función pop, pero sin incrementar el puntero a la siguiente posición disponible.

En la función swap se intercambian las posiciones de los ultimos dos valores de la pila.

11. Describa la secuencia de reset del microprocesador.
12. ¿Qué entiende por “core peripherals”? ¿Qué diferencia existe entre estos y el resto de
los periféricos?

Los core peripherals son los periféricos ya definidos e implementados por el fabricante (ARM). A diferencia del resto de los periféricos, estos se encuentran físicamente en el nucleo (core) del procesador ya que es necesario que sean de baja latencia.

13. ¿Cómo se implementan las prioridades de las interrupciones? Dé un ejemplo.
14. ¿Qué es el CMSIS? ¿Qué función cumple? ¿Quién lo provee? ¿Qué ventajas aporta?

El CMSIS es una interfaz de software común a todos los microprocesadores Cortex que se encuentra implementada en C. Se trata basicamente de una libreria escrita en C para que el programador pueda facilmente acceder y usar los core peripherals del microprocesador. Se trata de una capa de software que se encuentra entre la capa de middleware y el hardware.

Consta de una parte ya definida por ARM y otra dependiente del fabricante del chip.

15. Cuando ocurre una interrupción, asumiendo que está habilitada ¿Cómo opera el
microprocesador para atender a la subrutina correspondiente? Explique con un ejemplo.
16. ¿Cómo cambia la operación de stacking al utilizar la unidad de punto flotante?
17. Explique las características avanzadas de atención a interrupciones: tail chaining y late
arrival.
18. ¿Qué es el systick? ¿Por qué puede afirmarse que su implementación favorece la
portabilidad de los sistemas operativos embebidos?

El systick es un periférico de los procesadores ARM que se encarga de hacer una llamada al scheduler cada un tiempo fijo de 1ms. Esto favorece la portabilidad de los sistemas operativos embebidos ya que evita que este se deba implementar para cada fabricante de microcontroladores.

19. ¿Qué funciones cumple la unidad de protección de memoria (MPU)?

La MPU es bloque de hardware ubicado en el procesador que permite dar al software distintos niveles de acceso a ciertas secciones de memoria. Se encarga de monitorear todas las transacciones entre el procesador y la memoria. El principal objetivo de esto es prevenir a un proceso acceder a una región de la memoria que no se le asignó, evitando que este afecte a otro proceso o al mismo sistema operativo.

20. ¿Cuántas regiones pueden configurarse como máximo? ¿Qué ocurre en caso de haber
solapamientos de las regiones? ¿Qué ocurre con las zonas de memoria no cubiertas por las
regiones definidas?
21. ¿Para qué se suele utilizar la excepción PendSV? ¿Cómo se relaciona su uso con el resto
de las excepciones? Dé un ejemplo.
22. ¿Para qué se suele utilizar la excepción SVC? Expliquelo dentro de un marco de un
sistema operativo embebido.

---

# ISA

1. ¿Qué son los sufijos y para qué se los utiliza? Dé un ejemplo.

Los sufijos son letras adicionales que se agregan a las instrucciones base y consecuentemente generan una variante de dicha instrucción, es decir, una instrucción con una ligera diferencia de funcionamiento con respecto a la original. Por ejemplo en la instrucción **ldr** se tiene:

* **ldr**: instrucción base u original. Carga en un registro los 32 bits de una posición de memoria determinada.
* **ldrh**: instrucción con sufijo 'h' (base + h). Carga en un registro los primero 16 bits de la posición de memoria. Completa los bits superiores con ceros.
* **ldrb**: instrucción con sufijo 'b' (base + b). Carga en un registro los primero 8 bits de la posición de memoria. Completa los bits superiores con ceros.

2. ¿Para qué se utiliza el sufijo ‘s’? Dé un ejemplo.

Si el sufijo 's' esta presente en la instrucción entonces los flags del CCR (**C**ondition **C**ode **R**egister) son actualizados luego de la ejecución de la misma. Esto implica que los flags N, Z, C y V son actualizados en base al resultado de la operación.

3. ¿Qué utilidad tiene la implementación de instrucciones de aritmética saturada? Dé un
ejemplo con operaciones con datos de 8 bits.

La principal ventaja que trae la aritmética saturada es que, el resultado de una operación, al no poder hacer un "wrap around", es decir, dar la vuelta cuando hay un overflow, el valor resultante, aunque de todas formas será incorrecto, será numéricamente mas cercano al valor verdadero. Esto es ya que el valor se encuentra limitado entre un máximo y un mínimo.

Otra ventaja de la aritmética saturada es que permite implementar algoritmos mas eficientes en el campo del procesamiento digital de señales. Por ejemplo, al ajustar el nivel de volumen de una señal de sonido alcanzar un valor de saturación causaría menos distorsión que en el caso que el valor desborde.

Ejemplo de operación con aritmética saturada:

Suponiendo que el intervalo válido de valores es de 0 a 255 (8 bits) y el resultado de todas las operaciones esta saturado.

* 50 x (7 - 1) = 255

* 50 x 6 - 50 x 1 = 205

En este caso se observa que la propiedad de la distributividad falla en la aritmética saturada.

4. Describa brevemente la interfaz entre assembler y C ¿Cómo se reciben los argumentos
de las funciones? ¿Cómo se devuelve el resultado? ¿Qué registros deben guardarse en la
pila antes de ser modificados?

Cuando se llama a una función el procesador guarda en el stack primero todos los registros que se encontraba utilizando y luego los parámetros que la función recibe por argumento. Cuando se comienza a ejecutar la función, esta primero recupera del stack los valores de los argumentos y antes de retornar pone en el stack los valores de retorno de la función. Cuando el programa vuelve de la función saca del stack los valores retornados y luego los valores de los registros, de forma que estos se encuentren en el mismo estado que antes del llamado a la función.

5. ¿Qué es una instrucción SIMD? ¿En qué se aplican y que ventajas reporta su uso? Dé un
ejemplo.

Una instrucción SIMD (Single Instruction Multiple Data) realiza una misma operación sobre mas de un dato. 

Es una técnica empleada para llevar a cabo paralelismo a nivel de datos, es decir, operar sobre mas de un dato en una misma instrucción.