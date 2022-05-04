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

1. Describa brevemente las diferencias entre las familias de procesadores Cortex M0, M3 y
M4.

El M0 no está preparado para correr un RTOS.

2. ¿Por qué se dice que el set de instrucciones Thumb permite mayor densidad de código?
Explique.

3. ¿Qué entiende por arquitectura load-store? ¿Qué tipo de instrucciones no posee este
tipo de arquitectura?

Una arquitectura load-store implica que el set de instrucciones del microcontrolador está compuesto por dos tipos de instrucciones: instrucciones de acceso a memoria e instrucciones de operaciones de la ALU. 
Las de acceso a memoria cargan datos desde la memoria a los registros internos del procesador (lectura) y también desde estos registros hacia la memoria (escritura).
Las instrucciones de operaciones de la ALU tienen como operandos solo registros del procesador. Por lo tanto, para ejecutar operaciones entre posiciones de memoria primero se deben cargar estas en los registros del procesador, no existen instrucciones que ejecuten operaciones de la ALU directamente en memoria.

4. ¿Cómo es el mapa de memoria de la familia?
5. ¿Qué ventajas presenta el uso de los “shadowed pointers” del PSP y el MSP?
6. Describa los diferentes modos de privilegio y operación del Cortex M, sus relaciones y
como se conmuta de uno al otro. Describa un ejemplo en el que se pasa del modo
privilegiado a no priviligiado y nuevamente a privilegiado.
7. ¿Qué se entiende por modelo de registros ortogonal? Dé un ejemplo.
8. ¿Qué ventajas presenta el uso de intrucciones de ejecución condicional (IT)? Dé un
ejemplo.
9. Describa brevemente las excepciones más prioritarias (reset, NMI, Hardfault).
10. Describa las funciones principales de la pila. ¿Cómo resuelve la arquitectura el llamado
a funciones y su retorno?
11. Describa la secuencia de reset del microprocesador.
12. ¿Qué entiende por “core peripherals”? ¿Qué diferencia existe entre estos y el resto de
los periféricos?
13. ¿Cómo se implementan las prioridades de las interrupciones? Dé un ejemplo.
14. ¿Qué es el CMSIS? ¿Qué función cumple? ¿Quién lo provee? ¿Qué ventajas aporta?
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
2. ¿Para qué se utiliza el sufijo ‘s’? Dé un ejemplo.
3. ¿Qué utilidad tiene la implementación de instrucciones de aritmética saturada? Dé un
ejemplo con operaciones con datos de 8 bits.
4. Describa brevemente la interfaz entre assembler y C ¿Cómo se reciben los argumentos
de las funciones? ¿Cómo se devuelve el resultado? ¿Qué registros deben guardarse en la
pila antes de ser modificados?
5. ¿Qué es una instrucción SIMD? ¿En qué se aplican y que ventajas reporta su uso? Dé un
ejemplo.