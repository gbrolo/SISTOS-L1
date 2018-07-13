# SISTOS-L1
Universidad del Valle de Guatemala
Sistemas Operativos, S.10 2018 - Laboratorio 1

## Respuestas

### Ejercicio 1

1. ¿Por  qué  aparecen  números diferentes cada vez? 
Los numeros son distintos cada vez ya que cada vez que se ejecuta el programa, se corre un nuevo proceso
que va a ejecutar el programa de C, es decir, se crea un nuevo proceso de C que va a correr el programa.
El proceso anterior no se guarda, si no que se muere y luego cuando ya se necesita ejecutar de nuevo el programa,
el SO levanta un nuevo proceso que lo ejecute.

2. ¿Por qué aparecen dos números distintos a pesar de que estamos ejecutando un único programa?
Se debe al uso de ```fork()```. Esta llamada al sistema crea nuevos procesos, llamados procesos hijos.
Estos corren concurrentemente con el proceso padre. Siendo procesos distintos, tienen distindo pid.

3. ¿Por qué el primer y el segundo números son iguales?
Esto se debe a que exec reemplaza el segundo proceso con exactamente el primer proceso, lo que cambia es el
codigo que ejecuta, pero usa el mismo proceso y, por ende, tienen el mismo pid.

4. ¿Para  qué  sirve  este proceso?
El proceso es init. La primer cosa que el kernel hace es ejecutar el programa init. Init es el root/parent
de todos los procesos que ejecutan Linux. Se inicia durante el booteo del sistema. Este finaliza una
vez el sistema sea apagado.

#### Archivos de C
[Ejercicio A](./ejercicio1a.c)
[Ejercicio B](./ejercicio1b.c)

### Ejercicio 2

Output del trace:

```
os@debian:~/Documents$ sudo strace ./ejercicio2b f1.txt f2.txt
execve("./ejercicio2b", ["./ejercicio2b", "f1.txt", "f2.txt"], [/* 17 vars */]) = 0
brk(0)                                  = 0x8586000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
mmap2(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb7749000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY)      = 3
fstat64(3, {st_mode=S_IFREG|0644, st_size=64828, ...}) = 0
mmap2(NULL, 64828, PROT_READ, MAP_PRIVATE, 3, 0) = 0xb7739000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/i686/cmov/libc.so.6", O_RDONLY) = 3
read(3, "\177ELF\1\1\1\0\0\0\0\0\0\0\0\0\3\0\3\0\1\0\0\0\0n\1\0004\0\0\0"..., 512) = 512
fstat64(3, {st_mode=S_IFREG|0755, st_size=1327556, ...}) = 0
mmap2(NULL, 1337704, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0xb75f2000
mprotect(0xb7732000, 4096, PROT_NONE)   = 0
mmap2(0xb7733000, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x140) = 0xb7733000
mmap2(0xb7736000, 10600, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0xb7736000
close(3)                                = 0
mmap2(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb75f1000
set_thread_area({entry_number:-1 -> 6, base_addr:0xb75f18d0, limit:1048575, seg_32bit:1, contents:0, read_exec_only:0, limit_in_pages:1, seg_not_present:0, useable:1}) = 0
mprotect(0xb7733000, 8192, PROT_READ)   = 0
mprotect(0xb7767000, 4096, PROT_READ)   = 0
munmap(0xb7739000, 64828)               = 0
fstat64(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
mmap2(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb7748000
write(1, "First file:\n", 12First file:
)           = 12
fstat64(0, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
mmap2(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb7747000
read(0,
```

1. ¿Por qué la primera llamada que aparece es execve?
Ya que lo que se desea es reemplazar la imagen del proceso actual con una nueva, es necesario llamar
a ```execve()``` para que ejecute el programa al que apunta el filename, en este caso: ```./ejercicio2b```.

2. ¿Qué significan los resultados (números que están luego del signo ‘=’)?
Los numeros significan si la ejecucion ha sido exitosa o no y dependen del proceso que se ejecute.
En el caso de las llamadas hechas por el codigo, el numero varia segun la llamada, para el caso de open,
por ejemplo:

```
open("/etc/ld.so.cache", O_RDONLY)      = 3
```

Se tiene un return de 3, que en este caso indica que el open fue exitoso.

3. ¿Por qué entre las llamadas realizadas por usted hay un readvacío?
Se hace un read vacio porque el sistema tiene que recopilar la memoria suficiente para poder leer los
nuevos archivos y luego para escribir en el segundo archivo, con ayuda de mmap2.

4. Los tres servicios son:

    a. ```access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)```
    Este proceso verifica si el proceso que esta llamando puede acceder al archivo provisto con el path.
    La respuesta -1 significa que no se pudo acceder al archivo.

    b. ```mmap2(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xb7749000``` 
    mmap2 realiza un mapping en memoria en la direccion virtual del proceso que llama. El primer
    parametro corresponde a la direccion inicial, el segundo parametro es el tamanio del mapeo.
    El tercer parametro describe la memoria de proteccion deseada para el mapeo. El cuarto argumento
    determina si las actualizaciones al mapeo son visibles por otros procesos que esten mapeando la misma
    region.

    c. ```mprotect(0xb7732000, 4096, PROT_NONE)   = 0```
    El proceso mprotect cambia el acceso de las protecciones para las paginaciones de memoria del proceso
    que esta llamando y que contengan cualquier parte del rango de direcciones en el intervalo:
    ```
    [addr, addr+len-1]
    ```
    Si el proceso que llama trata de acceder a la memoria en una manera en la que viola las protecciones, el
    kernel generara una senial para el proceso. De ser exitoso, regresara un valor de 0, en error regresara
    -1.
    
#### Archivos de C
[Ejercicio B](./ejercicio2b.c)

### Ejercicio 3

1. ¿Qué ha modificado aquí, la interfaz de llamadas de sistema o el API? Justifique su respuesta.
La interfaz de llamadas de sistema de linux contiene funciones que son llamadas desde el espacio de usuario
e interactuan con el driver en el espacio de kernel para obtener los datos deseados. Ahora, la API, es mas
bien un termino generico que se utiliza para identificar las funciones expuestas por cualquier libreria.
Esas funciones se implementan como parte de librerias o SDK. Todas las llamadas a sistema constituyen una API 
que el kernel provee a las aplicaciones que corren en la plataforma. Estas llamadas de sistema forman parte de una 
API, sin embargo esta no sera la API de linux. Por lo tanto aqui se modifico la interfaz de llamadas del sistema.

2. ¿Por qué usamos el número de nuestra llamada de sistema en lugar de su nombre?
Los procesos no interactuan con las llamadas a sistema a traves de nombre, sino que lo hacen a traves
de el numero de la llamada del sistema; un argumento que un proceso debe de pasar al kernel para poder
identificar la llamada de sistema requerida.

3. ¿Por qué las llamadas de sistema existentes como read o fork se pueden llamar por nombre?
Por que la API de linux ya se encuentra definida y los paquetes que interactuan con esta API ya conocen
que numero de llamada de sistema corresponde a las llamadas existentes, es decir que el nombre estara
siempre asociado a el numero de llamada de sistema respectivo y ese linking no se puede modificar.

#### Screenshot de la llamada
![alt text](https://github.com/gbrolo/SISTOS-L1/blob/master/3h.PNG)

#### Archivos de C
[Ejercicio H](./ejercicio3h.c)
