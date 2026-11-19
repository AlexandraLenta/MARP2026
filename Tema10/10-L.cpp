/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"
#include "EnterosInf.h"
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

pair<EntInf, int> resolver(vector<int> const &valor, int C, int limit)
{
    int n = valor.size();

    // Matriz<EntInf> monedas(n + 1, maxC + 1, Infinito); 
    vector<EntInf> monedas(limit + 1, Infinito);

    // monedas[0][0] = 0;
    monedas[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        // monedas[i][0] = 0;
        for (int j = limit; j >= valor[i - 1]; j--)
        {
            // if (valor[i - 1] > j)
            //     monedas[i][j] = monedas[i - 1][j];
            // else
            //     monedas[i][j] = min(monedas[i - 1][j], monedas[i - 1][j - valor[i - 1]] + 1);

            monedas[j] = min(monedas[j], monedas[j - valor[i-1]] + 1);
        }
    }

    pair<EntInf, int> res;
    // for (int i = C; i < maxC; i++) {
    //     if (monedas[n][i] != Infinito) {
    //         res.first = monedas[n][i];
    //         res.second = i;
    //         break;
    //     }
    // }

    for (int i = C; i <= limit; i++) {
        if (monedas[i] != Infinito) {
            res.first = monedas[i];
            res.second = i;
            break;
        }
    }

    return res;
}

void resuelveCaso()
{
    int M, N;
    cin >> M >> N;

    vector<int> monedas(N);
    int sumaMax = 0;
    int a;
    int maxElem = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> a;
        monedas[i] = a;
        sumaMax += a;
        maxElem = max(maxElem, a);
    }

    auto res = resolver(monedas, M, min(sumaMax, maxElem + M));
    cout << res.second << " " << res.first << '\n';
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
