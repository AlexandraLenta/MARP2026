/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "ConjuntosDisjuntos.h"
#include <vector>
using namespace std;

/*@ <answer>

Podemos utilizar conjuntos disjuntos para resolver este problema.
Primero leemos el número de filas y columnas, luego construimos los conjuntos.

Para cada celda, miramos la derecha y las 3 direcciones inferiores, para evitar
al máximo unir con celdas de atrás, que ya hemos mirado.

Después de cada nueva celda añadida, decidimos el máximo (entre el último máximo y
el tamaño de la mancha que estamos mirando ahora).

Al final de la construcción inicial, imprimimos el máximo.

Después, leemos y unimos las nuevas celdas contaminadas. Esta vez tenemos que mirar en
las 8 direcciones, ya que no vamos en orden. De la misma manera que antes, decidimos 
el máximo.

Después de cada nueva celda añadida, imprimimos el máximo.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

bool valido(int i, int j, int F, int C)
{
    return 0 <= i && i < F && 0 <= j && j < C;
}

const vector<pair<int, int>> dirs8 = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};
const vector<pair<int, int>> dirs4 = {{1, 0}, {0, 1}, {1, 1}, {-1, 1}};

void resuelveCaso()
{

    int F, C;

    cin >> F >> C;

    // matriz -> lineal: fila * nrColumnas + columna
    // lineal -> matriz: fila = indexLineal / nrCol; columna = indexLineal % nrCol

    ConjuntosDisjuntos cj(F * C);
    vector<string> lineas(F);

    for (string &linea : lineas)
    {
        cin >> linea;
    }

    int mayor = 0;

    for (int i = 0; i < F; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (lineas[i][j] != '#')
                continue;

            int curr = i * C + j;

            for (const auto &dir : dirs4) {
                int ni = i + dir.first;
                int nj = j + dir.second;

                if (valido(ni, nj, F, C) && lineas[ni][nj] == '#') {
                    cj.unir(curr, ni * C + nj);
                    // std::cout << "uniendo [" << i << ',' << j << "] con [" << ni << ',' << nj << "]\n";
                }
            }

            mayor = std::max(mayor, cj.cardinal(curr));
        }
    }

    cout << mayor << ' ';

    int N;
    cin >> N;

    int f, c;

    for (int i = 0; i < N; i++)
    {
        cin >> f >> c;
        f--; c--;
        lineas[f][c] = '#';

        mayor = std::max(mayor, 1); // nueva mancha tiene 1 celda
        int curr = f * C + c;

        for (const auto &d : dirs8) {
            int ni, nj;
            ni = f + d.first; nj = c + d.second;
            
            if (valido(ni, nj, F, C) && lineas[ni][nj] == '#') {
                cj.unir(curr, ni * C + nj);
                // std::cout << "uniendo [" << f << ',' << c << "] con [" << ni << ',' << nj << "]\n";
            }
        }

        mayor = std::max(mayor, cj.cardinal(curr));
        cout << mayor << ' ';
    }

    cout << '\n';
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main()
{
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    cin.rdbuf(cinbuf);
#endif
    return 0;
}
