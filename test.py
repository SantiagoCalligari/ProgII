import pytest
import os
from main import *


def test_escribir_archivo():
    escribir_archivo("test", "test", True)
    with open("Salidas/test.txt", "r") as archivo:
        assert archivo.readline() == "test\n"


def test_calcular_posible():
    assert calcular_posible({"test": 4, "pruebas": 5}, {"test": 2, "hola": 3}) == "test"


def test_crear_diccionario():
    nombre_autor = "Hayley_Williams"
    diccionario = crear_diccionario(nombre_autor)
    assert diccionario  # Verifica que el diccionario no esté vacío


# Prueba la función de predicción con diferentes nombres de autor
def test_predecir():
    nombre_autor = "Hayley_Williams"
    diccionario = crear_diccionario(nombre_autor)
    predecir(nombre_autor, diccionario)

    # Verifica que se haya creado el archivo de salida esperado
    ruta_salida = f"Salidas/{nombre_autor}.txt"
    with open(ruta_salida, "r") as archivo_salida:
        contenido_salida = archivo_salida.read()

    assert contenido_salida
