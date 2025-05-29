# Percolación — Instrucciones de uso
Holi chiquibeibis, píllense unas breves instrucciones de uso, más organizaditas que las de la vez pasada.

Este proyecto incluye un Makefile que permite ejecutar distintas acciones desde la terminal. Puedes usar los siguientes comandos:

- make run L=x P=y: ejecuta el programa con los argumentos L y P que puedes ajustar como desees.
- make coverage L=x P=y: genera un reporte de cobertura con los mismos argumentos.
- make clean: elimina archivos generados automáticamente.

Tengan en cuenta que x,y son números cualquiera que pueden poner para cada parámetro. Por ejemplo:

>make run L=12 P=0.6
>make coverage L=12 P=0.6
>make clean

Para visualizar el reporte de cobertura, abre el archivo coverage/index.html con firefox u otro navegador:

>firefox coverage/index.html

Adicionalmente, el Makefile organiza los archivos en dos directorios:

- bin/: contiene los archivos objeto y el ejecutable percolacion.x.
- coverage/: contiene el reporte HTML de cobertura.