
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

El mapa de memoria de la familia Cortex-M está dividido en seis regiones, estando cada una asignada a distintas funciones:

* **System**: periféricos privados y componentes de control interno y debug del procesador como el controlador de interrupciones anidado (NVIC)
* **External Device**: utilizado para periféricos externos
* **External RAM**: utilizado para memoria RAM externa
* **Peripherals**: periféricos
* **SRAM**: datos del programa
* **Code**: código del programa y tabla de vectores de excepción

A continuación se puede ver el diagrama del mapa de memoria, junto con las direcciones donde comienza y termina cada región.

<p align="center">
  <img height=450 src=memorymap.png>
</p>

Esta arquitectura tiene gran flexibilidad, es decir, permite que las regiones de memoria sean usadas para otros propósitos. Por ejemplo, los programas pueden ser ejecutados desde la región 'Code' asi como también desde la región SRAM.

Como este mapa es igual para toda la familia Cortex-M resulta sencillo portar software entre dispositivos de la misma familia. Además favorece a los fabricantes de dispositivos de programación y debug.

5. ¿Qué ventajas presenta el uso de los “shadowed pointers” del PSP y el MSP?

El hecho de contar con un stack pointer para el Kernel del OS (MSP) y otro para las tareas de la aplicación (PSP) trae ciertos beneficios:
* Si alguna tarea de la aplicación encuentra algún problema que conlleve a invalidar su propio stack, el stack del Kernel (MSP) y el de las otras tareas probablemente se mantenga intacto, mejorando asi la confiabilidad general del sistema.
* El espacio de stack para cada tarea debe cubrir solamente el máximo uso del stack mas un nivel de stack frame. El espacio de stack necesario para las ISR y los handlers de las interrupciones anidadas es alocado solamente en el stack principal (apuntado por el MSP).
* Facilita la creación de un OS eficiente para los procesadores Cortex-M.
* Un OS puede utilizar la Memory Protection Unit (MPU) para definir la región del stack que cada tarea puede usar. Si en alguna tarea se da un stack overflow la MPU puede disparar una excepción MemManage y prevenir que la tarea sobreescriba regiones de memoria fuera del espacio asignado para su stack.

6. Describa los diferentes modos de privilegio y operación del Cortex M, sus relaciones y
como se conmuta de uno al otro. Describa un ejemplo en el que se pasa del modo
privilegiado a no priviligiado y nuevamente a privilegiado.
7. ¿Qué se entiende por modelo de registros ortogonal? Dé un ejemplo.

Un modelo de registros ortogonal implica que todos los registros de propósito general (R0 a R15) pueden ser argumento de todas las instrucciones del set, dicho de otra forma, todas las instrucciones pueden operar sobre todos los registros del procesador. Por ejemplo las siguientes instrucciones son todas validas:

* LDR R0, [R1]
* STR R10, [PC]
* LDRH LR, [R5]

8. ¿Qué ventajas presenta el uso de instrucciones de ejecución condicional (IT)? Dé un
ejemplo.

El uso de instrucciones de ejecución condicional (If-Then) trae la ventaja de que, si bien algunas instrucciones se ejecutarán y otras, todas pasarán por el procesador evitando la aparición de saltos condicionales, lo que hace que se arruine la continuidad del pipeline.

El hecho de que no se deba realizar un salto en el programa y el pipeline deba vaciar ciertas etapas hace que su eficiencia aumente, ya que evita perder ciclos de clock haciendo esto.

A modo de ejemplo, el siguiente programa representaría una condición if-else:

        LDR R0, #10
        SUBS R0, 1
        BEQ .skip1
        STR R1, [R3], 2
        BA  .skip2
    .skip1:
        STR R1, [R2]
    .skip2:
        ...

Ahora utilizando instrucciones IT seria:

    LDR R0, #10
    SUBS R0, 1
    ITE EQ
    STREQ R1, [R2]
    STRNE R1, [R3], 2

Como se puede ver, el código no tiene saltos condicionales si no que todas sus instrucciones pasarán por el procesador, aunque una de las dos no se ejecutará.

9. Describa brevemente las excepciones más prioritarias (reset, NMI, Hardfault).

Reset: es la excepción con mayor nivel de prioridad de todo el NVIC y su handler se ejecutará siempre primero luego de detectado el reset por mas que otras interrupciones se disparen.

NMI: una Non-Maskable Interrupt es una excepción de hardware que no se puede enmascarar, es decir, que no se puede deshabilitar. A diferencia de una interrupción común, el procesador no puede ignorar una NMI en ningún momento. Generalmente se las asocia a las fallas de hardware como un Brownout reset (caída de la tensión de alimentación).

Hardfault: al igual que NMI, esta excepción no puede ser deshabilitada y es disparada cuando el programa intenta realizar alguna acción prohibida como ser escribir o leer posiciones de memoria para las que no se tiene permiso, acceder a periféricos deshabilitados, dividir por cero, etc.

10. Describa las funciones principales de la pila. ¿Cómo resuelve la arquitectura el llamado
a funciones y su retorno?

Las principales funciones de la pila son:
* **Push**: copia el valor de un registro en la posición apuntada por la pila. El puntero pasa a apuntar a la siguiente posición disponible (siguiente posición mas baja en el mapa de memoria).
* **Pop**: copia el valor de la posición anterior a la posición apuntada por la pila en un registro. El puntero queda apuntando a la siguiente posición disponible en la pila.

El stack pointer también tiene otras funciones como peek, swap, duplicate y rotate. En la primera se recupera el proximo valor del stack en un registro al igual que en la función pop, pero sin incrementar el puntero a la siguiente posición disponible.

En la función swap se intercambian las posiciones de los ultimos dos valores de la pila.

11. Describa la secuencia de reset del microprocesador.

Luego de que se detecte cualquiera de los tres tipos de reset del microcontrolador (power on reset, system reset o processor reset) y antes de que el procesador comience a ejecutar el programa en memoria, el proceso de reset se da de la siguiente forma:
* Se lee la primera posición del mapa de memoria, correspondiente a la dirección inicial del MSP.
* Se lee la segunda posición del mapa de memoria, correspondiente al vector de reset (dirección de comienzo del reset handler).
* El procesador guarda las dos direcciones leídas en el MSP y el PC respectivamente.

12. ¿Qué entiende por “core peripherals”? ¿Qué diferencia existe entre estos y el resto de
los periféricos?

Los core peripherals son los periféricos ya definidos e implementados por el fabricante (ARM). A diferencia del resto de los periféricos, estos se encuentran físicamente en el nucleo (core) del procesador ya que es necesario que sean de baja latencia.

13. ¿Cómo se implementan las prioridades de las interrupciones? Dé un ejemplo.

Al habilitar la interrupción de alguno de los periféricos en el NVIC a esta se le debe asignar un nivel de prioridad. Se pueden configurar hasta 240 interrupciones y, dependiendo del fabricante del microcontrolador y su aplicación, entre 8 (3 bits) y 256 (8 bits) niveles de prioridad.

A continuación se muestra un diagrama con los niveles de prioridad en el caso de 3 y 4 bits de prioridad (total de 8 y 16 niveles respectivamente) ordenados de forma descendente. El nivel de prioridad de las tres exceptions (Reset, NMI y Hard fault) no son configurables y siempre tienen mayor prioridad que las interrupciones ya que deben ser atendidas primero.

<p align="center">
  <img height=450 src=prioritylevels.png>
</p>

Los niveles de prioridad funcionan de la siguente forma: supongamos que se tiene una interrupción del SPI configurada con un nivel de prioridad 0x20 y otra del I2C configurada con un nivel de prioridad 0x80. El procesador se encuentra corriendo normalmente y en un determinado instante llega la interrupción del I2C por lo que el procesador consultará en el NVIC el vector de la ISR (subrutina de atención de la interrupción) correspondiente a esta interrupción y saltará del programa principal a esta dirección para ejecutarla. Ahora supongamos que mientras el procesador se encuentra atendiendo esta ISR ocurre la interrupción del SPI. En este caso, como ya se encuentra atendiendo una interupción, consultará en el NVIC los niveles de prioridad de la interrupción del I2C y del SPI y las comparará. Como el del SPI es mayor al del I2C entonces el procesador dejará de atender la ISR del I2C y pasará a ejecutar la del SPI. Cuando termine de ejecutarla, volverá a seguir ejecutando la del I2C.

En el caso que la interrupción del SPI hubiese tenido un nivel de prioridad menor, el procesador primero terminaría de ejecutar la ISR del I2C y luego atendería la del SPI.

Estos niveles de prioridad, llamados prioridad de grupo, contienen a su vez otro nivel de prioridad denominado sub-prioridad. Se pueden configurar varias interrupciones con el mismo nivel de prioridad de grupo pero deben tener un distinto nivel de sub-prioridad. La regla de atención de la ISR mantiene la misma lógica de ejecución: si dos interrupciones con el mismo nivel de prioridad de grupo deben ser atendidas, la que tenga el mayor nivel de sub-prioridad será ejecutada primero.

14. ¿Qué es el CMSIS? ¿Qué función cumple? ¿Quién lo provee? ¿Qué ventajas aporta?

El CMSIS es una interfaz de software común a todos los microprocesadores Cortex que se encuentra implementada en C. Se trata basicamente de una libreria escrita en C para que el programador pueda facilmente acceder y usar los core peripherals del microprocesador. Se trata de una capa de software que se encuentra entre la capa de middleware y el hardware.

Consta de una parte ya definida por ARM y otra dependiente del fabricante del chip.

15. Cuando ocurre una interrupción, asumiendo que está habilitada ¿Cómo opera el
microprocesador para atender a la subrutina correspondiente? Explique con un ejemplo.

Cuando se dispara una interrupción que está habilitada, el procesador pasa a atender la ISR mediante la siguiente secuencia:

* Se guardan en el stack los registros del procesador y, si este se encontraba en modo Thread (ejecutando un OS), se guardará también la dirección del PSP de la tarea que se estaba ejecutando. Si no, guardará la dirección del MSP.
* Se busca del NVIC el vector de la excepción (dirección de comienzo del handler de la interrupción). Esto puede ocurrir en paralelo a la operación de stack, para reducir la latencia de atención de la subrutina.
* Se buscan las instrucciones del handler para su ejecución.
* Se actualizan los registros del NVIC y el core, como el estado pendiente de atención de la excepción y el estado activo. También se actualizan el PSR, LR, PC y el SP (dependiendo de cual se estaba usando, se actualiza el MSP o el PSP).

16. ¿Cómo cambia la operación de stacking al utilizar la unidad de punto flotante?

Al utilizar la FPU (unidad de punto flotante) el proceso de stacking de los registros del procesador se denomina lazy stacking y basicamente esto consiste, en el contexto de una interrupción, en no poner en el stack los registros de la FPU si no son utilizados en el programa ni en la ISR. Este método tiene la ventaja de hacer decrementar el tiempo que se tarda en atender una interrupción.

La FPU cuenta con 16 registros (S0 a S15) para realizar las operaciones de punto flotante. Al llegar una interrupción el lazy stacking puede actuar de X formas, dependiendo si la FPU es utilizada en el programa o en la ISR:

* Si ni en el programa ni en la ISR se utiliza la FPU, el stacking de los registros no se realiza.
* Si en el programa se utiliza la FPU pero no en la ISR, tampoco se realiza el stacking ya que los registros no serán modificados.
* Si en el programa no se utiliza la FPU pero si en la ISR, el stacking no se realiza ya que no es necesario preservar los valores.
* Si la FPU es utilizada en el programa y en la ISR, el stacking de los registros no se hace hasta que se deba hacer uso de la FPU.

La detección del uso de la FPU y el stacking son realizados automáticamente por el hardware, lo cual libera al programador de tener que implementar este proceso.

17. Explique las características avanzadas de atención a interrupciones: tail chaining y late
arrival.

Tail chaining: es un técnica implementada por el procesador cuando este se encuentra atendiendo una subrutina de interrupción y otra excepción del mismo o mayor nivel se dispara. En lugar de terminar de ejecutar la ISR, recuperar del stack los registros del procesador para inmediatamente volver a stackearlos y atender la ISR de la nueva interrupción lo que se hará es saltear los pasos de unstacking y stacking y atender directamente la ISR. De esta forma se pueden ahorrar ciclos de clock y atender la interrupción mucho mas rápido.

Late arrival: cuando una excepción se dispara el procesador pasa a atender la subrutina de interrupción. Antes de esto, como al pasar a ejecutar cualquier función, el procesador guarda en el stack los registros del procesador para preservar su valor. Si durante este proceso se dispara una excepción de mayor prioridad que la primera, el procesador terminará el stacking y en lugar de pasar a ejecutar la subrutina de la primera interrupción, pasará a ejecutar la de mayor nivel de priorirdad.

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

La excepción PendSV tiene especial importancia en el funcionamiento de sistemas operativos ya que es utilizada para hacer el cambio de contexto entre tareas. En el caso que se este atendiendo una interrupción y el Systick o una instrucción SVC generen una interrupción para el cambio de contexto, esta excepción retrasa este pedido hasta que el resto de las ISR pendientes terminen de ejecutarse. Esto es para que no se retrase la ejecución de la ISR.

Una vez que se debe cambiar de contexto, el OS dispara la excepción PendSV y hace esto dentro del handler. Para esto, como todas las ISR deben terminar de ejecutarse antes de atender la de PendSV, esta debe estar configurada como la excepción de mas baja prioridad.

22. ¿Para qué se suele utilizar la excepción SVC? Expliquelo dentro de un marco de un
sistema operativo embebido.

La excepción SVC es un mecanismo que permite a los procesos de un OS que tienen acceso no privilegiado acceder a recursos de hardware que si lo tienen mediante un servicio propio del OS, funcionando como una API. Esto vuelve al sistema mas seguro ya que evita que dichas tareas obtengan acceso no autorizado a hardware critico.

Además el SVC permite a las tareas ser desarrolladas independientemente del OS porque estas no necesitan tener las direcciones exactas de los servicios del OS. Las tareas solo tienen que conocer el numero de servicio del SVC y los parametros requeridos por los servicios del OS. La programación a nivel hardware es manejada directamente por los drivers de los dispositivos.

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

    50 x (7 - 1) = 255
    50 x 6 - 50 x 1 = 205

En este caso se observa que la propiedad de la distributividad falla en la aritmética saturada.

4. Describa brevemente la interfaz entre assembler y C ¿Cómo se reciben los argumentos
de las funciones? ¿Cómo se devuelve el resultado? ¿Qué registros deben guardarse en la
pila antes de ser modificados?

Cuando se llama a una función el procesador guarda en el stack primero todos los registros que se encontraba utilizando y luego los parámetros que la función recibe por argumento. Cuando se comienza a ejecutar la función, esta primero recupera del stack los valores de los argumentos y antes de retornar pone en el stack los valores de retorno de la función. Cuando el programa vuelve de la función saca del stack los valores retornados y luego los valores de los registros, de forma que estos se encuentren en el mismo estado que antes del llamado a la función.

5. ¿Qué es una instrucción SIMD? ¿En qué se aplican y que ventajas reporta su uso? Dé un
ejemplo.

Una instrucción SIMD (Single Instruction Multiple Data) realiza una misma operación sobre mas de un dato de forma paralela. El largo de estos datos pueden ser de 8 o 16 bits.

Es una técnica empleada para llevar a cabo paralelismo a nivel de datos, es decir, aplicar sobre mas de un dato una misma instrucción. Esto es particularmente ventajoso ya que se realizan varias operaciones en el tiempo de ejecución que toma una sola instrucción.