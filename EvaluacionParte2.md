# 4. Geometría computacional

a. Dada una aplicación de mapas, necesitamos identificar si un usuario se 
encuentra dentro de una determinada zona, calcular distancias a puntos de 
interés, o encontrar rutas como segmentos de línea. Cada punto representa la 
ubicación de un usuario o de un destino. Los segmentos pueden modelar caminos
o trayectorias. Los polígonos definen regiones como barrios o zonas de 
cobertura.

---

b. Utilizando el algoritmo _ray casting_ podemos determinar si un punto está 
dentro de un polígono, trazando una semirrecta desde el punto hacia la derecha,
y se cuenta cuántas veces cruza los lados del polígono. Si el número de cruces
es par, el punto está fuera. Si es impar, el punto está dentro. La 
implementación de este algoritmo se encuentra en `parte2ejercicio4b.cpp`.

---

c. Se le pasó el siguiente prompt a GPT-6 Luna:

> Tengo el siguiente algoritmo ray casting en C++ para determinar si un punto 
> está dentro de un polígono:
> 
> `parte2ejercicio4b.cpp` 
> 
> Realizá una revisión del código. Se puede mejorar, en cuanto a la eficiencia? 
> Ignorá las warnings de Clang-tidy

_Las warnings de Clang-tidy son las que arroja mi IDE (CLion)._

La respuesta de la IA fue la siguiente:

> El algoritmo es **O(n)** en tiempo y **O(1)** en memoria. Para un polígono 
> arbitrario hay que revisar sus aristas, así que no se puede mejorar el orden 
> asintótico en una sola consulta sin información adicional, como una 
> estructura espacial preprocesada para muchas consultas.
> 
> Hay dos aspectos importantes:
> 
> - El resultado para puntos en el borde no está definido explícitamente. Con 
>   la comparación estricta actual, el punto `(0,2)` del ejemplo se considera
>   adentro, pero no conviene depender de ese comportamiento accidental.
> - `n == 0` no causa una división por cero, pero la función debería decidir 
>   qué hacer con polígonos con menos de tres vértices. También es preferible 
>   usar `size_t` para los índices.
> 
> Una versión sencilla que trata el borde como **adentro** es:
> 
> ```cpp
> #include <cstddef>
> #include <vector>
> 
> struct Punto {
>     double x, y;
> };
> 
> bool estaEnSegmento(const Punto& a, const Punto& b, const Punto& p) {
>     const double cruz =
>         (b.x - a.x) * (p.y - a.y) -
>         (b.y - a.y) * (p.x - a.x);
> 
>     if (cruz != 0.0) {
>         return false;
>     }
> 
>     return p.x >= (a.x < b.x ? a.x : b.x) &&
>            p.x <= (a.x > b.x ? a.x : b.x) &&
>            p.y >= (a.y < b.y ? a.y : b.y) &&
>            p.y <= (a.y > b.y ? a.y : b.y);
> }
> 
> bool estaAdentro(const std::vector<Punto>& poligono, const Punto& p) {
>     const std::size_t n = poligono.size();
>     if (n < 3) {
>         return false;
>     }
> 
>     bool adentro = false;
> 
>     for (std::size_t i = 0, j = n - 1; i < n; j = i++) {
>         const Punto& a = poligono[j];
>         const Punto& b = poligono[i];
> 
>         if (estaEnSegmento(a, b, p)) {
>             return true;  // Convención: el borde cuenta como adentro.
>         }
> 
>         const bool cruza =
>             ((a.y > p.y) != (b.y > p.y)) &&
>             (p.x < a.x + (b.x - a.x) * (p.y - a.y) / (b.y - a.y));
> 
>         if (cruza) {
>             adentro = !adentro;
>         }
>     }
> 
>     return adentro;
> }
> ```
> 
> **Eficiencia:** esta versión sigue siendo O(n), pero evita copiar cada 
> vértice al recorrer el polígono y retorna inmediatamente si detecta que el 
> punto está en una arista. La división solo se evalúa cuando la arista cruza 
> la horizontal del punto; en ese caso, `a.y != b.y`, así que no divide por 
> cero.
> 
> **Precisión:** `cruz != 0.0` compara números de punto flotante exactamente. 
> Si las coordenadas provienen de cálculos y no son exactas, esa prueba puede
> fallar cerca del borde. En ese caso, usá una tolerancia elegida según la 
> escala de tus datos, o una biblioteca de geometría robusta. Evitaría agregar 
> un `epsilon` genérico sin considerar las unidades y magnitudes de las 
> coordenadas.

El código propuesto por GPT-6 no realiza significativos cambios al algoritmo 
propuesto inicialmente. Trata el caso límite de un polígono de menos de tres
vértices (es decir una línea), que mi algoritmo no consideró. Contempla la 
comparación de punto flotante, y usa referencias en lugar de copiar cada 
vértice, y retorna inmediatamente si detecta que el punto está en una arista.
Todas estas son mejoras prácticas, pero no alteran la propuesta inicial del
algoritmo.
