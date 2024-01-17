#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <sys/types.h>
#define BUFF_SIZE 511
#define WORK_DIR "./Textos"
#define ENTRY_DIR "./Entradas"

void create_entry_folder(){
  struct stat st = {0};
  if (stat(ENTRY_DIR, &st) == -1) {
    mkdir(ENTRY_DIR, 0744);
  }
}


char *sanitize_string(char *str) {
  int i = 0;
  int j = 0;
  while (str[i]) {
    if (str[i] != '\n') {
      str[i] = tolower(str[i]);
      if ((str[i] >= 'a' && str[i] <= 'z') || str[i] == ' ' || str[i] == '.') {
        str[j] = str[i];
        j++;
      }
    }
    i++;
  }
  str[j] = '\0';
  return str;
}



void sanitize_file(char *nombre_autor, char *nombre_archivo) {
  char line[BUFF_SIZE], file[BUFF_SIZE];
  snprintf(file, sizeof(file), "%s/%s/%s", WORK_DIR, nombre_autor, nombre_archivo);
  file[strlen(file) - 1] = '\0';

  FILE *fp = fopen(file, "r");
  if (fp == NULL) {
    perror("Error al abrir el archivo");
    return;
  }

  char result[BUFF_SIZE];

  while (fgets(line, sizeof(line), fp) != NULL) {
    char *punto = strchr(line, '.');

    if (punto != NULL) {
      strncat(result, line, punto - line + 1);
      printf("%s\n", sanitize_string(result));
      result[0] = '\0';
    } else {
      strcat(result, line);
    }
  }

  fclose(fp);
}

int process_file_list( char *nombre_autor){
  char file_list[BUFF_SIZE], file[BUFF_SIZE];
  printf("Limpiando y unificando archivos de %s\n\n", nombre_autor);
  snprintf(file_list, sizeof(file_list), "%s/%s/%s", WORK_DIR, nombre_autor, ".list");
  FILE *fp = fopen(file_list, "r");

  if (fp == NULL){
    printf("Error al abrir el archivo %s\n", file_list);
    return 1;
  }

  while(fgets(file, sizeof(file), fp) != NULL ) {
    sanitize_file(nombre_autor, file);
  }
  fclose(fp);
  return 0;
}

int create_file_list(char* nombre_autor){
  char command[BUFF_SIZE];
  struct stat st = {0};
  // Verificar si existe el autor
  snprintf(command, sizeof(command), "%s/%s", WORK_DIR, nombre_autor);
  if (stat(command, &st) == -1) {
    return 1;
  }

  // Si existe, crear el archivo temporal
  printf("Creando archivo temporal de %s\n", nombre_autor);
  snprintf(command, sizeof(command), "ls %s/%s > %s/%s/%s", WORK_DIR, nombre_autor, WORK_DIR, nombre_autor, ".list");
  system(command);
  return 0;
}


int main(int argc, char** argv){
  if (argc != 2){
    printf("Por favor usar solo un argumento\n");
    return 1;
  }
  char *nombre_autor = argv[1];

  int result = create_file_list(nombre_autor);
  if (result != 0){
    perror("Error");
    return result;
  }

  create_entry_folder();
  result = process_file_list(nombre_autor);
  if (result != 0){
    printf("Ha ocurrido un error procesando el archivo de el autor\n");
    return result;
  }
  return 0;
}
