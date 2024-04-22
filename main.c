#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Se crea el struct a utilizar
typedef struct{
  char nombre[50]; //nombre del paciente
  int edad; //edad del paciente
  int prioridad; //prioridad del paciente(de 1 a 3, donde "BAJA" = 3 y, "MEDIA" = 2 y "ALTA" = 1))
  int horaLlegada; //hora de llegada del paciente
  int minutos; //minutos de la hora de llegada del paciente
  char sintomas[200]; //sintomas del paciente
} tipoPersona;

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir");
}

int comparar_pacientes(void *a, void *b) //funcion para determinar orden de prioridad y hora de llegada
{
  tipoPersona *pacienteA = (tipoPersona *)a; //puntero a paciente 
  tipoPersona *pacienteB = (tipoPersona *)b; //puntero a el paciente a comparar

  if (pacienteA->prioridad < pacienteB->prioridad) return 1; //se compara la prioridad del paciente (considerar que la prioridad más alta, tiene el valor más bajo numericamente)
  if ((pacienteA->prioridad == pacienteB->prioridad) && (pacienteA->horaLlegada < pacienteB->horaLlegada)) return 1; // si las prioridades son iguales, se compara la hora de llegada
  if ((pacienteA->prioridad == pacienteB->prioridad) && (pacienteA->horaLlegada == pacienteB->horaLlegada) && (pacienteA->minutos < pacienteB->minutos)) return 1; // si las prioridades y las horas de llegada son iguales, se compara los minutos de llegada
  return 0;
}

void registrar_paciente(List *pacientes) { //funcion para resgitrar pacientes

  printf("Registrar nuevo paciente\n");
  tipoPersona *nuevoPaciente = (tipoPersona *)malloc(sizeof(tipoPersona)); //Creamos el nuevo paciente

  printf("Ingrese el nombre del paciente: ");
  getchar(); // Limpiar el buffer de entrada
  scanf("%[^\n]", nuevoPaciente->nombre); //Leemos el nombre del paciente
  for(int i = 0; i < strlen(nuevoPaciente->nombre); i++){ //recorremos cada caracter del nombre ingresado
    if((!isalpha(nuevoPaciente->nombre[i])) && (nuevoPaciente->nombre[i] != ' ')){ //verificamos que el nombre solo tenga letras o espacios
      printf("El nombre ingresado no es válido, intente nuevamente.\n"); //si no es válido, se vuelve a pedir el nombre
      free(nuevoPaciente); //liberamos la memoria
      return; //retornamos
    }
  }
  //si es nombre es válido, se continúa con el proceso

  getchar(); // Limpiar el buffer de entrada
  printf("Ingrese los síntomas del paciente: ");
  scanf("%[^\n]", nuevoPaciente->sintomas); //Leemos los síntomas y lo almacenamos en el paciente

  int edad; //variable para almacenar la edad del paciente
  printf("Ingrese la edad del paciente: ");
  if (scanf("%d", &edad) != 1) { // Verificamos si la entrada para la edad no es un número
      printf("Edad ingresada no es numérica\n");
      // En caso de que no sea un número:
      free(nuevoPaciente);  //Liberamos la memoria asignada
      return; // Salimos de la función sin agregar el paciente a la lista
  }
  //En caso de que la edad sea válida, continuamos
  nuevoPaciente->edad = edad; // Asignamos la edad del paciente


  printf("Ingrese la hora de llegada del paciente (No ingrese minutos. No ingrese decimales): ");
  scanf("%d", &nuevoPaciente->horaLlegada); //Leemos la hora de llegada del paciente

  if (nuevoPaciente->horaLlegada > 23) { //Se verifica que la hora sea válida
    printf("Hora ingresada no es valida\n");
    free(nuevoPaciente); //Liberamos memoria, ya que la hora no es válida
    return; //Retornamos
  }

  else { //En caso de que la hora sea válida
    printf("Ingrese los minutos de llegada del paciente: ");
    scanf("%d", &nuevoPaciente->minutos); //Leemos los minutos de llegada del paciente

    if (nuevoPaciente->minutos > 59) { //Se verifica que los minutos sean válidos
      printf("Minutos ingresados no son validos\n");
      free(nuevoPaciente); //Liberamos memoria, ya que los minutos no son válidos
      return; //retornamos
    } 
    else { //Si todos los datos ingresados son válidos, se agrega el paciente a la lista
      nuevoPaciente->prioridad = 3; //se asigna la prioridad 3 al paciente ("BAJA")
      printf("Paciente registrado con éxito\n");
      list_sortedInsert(pacientes, nuevoPaciente, comparar_pacientes); //ingresamos el paciente a la lista con nuestro criterio de ordenameinto
    }
  }
}

void asignar_prioridad(List *pacientes) { //función para asignar prioridad a los pacientes
  char nombrePaciente[50]; //variable para almacenar el nombre del paciente
  int prioridad; //variable para almacerar la prioridad del paciente
  printf("Ingrese el nombre del paciente: ");
  getchar(); // Limpiar el buffer de entrada
  scanf("%[^\n]", nombrePaciente); //Leemos el nombre del paciente

  bool encontrado = false; //variable para verificar si el paciente fue encontrado
  tipoPersona *paciente = (tipoPersona *)list_first(pacientes); //puntero a primer paciente
  tipoPersona *pacienteEncontrado = NULL; //puntero que se usará para almacenar el paciente encontrado

  while (paciente != NULL) { //recorremos la lista
    if (strcmp(paciente->nombre, nombrePaciente) == 0) { //si el nombre del paciente es igual al ingresado
      encontrado = true; //se marca que el paciente fue encontrado
      printf("Ingrese la nueva prioridad del paciente: \n");
      printf("1.- Alta\n");
      printf("2.- Media\n");
      printf("3.- Baja\n");
      scanf("%d", &prioridad); //almacenamos la nueva prioridad del paciente
      if(prioridad < 1 || prioridad > 3) //verificamos si la prioridad es válida
      {
        printf("Prioridad ingresada no es válida\n");
        return; //si no es válida, retornamos
      }
      else //en caso de que sea válida
      {
        paciente->prioridad = prioridad; //se asigna la nueva prioridad al paciente
        pacienteEncontrado = paciente; //se almacena el paciente encontrado
        list_popCurrent(pacientes); //se elimina el paciente de la lista
        list_sortedInsert(pacientes, pacienteEncontrado, comparar_pacientes); //se ingresa el paciente de nuevo a la lista, pero esta vez de forma ordenada
        printf("Prioridad asignada con éxito\n");
        return; //retornamos
      }
    }
    paciente = (tipoPersona *)list_next(pacientes); //avanzamos al siguiente paciente
  }

  if (!encontrado) { //si el paciente no fue encontrado
    printf("Paciente no encontrado.\n");
  }
}


void mostrar_lista_pacientes(List *pacientes) { //función para mostrar la lista de pacientes de manera ordenada (prioridad y hora de llegada)
  if (list_first(pacientes) == NULL) { //si la lista esta vacia
    printf("No hay pacientes en espera.\n");
    return; //retornamos
  }  

  //En caso de que no esté vacia, continuamos
  printf("Pacientes en espera: \n\n");

  tipoPersona *paciente = (tipoPersona *)list_first(pacientes); //puntero a primer paciente
  while (paciente != NULL) { //recorremos la lista
    //mostramos datos del paciente
    printf("Nombre: %s\n", paciente->nombre);
    printf("Edad: %d\n", paciente->edad);
    printf("Síntomas: %s\n", paciente->sintomas);
    printf("Prioridad: ");
    if(paciente->prioridad == 1) printf("ALTA\n");
    if(paciente->prioridad == 2) printf("MEDIA\n");
    if(paciente->prioridad == 3) printf("BAJA\n");
    if(paciente->horaLlegada < 10 && paciente->minutos < 10)
      printf("Hora de llegada: 0%d:0%d\n", paciente->horaLlegada, paciente->minutos);
    else if (paciente->horaLlegada < 10 && paciente->minutos > 10)
      printf("Hora de llegada: 0%d:%d\n", paciente->horaLlegada, paciente->minutos);
    else if (paciente->horaLlegada > 10 && paciente->minutos < 10)
      printf("Hora de llegada: %d:0%d\n", paciente->horaLlegada, paciente->minutos);
    else
      printf("Hora de llegada: %d:%d\n", paciente->horaLlegada, paciente->minutos);
    printf("------------------------------------\n");

    paciente = (tipoPersona *)list_next(pacientes); //avanzamos al siguiente paciente
    }
}

void atender_paciente(List *pacientes) //función para atender al paciente segun criterio de ordenamiento
{
  if (list_first(pacientes) == NULL) //Si la lista esta vacía 
    printf("No hay pacientes en espera.\n");

  else //si la lista no está vacía
  {
    tipoPersona *paciente = (tipoPersona *)list_first(pacientes); //puntero a primer paciente
    //mostramos datos del paciente
    printf("Atendiendo al paciente: %s\n", paciente->nombre);


    
    list_popFront(pacientes); //eliminamos al paciente de la lista
  }
}

void mostrar_pacientes_por_prioridad(List *pacientes) //función para mostrar pacientes por prioridad solicitada
{
  int prioridad; //variable para guardar la prioridad a ingresar
  printf("Ingrese prioridad deseada: \n");
  printf("1.- Alta\n");
  printf("2.- Media\n");
  printf("3.- Baja\n");
  scanf("%d", &prioridad); //almacenamos la prioridad ingresada
  if(prioridad < 1 || prioridad > 3) //verificamos si es valida
  {
    printf("Prioridad ingresada no es válida\n");
    return; //si no es valida retornamos
  }
  //si es valida, continuamos el proceso
  printf("Lista de pacientes con prioridad: ");
  if(prioridad == 1) printf("ALTA\n");
  if(prioridad == 2) printf("MEDIA\n");
  if(prioridad == 3) printf("BAJA\n");
  
  bool hay = false; //variable para verificar si hay pacientes con la prioridad ingresada
  tipoPersona *paciente = (tipoPersona *)list_first(pacientes); //punteroa a primer paciente

  while(paciente != NULL) //recorremos la lista
    {
      if(prioridad == paciente->prioridad) //si la prioridad del paciente es igual a la ingresada
      {
        //mostramos sus datos
        printf("Nombre: %s\n", paciente->nombre);
        printf("Edad: %d\n", paciente->edad);
        printf("Síntomas: %s\n", paciente->sintomas);
        if(paciente->horaLlegada < 10 && paciente->minutos < 10)
          printf("Hora de llegada: 0%d:0%d\n", paciente->horaLlegada, paciente->minutos);
        else if (paciente->horaLlegada < 10 && paciente->minutos > 10)
          printf("Hora de llegada: 0%d:%d\n", paciente->horaLlegada, paciente->minutos);
        else if (paciente->horaLlegada > 10 && paciente->minutos < 10)
          printf("Hora de llegada: %d:0%d\n", paciente->horaLlegada, paciente->minutos);
        else
          printf("Hora de llegada: %d:%d\n", paciente->horaLlegada, paciente->minutos);
        printf("------------------------------------\n");
        hay = true; //se marca que hay pacientes con la prioridad ingresada
      }
      paciente = (tipoPersona *)list_next(pacientes); //avanzamos al siguiente paciente
    }
  if(!hay) { //si no hay pacientes con la prioridad ingresada
    printf("No hay pacientes con prioridad ");
    if(prioridad == 1) printf("ALTA\n");
    if(prioridad == 2) printf("MEDIA\n");
    if(prioridad == 3) printf("BAJA\n");
  }
}

int main() {
  char opcion;
  List *pacientes = list_create(); //creamos TDA a utilizar

  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior
    switch (opcion) {
    case '1':
      registrar_paciente(pacientes);
      break;
    case '2':
      asignar_prioridad(pacientes);
      break;
    case '3':
      mostrar_lista_pacientes(pacientes);
      break;
    case '4':
      atender_paciente(pacientes);
      break;
    case '5':
      mostrar_pacientes_por_prioridad(pacientes);
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(pacientes);
  free(pacientes);

  return 0;
}
