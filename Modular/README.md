Holi chiquibeibis, para correr el código desde la consola pongan > make run L=x P=y. 
x, y son números cualquiera que quieran ingresar como argumentos.
También pueden hacer > make clean
                     > make coverage L=x P=y

Para ver el archivo generado en el coverage, pongan en la terminal > firefox coverage/index.html

Verifiquen que en el compu esté instalado todo para que corra lcov, gcov, firefox, etc.

Adicionalmente, make genera una estructura que incluye:
-El directorio bin/, donde se almacenan los archivos objeto y el ejecutable percolacion.x
-El directorio coverage/, que contiene el reporte HTML.