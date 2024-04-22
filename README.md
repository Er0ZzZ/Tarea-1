# Descripción

Este sistema ofrece a los usuarios la capacidad de administrar la atención médica de pacientes en un entorno hospitalario. Permite el registro de nuevos pacientes, la asignación de prioridades, la visualización de la lista de espera y la visualización de pacientes por agrupameniento segun su prioridad. Su objetivo es optimizar la eficacia en la atención médica, garantizando que los pacientes en estados críticos sean atendidos con prontitud, para así generar un orden sencillo y automatizado, facilitando el trabajo a los funcionarios.

# Cómo compilarlo

1. Abre en enlace para redirigirte al programa
2. Inicia sesión en caso de que no esté iniciada
3. Selecciona la opcion "Fork & RUN"
4. Oprime el botón "Run" para compilar y ejecutar el programa

# Funcionalidades

## Funcionando correctamente:
* Registrar Pacientes, asignandoles sus datos básicos y la prioridad inicial
* Asignar o modificar la prioridad de los pacientes
* Ver la lista de espera de pacientes, ordenada por prioridad y hora de registro
* Atender al siguiente paciente, respetando el orden de prioridad.
* Ver la lista de pacientes segun prioridad, ordenados por hora de registro

## Problemas conocidos;
* Ordenamiento de pacientes: No se considera el caso si dos pacientes llegan exactamente al mismo tiempo, debido a que no se ha implementado una detección para aquello.
* Pacientes repetidos: El programa no detecta si se ingresan pacientes repetidos, ya que no hay algun algoritmo implementado para detectarlo.
* Manipulación de cadenas: Se utilizan cadenas de caracteres sin verificar los límites. Esto podría llevar a desbordamientos de búfer si el usuario ingresa datos más largos de lo esperado.

## A mejorar:
* Modularizacion: líneas de código repetidas que cumplen la misma función, se puede modificar para que sea un programa mas modular, por ende, mas sencillo de comprender
* Implementar una lógica para que la prioridad se pueda modificar de manera automática.




# Ejemplo de uso

### Paso 1: Registrar un Nuevo Paciente
#### Se comienza registrando un nuevo paciente que acaba de llegar al hospital.


````
Opción seleccionada: 1) Registrar paciente
Ingrese el nombre del paciente: Nicolás Massú
Ingrese el síntoma del paciente: Rotura completa de la unión mediotendinosa y la porción proximal al tendón de Aquiles
Ingrese la edad del paciente: 44
Ingrese la hora de llegada del paciente (No ingrese minutos. No ingrese decimales): 19
Ingrese los minutos de llegada del paciente: 20
Paciente registrado con éxito
````
El sistema registra a Nicolás Massú con una prioridad inicial igual a 3, es decir "Baja", luego guarda la hora de registro. La prioridad puede ser ajustada más tarde basada en una evaluación médica más detallada.


### Paso 2: Asignar Prioridad a un Paciente
#### Tras una evaluación inicial, el médico determina que el estado de Nicolás Massú requiere atención prioritaria.

````
Opción seleccionada: 2) Asignar prioridad a paciente
Ingrese el nombre del paciente: Nicolás Massú
Ingrese la nueva prioridad del paciente: 
1.- Alta
2.- Media
3.- Baja
opcion seleccionada: 1
Prioridad asignada con éxito
````
El sistema actualiza la prioridad de Nicolás Massú a "Alta", asegurando que será uno de las próximas pacientes en ser atendido.

### Paso 3: Ver la Lista de Espera
#### El usuario revisa la lista de espera para ver todos los pacientes y sus prioridades.

````
Opción seleccionada: 3) Mostrar lista de espera

Pacientes en espera:

Nombre: Nicolás Massú
Edad: 44
Síntomas: Rotura completa de la unión mediotendinosa y la porción proximal al tendón de Aquiles
Prioridad: "ALTA"
Hora de Llegada: 19:20
----------------------------------
````

La lista muestra a Nicolás Massú en la parte superior, indicando su prioridad alta y que es el siguiente en línea para recibir atención.


### Paso 4: Atender al Siguiente Paciente
#### Nicolás Massú es llamada para ser atendida basándose en su prioridad.

````
Opción seleccionada: 4) Atender al siguiente paciente
Atendiendo al paciente: "Nicolás Massu"
````

El sistema muestra que Nicolás Massú está siendo atendido y lo elimina de la lista de espera.

### Paso 5: Conocer cuantos pacientes de prioridad "ALTA" hay actualmente
#### En este caso todos los pacientes de prioridad "ALTA" han sido atentidos

````
Opción seleccionada: 5) Mostrar pacientes por prioridad
Ingrese prioridad deseada:
1.- Alta
2.- Media
3.- Baja
Opción seleccionada: 1
Lista de pacientes con prioridad: BAJA
No hay pacientes con prioridad BAJA

````
El sistema indica que todos los pacientes con prioridad "ALTA", ya han sido atendidos
 
### Paso 6: Salir del programa
#### Todos los pacientes han sido atendidos

````
Opción seleccionada: 6) Salir
"Saliendo del sistema de gestión hospitalaria"
````
Todos los pacientes ya estan atendidos en el hospital, por lo tanto es hora de cerrar el sistema.
