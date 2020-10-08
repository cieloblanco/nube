Ejecución en threads.  
Uso de RAM de cada thread según parámetros en el main.  
Generación de archivo de 9.8 GB a partir de "el_quijote.txt".  

g++ -pthread wordcount.cpp -o w; ./w hola.txt

tam_bloque. Es el tamaño del bloque de texto que cada thread tendrá que procesar.  
partes=1. Indica el número de partes en las que se divide el bloque. Se divide según la RAM que se quiera usar.

**Ejemplos:**

*hola.txt*
![alt text](https://raw.githubusercontent.com/cieloblanco/nube/main/wordcount/presentacion/imagenes/holatxt.png | width=480)
![alt text](https://raw.githubusercontent.com/cieloblanco/nube/main/wordcount/presentacion/imagenes/holar.png)

*peru.txt*
![alt text](https://raw.githubusercontent.com/cieloblanco/nube/main/wordcount/presentacion/imagenes/perutxt.png)
![alt text](https://raw.githubusercontent.com/cieloblanco/nube/main/wordcount/presentacion/imagenes/perur.png)


