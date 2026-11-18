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

int resolver(vector<vector<int>> const& casillas) {
    int n = casillas.size();

    vector<vector<int>> maximo(n + 1, vector<int>(n + 2, 0));
    int maximoGen = 0;

    for (int i = n - 1; i >= 0; i--) {
        for (int j = n + 1; j >= 0; j--) {
            maximo[i][j] = max3(maximo[i+1][j], maximo[i+1][j - 1], maximo[i+1][j + 1]) + casillas[i][j];
            maximoGen = max(maximoGen, maximo[i][j]);
        }
    }

    return maximoGen;
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

    cout << resolver(casillas) << '\n';
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
