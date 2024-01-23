#include "main.h"

void crear_directorio_entradas(){
  char *Ruta = RUTA_DIRECTORIO_ENTRADAS;
  struct stat st = {0};
  if (stat(Ruta, &st) != 0) {
    mkdir(Ruta, 0744);
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
  return cadena;
}


int normalizar_archivo(char *nombre_autor, char *nombre_archivo) {
  char linea[BUFF_SIZE], ruta_archivo[BUFF_SIZE], resultado[BUFF_SIZE], entrada[BUFF_SIZE];
  snprintf(entrada, sizeof(entrada), "%s/%s%s", RUTA_DIRECTORIO_ENTRADAS, nombre_autor, ".txt");

  snprintf(ruta_archivo, sizeof(ruta_archivo), "%s/%s/%s", RUTA_DIRECTORIO_TRABAJO, nombre_autor, nombre_archivo);
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


void crear_archivo_autor( char* nombre_autor){
  char entrada[BUFF_SIZE];
  snprintf(entrada, sizeof(entrada), "%s/%s%s", RUTA_DIRECTORIO_ENTRADAS, nombre_autor, ".txt");
  FILE *archivo_entrada = fopen(entrada, "w");
  fprintf(archivo_entrada, "%s", "");
  fclose(archivo_entrada);
}

int crear_entrada_autor( char *nombre_autor ){
  char ruta_lista_archivos[BUFF_SIZE], nombre_archivo[BUFF_SIZE];
  snprintf(ruta_lista_archivos, sizeof(ruta_lista_archivos), "%s/%s/%s", RUTA_DIRECTORIO_TRABAJO, nombre_autor, ".list");
  FILE *fp = fopen(ruta_lista_archivos, "r");
  crear_archivo_autor(nombre_autor);
  if (fp == NULL){
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
  snprintf(comando, sizeof(comando), "ls %s/%s > %s/%s/%s", RUTA_DIRECTORIO_TRABAJO, nombre_autor, RUTA_DIRECTORIO_TRABAJO, nombre_autor, ".list");
  system(comando);
  return 0;
}

void run_python_script(char *nombre_autor){
  char comando[BUFF_SIZE];
  snprintf(comando, sizeof(comando), "python %s %s", RUTA_SCRIPT_PYTHON, nombre_autor);
  system(comando);
}
