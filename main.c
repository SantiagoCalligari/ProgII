#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_SIZE 255
#define WORK_DIR "./Textos/"

int clean_and_unify_files( char *nombre_autor){
  char file_list[BUFF_SIZE];
  FILE *fp = fopen(file_list, "r");

  snprintf(file_list, sizeof(file_list), "%s%s/%s", WORK_DIR, nombre_autor, ".list");
  printf("Limpiando y unificando archivos de /%s\n", nombre_autor);
  if (fp == NULL){
    printf("Error al abrir el archivo %s\n", file_list);
    return 1;
  }
  char file[BUFF_SIZE];

  while(fgets(file, sizeof(file), fp) != NULL ) {
    printf("%s", file);
  }
  return 1;
}

int create_file_list(char* nombre_autor){
  char command[BUFF_SIZE];
  printf("Procesando %s\n", nombre_autor);
  snprintf(command, sizeof(command), "ls %s%s > %s%s/%s", WORK_DIR, nombre_autor, WORK_DIR, nombre_autor, ".list");
  int result = system(command);

  if ( result != 0){
    printf("Ha ocurrido un error\n");
    return result;
  }
  clean_and_unify_files(nombre_autor);
  return 0;
}


int main(int argc, char** argv){
  if (argc != 2){
    printf("Por favor usar solo un argumento\n");
    return 1;
  }
  create_file_list(argv[1]);
  return 0;
}
