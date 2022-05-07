# Quadtree

## Para la visualización de las particiones

### Requisitos

Se hizo uso de **SDL2**. Para instalarlo en **Linux**, basta con emplear
```
sudo apt-get install libsdl2-dev
```

### Ejecución

Utilizar `make` en la línea de comando para obtener el ejecutable.

La dimensión del quadtree está definida por la dimensión de la ventana del programa. Este parámetro está en 800 por defecto, pero puede ser modificado empleando los argumentos de main, de tal forma que
```
./a.out 700
```
debería resultar en una ventana de tamaño 700.

## Para la visualización del grafo

### Requisitos

Para transformar los datos del árbol a un formato JSON, se empleó [JSON for Modern C++](https://github.com/nlohmann/json).

Asimismo, se utilizaron los siguientes módulos para Python para mostrar el grafo:
- matplotlib
- pydot
- networkx

Para instalarlos, basta con utilizar
```
pip3 install <nombre del módulo>
```

(Cabe mencionar que `pydot` viene dentro de `matplotlib`).

Respecto a dependencias del mismo sistema operativo, se requiere tener instalado `graphviz`, lo que se hace con

```
sudo apt-get install graphviz
```

### Ejecución

[por completar]
