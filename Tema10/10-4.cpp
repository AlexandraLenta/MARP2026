/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#include "IndexPQ.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>


int resolver(vector<string> const& lineas) {
    int n = lineas.size(), m = lineas[0].size();

    // vector<vector<int>> caminos(n + 1, vector<int>(m + 1, 0)); // 0 : no se puede llegar

    // caminos[1][0] = 1;

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= m; j++) {
    //         if (lineas[i - 1][j - 1] == 'X') {
    //             caminos[i][j] = 0;
    //         }
    //         else
    //             caminos[i][j] = caminos[i-1][j] + caminos[i][j - 1];
    //     }
    // }

    vector<int> caminosLin(m + 1, 0); // 0 : no se puede llegar

    caminosLin[1] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (lineas[i - 1][j - 1] == 'X') {
                caminosLin[j] = 0;
            }
            else
                caminosLin[j] = caminosLin[j] + caminosLin[j - 1];
        }
    }


    return caminosLin[m];
}

void resuelveCaso()
{
    int N, M;
    cin >> N >> M;

    vector<string> lineas(N);
    for (auto& s : lineas) {
        cin >> s;
    }

    cout << resolver(lineas) << '\n';
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
