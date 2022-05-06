# Quadtree

## Requisitos

### SDL2

Para instalarlo en **Linux**, basta con emplear
```
sudo apt-get install libsdl2-dev
```

En el caso de **Windows**, el procedimiento es más largo (nos guiamos del procedimiento mostrado en este [tutorial de SDL2](https://www.youtube.com/watch?v=KsG6dJlLBDw)

1. Descargar **[MinGW64](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download)** 
2. Descargar la [librería de SDL2 para MinGW](https://libsdl.org/download-2.0.php)
3. Descargar la [librería de SDL_image 2.0 para MinGW](https://www.libsdl.org/projects/SDL_image/)
4. Descomprimir el archivo de MinGW64 y copiar la carpeta en una ubicación deseada (se recomienda en el disco C).
5. Añadir una variable global que permita usar MinGW64 con mayor facilidad (incluir la dirección en el path, por ejemplo `C:\mingw64\bin`)
6. Descomprimir la carpeta de SDL2, copiar la carpeta `x86_64-w64-mingw32` en la misma carpeta en la que está la carpeta de MinGW64; renombrar si se desea.
7. Descomprimir la carpeta de la imagen para SDL2, ir a la carpeta `x86_64-w64-mingw32`, seleccionar las carpetas dentro de esta y pegarlas en la carpeta de SDL2.
8. Configurar el editor de texto a utilizar para que permita reconocerlo (de ser necesario).


## Ejecución

Utilizar `make` en la línea de comando para obtener el ejecutable.

La dimensión del quadtree está definida por la dimensión de la ventana del programa. Este parámetro está en 800 por defecto, pero puede ser modificado empleando los argumentos de main, de tal forma que
```
./a.out 700
```
debería resultar en una ventana de tamaño 700.