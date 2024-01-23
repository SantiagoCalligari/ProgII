#include "main.h"
int main(int argc, char** argv){
  if (argc != 2){
    printf("Por favor usar solo un argumento\n");
    return 1;
  }
  char *nombre_autor = argv[1];

  printf("Creando archivo temporal de %s\n", nombre_autor);
  int resultado = crear_listado_archivos(nombre_autor);
  if (resultado != 0){
    perror("Error");
    return resultado;
  }

  crear_directorio_entradas();
  printf("Limpiando y unificando archivos de %s\n\n", nombre_autor);
  resultado = crear_entrada_autor(nombre_autor);
  if (resultado != 0){
    perror("Error");
    return resultado;
  }

  run_python_script(nombre_autor);
  return 0;
}
