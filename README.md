# Quadtree

## Requisitos

### SDL2

Para instalarlo en **Linux**, basta con emplear
```
sudo apt-get install libsdl2-dev
```

En el caso de **Windows**, el procedimiento es más largo (nos guiamos del procedimiento mostrado en [este](https://www.youtube.com/watch?v=KsG6dJlLBDw) vídeo):
1. Descargar **[MinGW64](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-win32/seh/x86_64-8.1.0-release-win32-seh-rt_v6-rev0.7z/download)** 
2. Descargar la [librería de SDL2 para MinGW](https://libsdl.org/download-2.0.php)
3. Descargar la [librería de SDL_image 2.0 para MinGW](https://www.libsdl.org/projects/SDL_image/)
4. 


## Ejecución

Utilizar `make` en la línea de comando para obtener el ejecutable.

La dimensión del quadtree está definida por la dimensión de la ventana del programa. Este parámetro está en 800 por defecto, pero puede ser modificado empleando los argumentos de main, de tal forma que
```
./a.out 700
```
debería resultar en una ventana de tamaño 700.