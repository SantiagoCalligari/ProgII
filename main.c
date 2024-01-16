#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_SIZE 255
#define WORK_DIR "./Textos/"


int create_file_list(char* nombre_autor){
  char command[BUFF_SIZE];
  snprintf(command, sizeof(command), "ls %s%s > %s%s/%s", WORK_DIR, nombre_autor, WORK_DIR, nombre_autor, ".list");
  int result = system(command);
  if (result == -1) {
      perror("Error al ejecutar el comando");
  }

  return result;
}


int main(int argc, char** argv){
  if (argc != 2){
    printf("Por favor usar solo un argumento\n");
    return 1;
  }
  create_file_list(argv[1]);
}
