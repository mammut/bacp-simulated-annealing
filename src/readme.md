# BACP con Simulated Annealing

El siguiente documento explica el proceso de compilación y ejecución del solver usando Greedy + Simulated Annealing.

El programa fue probado en una maquina virtual con Fedora 21 de 64 bits, 512 MB de RAM y un procesador Intel Core i5 2.5 GHz.

### Compilación

Para compilar basta ejecutar el siguiente comando:

```bash
$ make
```

para limpiar el proyecto:

```bash
$ make clean
```

#####Nota*
Si se desea compilar en OS X, comentar linea 5 del archivo makefile y descomentar linea 4.

El programa utiliza la libreria **argp** para parsear los parámetros, esta libreria viene por defecto en los sitememas Unix, además la compilación fue probada exotisamente en los computadores de la universidad por ssh.
### Ejecución

Para ejecutar el programa se debe indicar al menos el archivo de entrada como argumento. Se tienen las siguientes opciones:

- `-a, --alpha=0.9`           Alpha: rapidez de decaimiento de temperatura
- `-i, --iter=100`            Numero de iteraciones en cada temperatura del algoritmo SA
- `-r, --red-output`          Salida reducida
- `-t, --t-min=0.00001`       Temperatura mínima de detención del algoritmo SA
- `-T, --t-init=1.0`          Temperatura inicial del algoritmo SA
- `-?, --help`                Mostrar esta lista de ayuda
- `    --usage `              Dar un mensaje de uso pequeño
- `-V, --version`             Imprimir la versión del programa

#### Ejemplos

```bash
./bacp --iter=1000 -T 1.0 -t 0.0001 --alpha=0.85 instancias/informatica/bacp12.txt
./bacp --iter=300 -T 1.0 -t 0.001 --alpha=0.9 -r instancias/informatica/bacp8.txt
```

#### Sobre el código
| Archivo                        | Código | Comentarios | Raw |
|--------------------------------|--------|-------------|-----|
| includes/bacp.h                | 23     | 4           | 29  |
| bacp.c                         | 81     | 48          | 150 |
| includes/simulated-annealing.h | 13     | 0           | 16  |
| simulated-annealing.c          | 110    | 69          | 213 |
| includes/main.h                | 10     | 2           | 13  |
| main.c                         | 79     | 17          | 110 |

 - Total código: 316
 - Total comentario: 140
 - Total raw: 531
 - Porcentaje comentarios: 30.701754
