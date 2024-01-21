#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <sys/types.h>
#define BUFF_SIZE 512
#define RUTA_DIRECTORIO_TRABAJO "./Textos"
#define RUTA_DIRECTORIO_ENTRADAS "./Entradas"

void crear_directorio_entradas(){
  struct stat st = {0};
  if (stat(RUTA_DIRECTORIO_ENTRADAS, &st) == -1) {
    mkdir(RUTA_DIRECTORIO_ENTRADAS, 0744);
  }else{
    remove(RUTA_DIRECTORIO_ENTRADAS);
    mkdir(RUTA_DIRECTORIO_ENTRADAS, 0744);
  }
}

char *normalizar_cadena(char *cadena) {
  int i = 0, j = 0;
  char siguiente, anterior, actual;
  for (i = 0; cadena[i] != '.'; i++) {
    cadena[j] = tolower(cadena[i]);

    siguiente = cadena[j+1];
    anterior = cadena[j-1];
    actual = cadena[j];

    if (( actual == '\n' ) && ((anterior >= 'a' && anterior <= 'z') || (siguiente >= 'a' && siguiente <= 'z'))) {
      cadena[j] = ' ';
      j++;
    }
    if( (actual >= 'a' && actual <= 'z') || actual == ' '){
      j++;
    }
    
  }
  cadena[j] = '\n';
  cadena[j+1] = '\0';
  printf("%s",cadena);
  return cadena;
}


int normalizar_archivo(char *nombre_autor, char *nombre_archivo) {
  char linea[BUFF_SIZE], ruta_archivo[BUFF_SIZE], resultado[BUFF_SIZE], entrada[BUFF_SIZE];

  snprintf(ruta_archivo, sizeof(ruta_archivo), "%s/%s/%s", RUTA_DIRECTORIO_TRABAJO, nombre_autor, nombre_archivo);
  snprintf(entrada, sizeof(entrada), "%s/%s%s", RUTA_DIRECTORIO_ENTRADAS, nombre_autor, ".txt");
  ruta_archivo[strlen(ruta_archivo) - 1] = '\0';
  entrada[strlen(entrada)] = '\0';
  resultado[0] = '\0';

  FILE *escrito_autor = fopen(ruta_archivo, "r");
  FILE *archivo_entrada = fopen(entrada, "a");

  if (escrito_autor == NULL || archivo_entrada == NULL){
    perror("Error");
    return 1;
  }

  while (fgets(linea, sizeof(linea), escrito_autor) != NULL) {
    char *punto = strchr(linea, '.');

    if (punto != NULL) {
      strncat(resultado, linea, punto - linea + 1);
      fprintf(archivo_entrada, "%s", normalizar_cadena(resultado));
      resultado[0] = '\0';
    } else {
      strcat(resultado, linea);
    }
  }

  fclose(archivo_entrada);
  fclose(escrito_autor);
  return 0;
}

int crear_lista_archivos( char *nombre_autor){
  char ruta_lista_archivos[BUFF_SIZE], nombre_archivo[BUFF_SIZE];
  printf("Limpiando y unificando archivos de %s\n\n", nombre_autor);
  snprintf(ruta_lista_archivos, sizeof(ruta_lista_archivos), "%s/%s/%s", RUTA_DIRECTORIO_TRABAJO, nombre_autor, ".list");
  FILE *fp = fopen(ruta_lista_archivos, "r");

  if (fp == NULL){
    printf("Error al abrir el archivo %s\n", ruta_lista_archivos);
    return 1;
  }

  while(fgets(nombre_archivo, sizeof(nombre_archivo), fp) != NULL ) {
    normalizar_archivo(nombre_autor, nombre_archivo);
  }
  fclose(fp);
  return 0;
}

int crear_listado_archivos(char* nombre_autor){
  char comando[BUFF_SIZE];
  struct stat st = {0};
  // Verificar si existe el autor
  snprintf(comando, sizeof(comando), "%s/%s", RUTA_DIRECTORIO_TRABAJO, nombre_autor);
  if (stat(comando, &st) == -1) {
    return 1;
  }

  // Si existe, crear el archivo temporal
  printf("Creando archivo temporal de %s\n", nombre_autor);
  snprintf(comando, sizeof(comando), "ls %s/%s > %s/%s/%s", RUTA_DIRECTORIO_TRABAJO, nombre_autor, RUTA_DIRECTORIO_TRABAJO, nombre_autor, ".list");
  system(comando);
  return 0;
}


int main(int argc, char** argv){
  if (argc != 2){
    printf("Por favor usar solo un argumento\n");
    return 1;
  }
  char *nombre_autor = argv[1];

  int resultado = crear_listado_archivos(nombre_autor);
  if (resultado != 0){
    perror("Error");
    return resultado;
  }

  crear_directorio_entradas();
  resultado = crear_lista_archivos(nombre_autor);
  if (resultado != 0){
    printf("Ha ocurrido un error procesando el archivo de el autor\n");
    return resultado;
  }
  return 0;
}
