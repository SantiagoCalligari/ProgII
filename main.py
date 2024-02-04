from collections import defaultdict
import os
import sys


def crear_diccionario(nombre_autor):
    ruta_archivo = "Entradas/" + nombre_autor + ".txt"
    # La función lambda crea diccionarios anidados con valores predeterminados de 0.
    diccionario = defaultdict(
        lambda: {"siguientes": defaultdict(int), "anteriores": defaultdict(int)}
    )
    with open(ruta_archivo, "r") as archivo:
        for linea in archivo:
            palabras = linea.split()

            for palabra_anterior, palabra_actual in zip(
                [None] + palabras[:-1], palabras
            ):
                diccionario[palabra_actual]["anteriores"][palabra_anterior] += 1
                diccionario[palabra_anterior]["siguientes"][palabra_actual] += 1

            diccionario[palabras[-1]]["siguientes"][None] += 1
    return diccionario


def calcular_posible(posibles_siguientes, posibles_anteriores):
    resultado = defaultdict(int)
    for diccionario in [posibles_siguientes, posibles_anteriores]:
        for clave, valor in diccionario.items():
            resultado[clave] += valor
    if None in resultado:
        del resultado[None]
    return max(resultado, key=resultado.get)


def escribir_archivo(nombre_autor, linea, borrar):
    if not os.path.exists("Salidas"):
        os.mkdir("Salidas")

    file_path = "Salidas/" + nombre_autor + ".txt"

    if os.path.exists(file_path) and borrar:
        with open(file_path, "w") as archivo:
            archivo.write(linea + "\n")
    else:
        with open(file_path, "a") as archivo:
            archivo.write(linea + "\n")


def predecir(nombre_autor, diccionario):
    palabras = []
    ruta = "Frases/" + nombre_autor + ".txt"
    borrar = True

    with open(ruta, "r") as archivo:
        for linea in archivo:
            palabras = linea.split()

            while "_" in palabras:
                indice_guion = palabras.index("_")

                anterior = None
                if indice_guion != 0:
                    anterior = palabras[indice_guion - 1]
                siguiente = None
                if indice_guion != len(palabras) - 1:
                    siguiente = palabras[indice_guion + 1]

                posibles_por_siguiente = diccionario[siguiente]["anteriores"]
                posibles_por_anterior = diccionario[anterior]["siguientes"]

                palabras[indice_guion] = calcular_posible(
                    posibles_por_siguiente, posibles_por_anterior
                )

            escribir_archivo(nombre_autor, " ".join(palabras), borrar)
            borrar = False


def main():
    if len(sys.argv) != 2:
        print("Uso: python predictor.py <nombre_autor>")
        sys.exit(1)

    nombre_autor = sys.argv[1]
    diccionario = crear_diccionario(nombre_autor)
    predecir(nombre_autor, diccionario)


main()
