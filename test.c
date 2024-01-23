#include "main.h"
#include <assert.h>

// Función para probar la creación del directorio de entradas
void test_crear_directorio_entradas() {
  crear_directorio_entradas();
  struct stat st = {0};
  assert (stat(RUTA_DIRECTORIO_ENTRADAS, &st) == 0); // Verificar que el directorio se creó exitosamente
}

// Función para probar la normalización de cadenas
void test_normalizar_cadena() {
    char entrada[] = "(¬_¬)~*Nyaa~! Hoy el sol está radiante como mi espíritu kawaii~ OwO (>_<) ¿No sientes esa energía positiva en el aire? 7///7 Es un día perfecto para disfrutar de anime y snacks deliciosos!(¬°-°)¬ ¿Qué tal si nos perdemos juntos en el mundo otaku? (^_^)o  Kawaii desu ne~!.\n";
    char esperado[] = "nyaa hoy el sol est radiante como mi espritu kawaii owo  no sientes esa energa positiva en el aire  es un da perfecto para disfrutar de anime y snacks deliciosos qu tal si nos perdemos juntos en el mundo otaku o  kawaii desu ne\n";
    assert(strcmp(normalizar_cadena(entrada), esperado) == 0); // Verificar que la normalización funciona correctamente
}

// Función para probar la creación de una entrada de autor
void test_crear_entrada_autor() {
   int resultado = crear_entrada_autor("Fito_Paez");
   assert(resultado == 0); // Verificar que la entrada de autor se creó sin errores

   // Verificar existencia y no vacuidad del archivo de entrada
   FILE *archivo_entrada = fopen("Entradas/Fito_Paez.txt", "r");
   assert(archivo_entrada != NULL);
   fseek(archivo_entrada, 0, SEEK_END);
   assert(ftell(archivo_entrada) > 0);
   fclose(archivo_entrada);

   // Verificar existencia del archivo de lista
   FILE *archivo_lista = fopen("Textos/Fito_Paez/.list", "r");
   assert(archivo_lista != NULL);
   fclose(archivo_lista);
}

// Función para probar la creación de un archivo de autor vacío
void test_crear_archivo_autor() {
    crear_archivo_autor("Fito_Paez");
    FILE *archivo_prueba = fopen("Entradas/Fito_Paez.txt", "r");
    fseek(archivo_prueba, 0, SEEK_END);
    assert(ftell(archivo_prueba) == 0); // Verificar que el archivo de autor está vacío
    fclose(archivo_prueba);
}

int main() {
    test_crear_directorio_entradas();
    test_crear_entrada_autor();
    test_normalizar_cadena();
    test_crear_archivo_autor();

    printf("Todas las pruebas pasaron con éxito.\n");

    return 0;
}

