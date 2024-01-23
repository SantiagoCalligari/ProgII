"""
Documentacion para las funciones en predictor.py
"""


from collections import defaultdict


def crear_diccionario(nombre_autor: str) -> defaultdict:
    """
    Crea un diccionario con las palabras anteriores y
    siguientes a cada palabra en el archivo del autor dado.
    Args:
        nombre_autor (str): Nombre del autor del archivo a analizar.
    Returns:
        defaultdict: Diccionario con las palabras que siguen a cada palabra.
    """
    pass


def calcular_posible(
    posibles_siguientes: defaultdict, posibles_anteriores: defaultdict
) -> str:
    """
    toma dos diccionarios, los fusiona y devuelve la palabra
    la palabra que más veces aparece en ambos diccionarios.
    Args:
        posibles_siguientes (defaultdict): Diccionario con las palabras que siguen a cada palabra.
        posibles_anteriores (defaultdict): Diccionario con las palabras que anteceden a cada palabra.
    Returns:
        str: Palabra más probable de seguir a la palabra anterior.
    """
    pass


def escribir_archivo(nombre_autor: str, linea: str, borrar: bool) -> None:
    """
    Toma un nombre de autor, una línea y un booleano que indica si se debe
    eliminar el archivo antes de escribir.
    luego escribe la línea en el archivo correspondiente al autor.
    Args:
        nombre_autor (str): Nombre del autor del archivo a analizar.
        linea (str): Linea a escribir en el archivo.
        borrar (bool): Si se debe borrar el archivo antes de escribir.
    """
    pass


def predecir(nombre_autor: str, diccionario: defaultdict) -> None:
    """
    Toma un nombre de autor y un diccionario de palabras, abre el archivo de frases
    y luego predice cada palabra que falta en cada frase.
    finalmente llama a escribir archivo.

    Args:
        nombre_autor (str): Nombre del autor del archivo a analizar.
        diccionario (defaultdict): Diccionario con las palabras que siguen a cada palabra.
    """
    pass
