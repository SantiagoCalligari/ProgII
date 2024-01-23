#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <sys/types.h>
#define BUFF_SIZE 512
#define RUTA_DIRECTORIO_TRABAJO "Textos"
#define RUTA_DIRECTORIO_ENTRADAS "Entradas"
#define RUTA_SCRIPT_PYTHON "main.py"

int crear_listado_archivos(char* nombre_autor);
// crear_listado_archivos toma un nombre de autor y se
// fija si existe el autro dentro de RUTA_DIRECTORIO_TRABAJO
// si existe escribe el nombre de todos los archivos
// dentro del directorio del aturo en un archivo
// para que luego se pueda leer y crear las entradas.

void crear_directorio_entradas();
// Al llamar a esta función se creará el directorio
// Entradas en el directorio de trabajo, utilizando
// la constante RUTA_DIRECTORIO_TRABAJO.

int crear_entrada_autor(char *nombre_autor);
// crear_nombre_autor toma un nombre de autor
// y llama a normalizar archivo del autor dado.

int normalizar_archivo(char *nombre_autor, char *nombre_archivo);
// normalizar_archivo toma un nombre de autor, 
// un nombre de archivo y una entrada para luego
// llamar a normalizar cadena y luego
// escribir la cadena normalizada dentro de un
// archivo con el nombre del autor.
// devuelve un int status para saber el estado de la función.


void crear_archivo_autor( char* nombre_autor);
// crear_archivo_autor toma una nombre_autor y
// crea un archivo nuevo, vacio del autor dado.

char *normalizar_cadena(char* cadena);
// Esta función recibe una cadena de caracteres
// y devuelve la misma cadena menos los caracteres 
// especiales, tambien devuelve los espacios.

void run_python_script(char *nombre_autor);
// Toma un nombre de autor y corre el script de
// python con nombre PYTHON_SCRIPT_NAME y le pasa
// como arghumento el nombre del autor.
