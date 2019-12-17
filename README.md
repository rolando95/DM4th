# D-M4th
[![C++Version](https://img.shields.io/badge/C%2B%2B-11%2C%2014%2C%2017-blue)](C++11,14,17)
[![Build Status](https://travis-ci.org/rolando95/DM4th.svg?branch=master)](https://travis-ci.org/rolando95/DM4th)

D-M4th es una librería escrita en `C++` que métodos para un fácil manejo de operaciones con vectores, matrices, arreglos dinámicos de N dimensiones y números complejos. 

![Calculator Screenshot](resources/screenshots/DM4thScreenshot.png)

## Características
- Clase tipo `NDArray` que permitirán manejar vectores, matrices y arreglos de N dimensiones.
  - Modificar el número de elementos y dimensiones de un arreglo con métodos `resize()` o `reshape()`.
  - Inserción y eliminación de elementos con `push()` y `pop()`.
  - Operaciones algebráicas entre arreglos y escalares usando operadores de suma, resta, multiplicación, división, residuo, etc. Ejemplo: `arr1`+`arr2`, `arr1`*`10`, etc.
  - Operaciones relacionales y lógicas entre arreglos y escalares usando operadores relacionales o lógicos. Ejemplo:  `arr1`==`arr2`, `arr1`<=`arr2`, `arr`>`4` || `(arr2 + 1)`<`5`, etc.
  - Sistema de conteo de referencias por array que permitirán administrar memoria sin pensar en punteros por parte del programador.
  - Obtener subArreglos (array slicing) de forma similar a Matlab y Python con el método `view()` y `slice()`.
    - Un array slicing en numpy (Python) como `arr[1:5]`, su equivalente en DM4th sería `arr.view(slice(1,5))`
    - Para 2 dimensiones, el equivalente de `arr[:, 4:]` en DM4th sería `arr.view(ALL, slice(4,END))`.
    - El equivalente de `arr[2:6, 3, :3]` en DM4th sería `arr.view(slice(2,6), 3, slice(0,3))` y así sucesivamente.
  - Métodos para realizar operaciones de álgebra lineal en paralelo usando OpenMP.

- Métodos numéricos de utilidad para diferentes operaciones de cálculo diferencial e integral, álgebra lineal, entre otros.

## Instalación y compilación
* D-M4th es un `header-only library`. No es necesario compilar dependencias para instalar. Basta con descargar o clonar la librería dentro de tu proyecto e incluir la cabecera `#include "DM4th/DM4th.h"`.

    Si no tienes ningún entorno de desarrollo instalado, puedes instalar un editor de código y compilador de C++ recomendado:
    
   *  [Instalar compilador de C++ y Visual Studio Code para Windows](https://code.visualstudio.com/docs/cpp/config-mingw).


  **NOTA:** D-M4th es compatible con versiones de C++11 en adelante.

* Si usas g++, la siguiente instrucción de compilación con `D-M4th` puede ser suficiente:

    ```sh
    g++ -std=c++11 main.cpp
    ```

## Ejemplos

* Programa Hola Mundo con `D-M4th`

    - Código

    ```C++
    #include "DM4th/DM4th.h"

    using namespace std;
    using namespace DM4th;

    int main()
    {
        NDArray<string> hello  = items<string>("Hello", "World");
        NDArray<number> myList = range<number>(10);

        cout << hello << endl;
        cout << myList << endl;

        cin.get();
        return 0;
    }
    ```
    - Salida
    ```C++
    ["Hello", "World"]
    [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    ```
<details>
<summary>Operaciones con números complejos</summary>

* Código
    ```C++
    
    #include "DM4th/DM4th.h"

    using namespace std;
    using namespace DM4th;

    int main()
    {
        number a = 5+7i;
        number b = 10-2i;
        number c = -25;

        cout<< "sum:  " << a+b << endl;
        cout<< "sub:  " << a-b << endl;
        cout<< "mult: " << a*b << endl;
        cout<< "div:  " << a/b << endl;
        cout<< "sqrt: " << sqrt(c) << endl;
        cout<< "sin:  " << sin(rad(c)) << endl;
        
        cin.get();
        return 0;
    }
    ```
* Salida
    ```C++
    sum:  15+5i
    sub:  -5+9i
    mult: 64+60i
    div:  0.346154+0.769231i
    sqrt: 5i
    sin:  -0.422618
    ```
</details>

<details>
<summary>Operaciones con arreglos</summary> 

* Código
    ```C++
    #include "DM4th/DM4th.h"

    using namespace std;
    using namespace DM4th;

    int main()
    {
        NDArray<number> arr1 = range<number>(5);
        NDArray<number> arr2 = range<number>(10,5,-1);
        number value = 10;
        
        cout<< "arr1: " << arr1 << endl;
        cout<< "arr2: " << arr2 << endl;
        cout<< "sum:  " << arr1+arr2 << endl;
        cout<< "sub:  " << arr1-arr2 << endl;
        cout<< "mult: " << arr1*arr2 << endl;
        cout<< "div:  " << arr1/value << endl;

        cin.get();
        return 0;
    }
    ```
* Salida
    ```C++
    arr1: [0, 1, 2, 3, 4]
    arr2: [10, 9, 8, 7, 6]
    sum:  [10, 10, 10, 10, 10]
    sub:  [-10, -8, -6, -4, -2]
    mult: [70]
    div:  [0, 0.1, 0.2, 0.3, 0.4]
    ```
</details>

<details>
<summary>Inserción y eliminación de elementos en arreglos de una dimensión</summary> 

* Código
    ```C++
    #include "DM4th/DM4th.h"

    using namespace std;
    using namespace DM4th;

    int main()
    {
        NDArray<number> arr1 = items<number>(1,3,5,7,9);
        NDArray<number> arr2 = items<number>(2,4,6,8,0);
        number value = 1000;

        cout << "arr1: " << arr1 << endl;
        cout << "arr2: " << arr2 << endl << endl;

        cout << "value " << value << " inserted into arr1: ";
        arr1.push(value);
        cout << arr1 << endl << endl;

        cout << "Inserting arr2 into arr1: ";
        arr1.pushArray(arr2);
        cout << arr1 << endl << endl;

        cout << "Inserting " << -999 << " into arr1 at index 3: ";
        arr1.push(-999, 3);
        cout << arr1 << endl << endl;

        cout << "Removing some elements from arr1:" << endl;
        arr1.pop();
        cout << arr1 << endl ;

        arr1.pop(0);
        cout << arr1 << endl;

        cin.get();
        return 0;
    }
    ```
* Salida
    ```c++
    arr1: [1, 3, 5, 7, 9]
    arr2: [2, 4, 6, 8, 0]

    value 1000 inserted into arr1: [1, 3, 5, 7, 9, 1000]

    Inserting arr2 into arr1: [1, 3, 5, 7, 9, 1000, 2, 4, 6, 8, 0]

    Inserting -999 into arr1 at index 3: [1, 3, 5, -999, 7, 9, 1000, 2, 4, 6, 8, 0]

    Removing some elements from arr1:
    [1, 3, 5, -999, 7, 9, 1000, 2, 4, 6, 8]
    [3, 5, -999, 7, 9, 1000, 2, 4, 6, 8]
    ```
</details>

<details>
<summary>Operaciones con arreglos de 2 dimensiones</summary>

* Código
    ```C++
    #include "DM4th/DM4th.h"

    using namespace std;
    using namespace DM4th;

    int main()
    {
        NDArray<number> arr1 = range<number>(10,25);
        cout << "arr1:\n" << arr1 << endl;

        arr1.reshape(3,5);
        cout << "Reshape 3x5:\n" << arr1 << endl;

        arr1.resize(3,4);
        cout << "Resize 3x4:\n" << arr1 << endl;

        arr1.resize(4,4);
        arr1(3,0) = -7i;
        cout << "Resize 4x4:\n" << arr1 << endl;

        NDArray<number> arr2 = arr1+arr1;
        cout << "arr2=arr1+arr1:\n" << arr2 << endl;

        cout << "arr2*10:\n" << arr2*10 << endl;

        cin.get();
        return 0;
    }
    ```
* Salida
    ```c++
    arr1:
    [10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24]
    Reshape 3x5:
    [
        [10, 11, 12, 13, 14],
        [15, 16, 17, 18, 19],
        [20, 21, 22, 23, 24]
    ]
    Resize 3x4:
    [
        [10, 11, 12, 13],   
        [15, 16, 17, 18],   
        [20, 21, 22, 23]
    ]
    Resize 5x5:
    [
        [10, 11, 12, 13],
        [15, 16, 17, 18],
        [20, 21, 22, 23],
        [-7i, 0, 0, 0]
    ]
    arr2=arr1+arr1:
    [
        [20, 22, 24, 26],
        [30, 32, 34, 36],
        [40, 42, 44, 46],
        [-14i, 0, 0, 0]
    ]
    arr2*10:

    [
        [200, 220, 240, 260],
        [300, 320, 340, 360],
        [400, 420, 440, 460],
        [-140i, 0, 0, 0]
    ]
    ```
</details>

<details>
<summary>Trabajando con elementos de Array</summary>

* Código
  ```C++
    #include "DM4th/DM4th.h"

    using namespace std;
    using namespace DM4th;

    int main(){
        NDArray<number> arr1 = range<number>(10,18,2);
        NDArray<number> arr2 = zeros<number>(2,2);

        arr1.reshape(2,2);

        cout << "arr1:\n" << arr1 << endl;
        cout << "arr2:\n" << arr2 << endl << endl;

        cout << "Copying arr1 items into arr2" << endl;
        for(int x=0; x<arr1.shape(0); x++)
        {
            for(int y=0; y<arr1.shape(1); y++)
            {
                arr2(x,y) = arr1(x,y);
            }
        }
        cout << arr2 << endl << endl;

        cout << "Access to each arr2 item using a single foreach in C++" << endl;
        for(auto &x: arr2)
        {
            cout << x << endl; // Printing each item of arr2
            x = 15; // assigning 15 into each item of arr2
        }
        cout << arr2 << endl << endl;

        cout << "Another way to access each item of arr2 using a single for" << endl; 
        number value = 10;
        for(int x=0; x<arr2.data_size(); x++)
        {
            arr2.data_item(x) = value*x;
        }
        cout << arr2 << endl << endl;

        cout << "Copying arr1 items into arr2 using getCopy function" << endl;
        arr2 = arr1.getCopy();
        cout << arr2 << endl << endl;

        cin.get();
        return 0;
    }
  ```
* Salida
  ```C++
    arr1:
    [
        [10, 12],
        [14, 16]
    ]
    arr2:
    [
        [0, 0],
        [0, 0]
    ]

    Copying arr1 items into arr2
    [
        [10, 12],
        [14, 16]
    ]

    Access to each arr2 item using a single foreach in C++
    10
    12
    14
    16
    [
        [15, 15],
        [15, 15]
    ]

    Another way to access each item of arr2 using a single for
    [
        [0, 10],
        [20, 30]
    ]

    Copying arr1 items into arr2 using getCopy function
    [
        [10, 12],
        [14, 16]
    ]
  ```
</details>

<details>
<summary>Arreglos dinámicos de más de 2 dimensiones</summary>

* Código
  ```C++
    #include "DM4th/DM4th.h"

    using namespace std;
    using namespace DM4th;

    int main()
    {
        NDArray<number> arr1 = range<number>(0,24,2);
        cout << "arr1\n" << arr1 << endl << endl;

        arr1.reshape(2,2,3);
        cout << "Reshape 2x2x3:\n" << arr1 << endl << endl;

        arr1 /= 10;
        cout << "arr1/10:\n" << arr1 << endl << endl;

        cout << "Assigning 9999 into arr2(1,0,2)" << endl;
        arr1(1,0,2) = 9999;
        cout << arr1 << endl << endl;

        arr1.reshape(2,6);
        cout << "Reshape 2x6:\n" << arr1 << endl << endl;

        cin.get();
        return 0;
    }
    ```
* Salida
    ```c++
    arr1
    [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22]

    Reshape 2x2x3:
    [
        [
            [0, 2, 4],
            [6, 8, 10]
        ],
        [
            [12, 14, 16],
            [18, 20, 22] 
        ]
    ]

    arr1/10:
    [
        [
            [0, 0.2, 0.4],
            [0.6, 0.8, 1]
        ],
        [
            [1.2, 1.4, 1.6],
            [1.8, 2, 2.2]
        ]
    ]

    Assigning 9999 into arr2(1,0,2)
    [
        [
            [0, 0.2, 0.4],
            [0.6, 0.8, 1]
        ],
        [
            [1.2, 1.4, 9999],
            [1.8, 2, 2.2]
        ]
    ]

    Reshape 2x6:
    [
        [0, 0.2, 0.4, 0.6, 0.8, 1],
        [1.2, 1.4, 9999, 1.8, 2, 2.2]
    ]
    ```
</details>

<details>
<summary>Array Slicing</summary>

* Código
    ```C++
    #include "DM4th/DM4th.h"

    using namespace std;
    using namespace DM4th;

    int main()
    {
        NDArray<number> matrix = items<number>(
            12, 90, 34,
            78, 56, 65,
            87, 43, 21
        ).reshape(3, 3);

        cout << "Matrix:\n" << matrix << endl;

        cout << "\nGet column 1 of matrix" << endl;
        NDArray<number> vector = matrix.view(ALL, 1); // Like vector = matrix[:, 1] in Python
        cout << vector << endl;

        cout << "\nSet 1000 to row 2 of matrix" << endl;
        matrix.view(2) = 1000; // Like matrix[2,:] = 1000 in Python
        cout << matrix << endl;

        cout << "\nSet 3+2i to column 0 of matrix" << endl;
        matrix.view(ALL, 0) = 3+2i; // Like matrix[:,0] = complex(3,2) in Python
        cout << matrix << endl;


        NDArray<number> arr1 = range<number>(10);
        NDArray<number> arr2 = items<number>(1i, 3i, 5i, 7i, 9i, 11i, 13i, 15i, 17i, 19i);
        cout << "\narr1:" << arr1 << endl;
        cout << "arr2:" << arr2 << endl;

        cout << "\nSetting 3rd, 4th and 5th elements of arr1 from some elements of arr2" << endl;
        arr1.view(slice(2,5)) = arr2.view(slice(2,5)); // Like arr1[2:5] = arr2[2:5] in Python 
        cout << arr1 << endl;

        cin.get();
        return 0;
    }
    ```
* Salida
    ```C++
    Matrix:
    [
        [12, 90, 34],
        [78, 56, 65],
        [87, 43, 21]
    ]

    Get column 1 of matrix
    [90, 56, 43]

    Set 1000 to row 2 of matrix
    [
        [12, 90, 34],
        [78, 56, 65],
        [1000, 1000, 1000]
    ]

    Set 3+2i to column 0 of matrix
    [
        [3+2i, 90, 34],
        [3+2i, 56, 65],
        [3+2i, 1000, 1000]
    ]

    arr1:[0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    arr2:[i, 3i, 5i, 7i, 9i, 11i, 13i, 15i, 17i, 19i]

    Setting 3rd, 4th and 5th elements of arr1 from some elements of arr2
    [0, 1, 5i, 7i, 9i, 5, 6, 7, 8, 9]

    ```
</details>

<details>
<summary>Métodos numéricos</summary>

* Código
    ```C++
    #include "DM4th/DM4th.h"

    using namespace std;
    using namespace DM4th;

    number myFunction(number x)
    {
        return x*x + 25;
    }

    int main()
    {
        number a = 5;
        number b = 3.5;
        number c = -0.2i;
        
        NDArray<number> polynomial = items<number>(6, 1, -1, -3);

        
        cout << "Factorial: " << factorial(a) << " " << factorial(b) << " " << factorial(c) << endl;

        // Root of f(x)=x*x+25
        cout << "Root of myFunction: " << newtonRaphson(myFunction) << endl;

        // Area of f(x)=x*x+25 [from 0 to 10]
        cout << "Integral: " << integral(myFunction, 0, 10) << endl;
    
        // All roots of f(x)=6x^(3)+x^(2)-x-3
        cout << "Roots: " << bairstowsMethod(polynomial) << endl;

        cin.get();
        return 0;
    }
    ```
* Salida
    ```c++
    Factorial: 120 11.6317 0.961947
    Root of myFunction: 5i
    Integral: 583.333
    Roots: [-0.486931+0.618327i, -0.486931-0.618327i, 0.807195]
    ```
</details>

<details>
<summary>Lectura y escritura de archivos</summary>

* Código
    ```C++
    #include "DM4th/DM4th.h"

    using namespace std;
    using namespace DM4th;
    
    int main()
    {
        NDArray<number> arr1 = identity<number>(10,10);

        arr1.saveFile("example.txt"); // example.txt is created automatically if it doesn't exist

        NDArray<number> arr2;
        arr2.loadFile("example.txt");

        cout << arr2 << endl;

        cin.get();
        return 0;
    }
    ```
* Salida
    ```C++
    [
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 1, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 1, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 1, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 1, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 1, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 1]
    ]
    ```
</details>