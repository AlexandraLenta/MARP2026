/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
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

int max3(int a, int b, int c) {
    int ret = max(a, b);
    ret = max(ret, c);
    return ret;
}

pair<int, int> resolver(vector<vector<int>> const& casillas) {
    int n = casillas.size();

    // vector<vector<int>> maximo(n + 1, vector<int>(n + 2, 0));

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= n; j++) {
    //         maximo[i][j] = max3(maximo[i-1][j-1], maximo[i-1][j], maximo[i-1][j+1]) + casillas[i-1][j-1];
    //     }
    // }

    // int maximoGen = 0, colInicial = 0;
    // for (int j = 1; j <= n; j++) {
    //     if (maximo[n][j] > maximoGen) {
    //         maximoGen = maximo[n][j];
    //         colInicial = j;
    //     }
    // }

    vector<int> maximo(n + 2, 0);

    for (int i = 0; i < n; i++) {
        int antIzq = 0;
        for (int j = 1; j <= n; j++) {
            int antAct = maximo[j];
            maximo[j] = max3(antIzq, antAct, maximo[j + 1]) + casillas[i][j - 1];
            antIzq = antAct;
        }
    }

    int maximoGen = 0, colInicial = 0;
    for (int j = 1; j <= n; j++) {
        if (maximo[j] > maximoGen) {
            maximoGen = maximo[j];
            colInicial = j;
        }
    }

    return {maximoGen, colInicial};
}

void resuelveCaso()
{
    int N, a;
    cin >> N;
    vector<vector<int>> casillas(N, vector<int>(N));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> a;
            casillas[i][j] = a;
        }
    }
    auto res = resolver(casillas);
    cout << res.first << ' ' << res.second << '\n';
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
