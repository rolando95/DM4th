# DM4th
DM4th es una librería escrita en C++ que prevee numerosos métodos y clases que permitirán un fácil manejo de operaciones con vectores, matrices, árboles y números complejos. 

![Calculator Screenshot](resources/screenshots/DM4thScreenshot.png)

## Características
- Clase tipo NDArray que permitirán manejar vectores y matrices multidimensionales de manera dinámica
  - Métodos de push, pop, resize y reshape incluídos
  - Sobrecarga de operadores aritméticos y binarios
  - Sistema de conteo de referencias por array que permitirán administrar memoria sin pensar en punteros por parte del programador 
- Clase tipo Tree con métodos para manejo de estructuras no lineales de forma sencilla
  - Árboles binarios y árboles N-arios soportados
  - Métodos de push, pop y resize de hijos
  - Sistema de conteo de referencias por cada hijo de un árbol que permitirán administrar memoria sin pensar en punteros por parte del programador
- Métodos numéricos de utilidad para diferentes operaciones de cálculo diferencial e integral, álgebra lineal, entre otros.
  - Soluciones de métodos de búsqueda de raíces de función como Newthon-Raphson y el Método de Bairstow con soporte de raíces complejas
  - Soporte de resultados con números reales y complejos en todos los métodos incluídos en la librería
- Entrada y salida por consola utilizando métodos input() y print() de números complejos, arreglos multidimensionales y árboles
- 