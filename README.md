# Predictor de Texto
<a href="https://www.github.com/santiagoCalligari/ProgII">Enlace Github</a>

## Trabajo de Fin de Curso - Santiago Calligari

---

## Introducción

### Implementación en C

En la fase inicial, el programa recibe el nombre de un artista y verifica su existencia en la carpeta designada por la constante `RUTA_DIRECTORIO_TRABAJO`. En caso de no existir, finaliza con un error. En caso contrario, dentro del directorio del autor, crea un archivo oculto llamado `.list`, que contiene los nombres de todos los archivos en dicho directorio.

Posteriormente, se crea un directorio con el nombre dado por la constante `RUTA_DIRECTORIO_ENTRADAS`. A continuación, el programa recorre y normaliza cada archivo del directorio del autor.

#### Proceso de Normalización de un Archivo

El programa abre el archivo y lo lee hasta encontrar un punto. En ese momento, invoca la función `normalizar_cadena()`, la cual devuelve una cadena normalizada, eliminando cualquier carácter que no esté entre 'a' y 'z'. Cuando se encuentra un salto de línea, se gestiona para dejar un espacio o simplemente nada, dependiendo de la necesidad para evitar la concatenación de dos palabras.

Una vez normalizada la cadena, se guarda en el archivo con el nombre del autor en la ruta dada por `RUTA_DIRECTORIO_ENTRADAS`. Este proceso se repite para todos los archivos del autor.

Finalizada la normalización de todos los archivos del autor, se ejecuta en Python el script especificado por la constante `RUTA_SCRIPT_PYTHON` mediante la función `run_python_script()`.

### Implementación en Python

Cuando se llama a este programa en Python, se proporciona el nombre de un artista sin verificar su existencia, ya que la entrada se crea previamente en C antes de llamar a este programa.

#### Proceso de Entrenamiento

El programa utiliza un diccionario de diccionarios de diccionarios para almacenar información sobre las palabras en las entradas. Cada palabra es una clave que tiene como valor un diccionario con dos conjuntos de claves: `siguientes` y `anteriores`. Estos conjuntos contienen diccionarios con palabras y la cantidad de ocurrencias de las palabras siguientes o anteriores. El formato es el siguiente:
```json
{
  "lorem": {
    "siguientes": {"ipsum": 2, "dolor": 3, "sit": 66},
    "anteriores": {"amet": 5, "forum": 65, "agora": 652}
  },
  "ipsum": {
    "siguientes": {"forum": 2, "dolor": 3, "sit": 66},
    "anteriores": {"lorem": 5, "ipsum": 65, "agora": 652}
  },
  .
  .
  .
}
```

Se utiliza un `DefaultDict` para evitar la repetición de código en caso de que algo no exista en el diccionario.

Durante el recorrido del archivo de entradas, por cada palabra se agrega al diccionario si no existe. También se añade la siguiente palabra al conjunto de `siguientes` y la palabra anterior al conjunto de `anteriores`. Al inicio de una cadena, se agrega `None` en el conjunto de `anteriores`, y lo mismo para `siguientes` cuando la palabra es la última.

Una vez alimentado el diccionario, se pasa a la fase de predicción.

#### Proceso de Predicción

Se abre el archivo especificado en la carpeta de frases y se itera hasta encontrar un '_'. En ese momento, se determinan las palabras anteriores y posteriores al '_', y se obtiene de nuestro diccionario los conjuntos de "siguientes" de la palabra anterior y "anteriores" de la palabra siguiente para enviarlos a la función predictora.

La función predictora realiza una unión de todas las palabras posibles y selecciona aquella que tiene la mayor cantidad de ocurrencias. Cuando se obtiene la predicción, se reemplaza la palabra y se reescribe la línea.
