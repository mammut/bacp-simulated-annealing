# BACP con Simulated Annealing

El siguiente documento explica el proceso de compilación y ejecución del solver usando Simulated Annealing.

El programa fue probado en una maquina virtual con Fedora 21 de 64 bits, 512 MB de RAM y un procesador Intel Core i5 2.5 GHz.

### Compilación

Para compilar basta ejecutar el siguiente comando:

```bash
make
```

para limpiar el proyecto:

```bash
make clean
```

### Ejecución

Para ejecutar el programa se debe indicar al menos el archivo de entrada con el flag `-f`. Se tienen los siguientes argumentos:

- `-f bacp12.txt` *file*: Path al archivo de entrada con el formato especificado
- `-T 1.0` *T*:  Temperatura inicial
- `-t 0.0001` *t*: Temperatura final
- `-a 0.9`: *alpha*: Velocidad en que la temperatura *T* disminuye a *t*
- `-i 500` *Iter*: Número máximo de repeticiones para una temperatura fija *T*

#### Ejemplo

```bash
./bacp -f bacp12.txt -i 1000 -T 1.0 -t 0.0001 -a 0.85
```
