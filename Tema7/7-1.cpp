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
#include "ConjuntosDisjuntos.h"
#include <list>
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
    Dijkstra(GrafoValorado<int> const &g, int orig) : origen(orig),
                                                      dist(g.V(), INF), ulti(g.V()), pq(g.V())
    {
        dist[origen] = 0;
        pq.push(origen, 0);
        ConjuntosDisjuntos cjtos(g.V());

        while (!pq.empty())
        {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v))
                relajar(a, v);
        }
    }

    bool hayCamino(int v) const { return dist[v] != INF; }

    int distancia(int v) const { return dist[v]; }

    list<int> camino(int v) const
    {
        list<int> cam;

        // recuperamos el camino retrocediendo
        Arista<int> a;

        int uno = v;

        for (a = ulti[v]; uno != origen; a = ulti[uno]) {
            cam.push_front(uno);
            uno = a.otro(uno);
        }

        cam.push_front(uno);

        return cam;
    }

private:
    const int INF = std::numeric_limits<int>::max();
    int origen;
    std::vector<int> dist;
    std::vector<Arista<int>> ulti;
    IndexPQ<int> pq;

    void relajar(Arista<int> a, int uno)
    {
        int v = uno, w = a.otro(v);
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
    int N, C;
    cin >> N >> C;

    GrafoValorado<int> g(N);

    int a, b, c;
    for (int i = 0; i < C; i++)
    {
        cin >> a >> b >> c;

        g.ponArista({a - 1, b - 1, c});
    }

    int K;
    cin >> K;

    for (int i = 0; i < K; i++)
    {
        cin >> a >> b;
        Dijkstra d(g, a - 1);
        if (d.hayCamino(b - 1))
        {
            cout << d.distancia(b - 1) << ": ";
            auto camino = d.camino(b - 1);
            a = camino.front() + 1;
            camino.pop_front();

            while (!camino.empty()) {
                cout << a << " -> ";
                a = camino.front() + 1;
                camino.pop_front();
            }
            cout << a << '\n';
        }
        else
        {
            cout << "NO LLEGA\n";
        }
    }

    cout << "---\n";
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
