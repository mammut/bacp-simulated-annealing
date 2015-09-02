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

#### Ejemplo

```bash
./bacp --iter=1000 -T 1.0 -t 0.0001 --alpha=0.85 inst/informatica/bacp12.txt
```
