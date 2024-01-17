#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_SIZE 255
#define WORK_DIR "./Textos"

void sanitize_file(char *nombre_autor, char *nombre_archivo){
  char line[BUFF_SIZE], file[BUFF_SIZE];
  snprintf(file, sizeof(file), "%s/%s/%s", WORK_DIR, nombre_autor, nombre_archivo);
  file[strlen(file)-1] = '\0';

  FILE *fp = fopen(file, "r");

  while(fgets(line, sizeof(line), fp) != NULL ) {
    printf("%s", line);
  }
}

int process_file_list( char *nombre_autor){
  char file_list[BUFF_SIZE], file[BUFF_SIZE];
  printf("Limpiando y unificando archivos de %s\n", nombre_autor);
  snprintf(file_list, sizeof(file_list), "%s/%s/%s", WORK_DIR, nombre_autor, ".list");
  FILE *fp = fopen(file_list, "r");

  if (fp == NULL){
    printf("Error al abrir el archivo %s\n", file_list);
    return 1;
  }

  while(fgets(file, sizeof(file), fp) != NULL ) {
    printf("%s", file);
    sanitize_file(nombre_autor, file);
  }
  return 0;
}

int create_file_list(char* nombre_autor){
  char command[BUFF_SIZE];
  printf("Creando archivo temporal de %s\n", nombre_autor);
  snprintf(command, sizeof(command), "ls %s/%s > %s/%s/%s", WORK_DIR, nombre_autor, WORK_DIR, nombre_autor, ".list");
  return system(command);
}


int main(int argc, char** argv){
  if (argc != 2){
    printf("Por favor usar solo un argumento\n");
    return 1;
  }
  char *nombre_autor = argv[1];

  int result = create_file_list(nombre_autor);
  if (result != 0){
    printf("Ha ocurrido un error creando el archivo temporal\n");
    return result;
  }

  result = process_file_list(nombre_autor);
  if (result != 0){
    printf("Ha ocurrido un error procesando el archivo de el autor\n");
    return result;
  }
  return 0;
}
