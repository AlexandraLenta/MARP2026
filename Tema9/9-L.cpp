/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include "GrafoValorado.h"
#include "IndexPQ.h"
#include <vector>
#include <limits>
#include <algorithm>

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
    Dijkstra(GrafoValorado<long long> const &g, int orig) : origen(orig),
                                                      dist(g.V(), INF), pq(g.V())
    {
        dist[origen] = 0;
        pq.push(origen, 0);

        while (!pq.empty())
        {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v))
                relajar(a, v);
        }
    }

    bool hayCamino(int v) const { return dist[v] != INF; }

    long long distancia(int v) const { return dist[v]; }

private:
    const long long INF = std::numeric_limits<long long>::max();
    int origen;
    std::vector<long long> dist;
    IndexPQ<long long> pq;

    void relajar(Arista<long long> a, int v)
    {
        int w = a.otro(v);

        if (dist[w] > dist[v] + a.valor())
        {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }
};

void resuelveCaso()
{
    int N, M;
    cin >> N >> M;

    int a, b, c;
    GrafoValorado<long long> g(N);

    for (int i = 0; i < M; i++)
    {
        cin >> a >> b >> c;
        g.ponArista({a - 1, b - 1, c});
    }

    Dijkstra d1(g, 0);
    Dijkstra d2(g, N - 1);

    // distancia al norte y al sur de cada nodo
    vector<pair<long long, long long>> v;

    for (int i = 1; i < N - 1; i++)
    {
        v.push_back({d1.distancia(i), d2.distancia(i)});
    }

    // sort segun la diferencia
    sort(v.begin(), v.end(), [](const pair<long long, long long> d1, const pair<long long, long long> d2)
         { return d1.first - d1.second < d2.first - d2.second; });

    int mitad = v.size() / 2;
    long long sum = 0;
    for (int i = 0; i < (int)v.size(); i++)
        sum += (i < mitad) ? v[i].first : v[i].second;

    cout << sum * 2 << '\n';
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
