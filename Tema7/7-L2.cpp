/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include "DigrafoValorado.h"
#include <vector>
#include "IndexPQ.h"
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
    Dijkstra(DigrafoValorado<int> const &g, int orig) : origen(orig),
                                                       dist(g.V(), INF), pq(g.V())
    {
        dist[origen] = 0;
        pq.push(origen, 0);

        while (!pq.empty())
        {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    bool hayCamino(int v) const { return dist[v] != INF; }

    int distancia(int v) const { return dist[v]; }

private:
    const int INF = std::numeric_limits<int>::max();
    int origen;
    std::vector<int> dist;
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a)
    {
        int v = a.desde(), w = a.hasta();
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

    int n, m;
    cin >> n >> m;

    int a, b, c;
    DigrafoValorado<int> g(N);

    for (int i = 0; i < M; i++)
    {
        cin >> a >> b >> c;
        g.ponArista({a - 1, b - 1, c});
    }

    int F;
    cin >> F;

    // cruce -- minutos
    vector<int> minutosParar(N, -1);

    for (int i = 0; i < F; i++)
    {
        cin >> a >> b;

        minutosParar[a - 1] = b;
    }

    Dijkstra d1(g, n - 1);
    Dijkstra d2(g.inverso(), m - 1);

    int minim = std::numeric_limits<int>::max();
    for (int i = 0; i < g.V(); i++)
    {
        if (minutosParar[i] != -1)
        {
            if (d1.hayCamino(i) && d2.hayCamino(i))
                minim = min(minim, d1.distancia(i) + d2.distancia(i) + minutosParar[i]);
        }
    }

    if (minim != std::numeric_limits<int>::max()) {
        cout << minim << '\n';
    }
    else {
        cout << "IMPOSIBLE\n";
    }
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
