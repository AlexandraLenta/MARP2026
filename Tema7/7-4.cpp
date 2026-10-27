/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <limits>

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class Dijkstra
{
public:
    Dijkstra(DigrafoValorado<int> const &g, int origen, int limit) :
                                                       dist(g.V(), INF), ulti(g.V()), pq(g.V())
    {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty())
        {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v))
                relajar(a);

            if (dist[v] <= limit)
                count++;
        }

        count--; // no tenemos en cuenta el origen
    }

    int getCount() {
        return count; 
    }

private:
    const int INF = std::numeric_limits<int>::max();
    int origen;
    std::vector<int> dist;
    std::vector<AristaDirigida<int>> ulti;
    IndexPQ<int> pq;
    int count = 0;

    void relajar(AristaDirigida<int> a)
    {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor())
        {
            dist[w] = dist[v] + a.valor();
            ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
};

void resuelveCaso()
{
    int N, S, T, P;
    cin >> N >> S >> T >> P;

    DigrafoValorado<int> g(N);

    int a, b, t;
    for (int i = 0; i < P; i++)
    {
        cin >> a >> b >> t;
        g.ponArista({a - 1, b - 1, t});
    }

    Dijkstra d(g.inverso(), S - 1, T);

    cout << d.getCount() << '\n';
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
