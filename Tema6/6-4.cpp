/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"
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

class ARM
{
public:
    ARM(GrafoValorado<int> const& g) : costeMax(0) { // O(A * log A)
        PriorityQueue<Arista<int>> pq(g.aristas()); // O(A)

        ConjuntosDisjuntos cjtos(g.V()); // O(V)

        while (!pq.empty()) { // O(A)
            auto a = pq.top(); pq.pop(); // O(logA)
            int v = a.uno();
            int w = a.otro(v);
            
            if (!cjtos.unidos(v, w)) { // O(log*V )
                cjtos.unir(v, w); // O((V - 1) * log*V)
                _arm.push_back(a);
                
                costeMax = max(a.valor(), costeMax);

                if (_arm.size() == g.V() - 1) break;
            }
        }
    }

    int maxCoste() const {
        return costeMax;
    }

    std::vector<Arista<int>> arm() const {
        return _arm;
    }

private:
    std::vector<Arista<int>> _arm;
    int costeMax;
};

void resuelveCaso()
{
    int N, M;
    cin >> N >> M;

    GrafoValorado<int> g(N);

    int a, b, c;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;

        g.ponArista({a - 1, b - 1, c});
    }

    ARM res(g);

    if (res.arm().size() == g.V() - 1) {
        cout << res.maxCoste() << '\n';
    }
    else
        cout << "IMPOSIBLE\n";
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
