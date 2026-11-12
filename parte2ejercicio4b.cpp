#include <iostream>
#include <vector>
using namespace std;

struct Punto {
    double x, y;
    Punto(double _x, double _y) : x(_x), y(_y) {}
};

bool estaAdentro(const vector<Punto>& poligono, Punto p) {
    int n = poligono.size();
    int cruces = 0;
    for (int i = 0; i < n; i++) {
        Punto a = poligono[i];
        Punto b = poligono[(i + 1) % n];

        if (((a.y > p.y) != (b.y > p.y)) &&
            (p.x < (b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x)) {
            cruces++;
            }
    }
    return cruces % 2 == 1;
}

int main() {
    // Cuadrado
    vector<Punto> poligono = {{0,0}, {4,0}, {4,4}, {0,4}};
    Punto p1(2, 2); // Punto adentro
    Punto p2(5, 2); // Punto afuera
    Punto p3(0, 2); // Punto en el borde

    cout << "El punto (2,2) está adentro? " << (estaAdentro(poligono, p1) ? "Sí" : "No") << endl;
    cout << "El punto (5,2) está adentro? " << (estaAdentro(poligono, p2) ? "Sí" : "No") << endl;
    cout << "El punto (0,2) está adentro? " << (estaAdentro(poligono, p3) ? "Sí" : "No") << endl;

    return 0;
}