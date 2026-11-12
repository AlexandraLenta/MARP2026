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

Se pide el camino más corto desde un nodo (trabajo) a otro (casa), pasando necesariamente por un nodo
que contenga una farmacia. El tiempo de espera en esos nodos también cuenta hacia la distancia.
Solo se debe parar en 1 farmacia, en la que tenga menos tiempo de espera, aunque haya más farmacias 
en el camino.

Para resolver este problema, se puede utilizar el algoritmo de Dijkstra, dos veces, una con el origen
en el nodo "trabajo" y otra vez con el grafo inverso y origen en el nodo "casa".

Así conseguimos el camino más corto desde ambos extremos hasta cada nodo. Luego miramos solo los nodos que 
tengan una farmacia, y sumamos la distancia desde el trabajo hasta ese nodo con la distancia desde la casa
hasta ese nodo, y finalmente con el tiempo de espera de ese nodo. Así, solo se cuenta una vez el tiempo de
espera, y solo se cuenta el tiempo de espera mínimo de entre todos los posibles.

El coste de tiempo del algoritmo es O(N + A * log(N)), donde N es el número de nodos y A el número de conexiones
entre los nodos. El algoritmo de Dijkstra se ejecuta dos veces, con complejidad O(A * log (N)), ya que inicializar 
los vectores es O(N) y se hace 1 vez por vector, construir la cola es O(N), y se hace una vez, y luego la operación
pop con coste O(log N) se hace N veces, y update con coste O(log N) se hace A veces. Por tanto, el coste sería
O(2*N + NlogN + AlogN), lo que se simplifica a O(A*log(N)). 
El bucle que recorre las farmacias para calcular la distancia mínima tiene como mucho coste O(N), si todos los
nodos son farmacias. 

Tras recorrer todos los nodos con farmacias así, nos quedamos con el valor del camino que menos tiempo lleva.

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
