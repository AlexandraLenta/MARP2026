/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include <limits>
using namespace std;

/*@ <answer>

trozos[i][j] = mínimo esfuerzo para hacer todos los cortes que hay estrictamente entre la marca i y la marca j (con i y j ya siendo extremos del trozo).

trozos[i][i] = 0; -> no hay cortes entre la misma marca
trozos[i][i+1] = 0; -> no hay cortes entre dos marcas seguidas

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

int resolver(vector<long long> const &D, int const L)
{
    int n = D.size() - 1;
    Matriz<long long> trozos(n + 1, n + 1, 0);
    
    for (int d = 2; d <= n; ++d) // recorre diagonales
        for (int i = 0; i <= n - d; ++i)
        { // recorre elementos de diagonal
            int j = i + d;
            trozos[i][j] = numeric_limits<long long>::max();

            for (int k = i + 1; k <= j - 1; ++k)
            {
                long long temp = trozos[i][k] + trozos[k][j] + (D[j] - D[i]) * 2; // add esfuerzo de este

                if (temp < trozos[i][j])
                { // es mejor partir por k
                    trozos[i][j] = temp;
                }
            }
        }

    return trozos[0][n];
}

void resuelveCaso()
{
    int L, N;
    cin >> L >> N;

    int a;
    vector<long long> nrs(N + 2);
    
    nrs[0] = 0;
    nrs[N + 1] = L;

    for (int i = 1; i <= N; i++)
    {
        cin >> a;
        nrs[i] = a;
    }

    cout << resolver(nrs, L) << '\n';
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main()
{
    // entrada/salida rápida
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ajustes para que cin extraiga directamente de un fichero (solamente en local)
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
    {
        cout << "Error: no se ha podido abrir el archivo de entrada." << endl;
        // sin fichero no hay nada que leer, y cin >> ... dejaría las
        // variables sin tocar, con su valor basura
        return 1;
    }
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
