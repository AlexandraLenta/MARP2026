/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 * MARP71 Zhiyi Zhou
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "GrafoValorado.h"
#include "IndexPQ.h"
#include <list>
#include <limits>
using namespace std;

/*@ <answer>

En este problema se pide hallar el coste del camino con coste menor posible que une las tres localidades: las dos aldeas y el pueblo.

Se puede plantear como un grafo valorado, con los lugares de comarca como nodos y los tramos que los une como aristas y el coste 
para despejar cada tramo como coste de la arista correspondiente. El grafo es no dirigido, ya que un camino se puede recorrer en 
los dos sentidos.

Para hallar el coste minimo total, tenemos que encontrar el punto de encuentro entre las tres localidades, asi que utilizamos el
algoritmo de Dijkstra con origen en cada uno de los nodos.

Luego con un bucle for cogemos cada uno de los nodos (localidades) y probamos que coste tendría la ruta si ese nodo fuera 
el punto de encuentro. Elegimos la ruta con coste minimo. Como no se pide detallar el punto de encuentro o la ruta completa
elegida, solo imprimimos el coste minimo. 

Complejidad: O(3 * AlogV + V), siendo V el numero de lugares de comarca, y A el numero total de tramos que los une, ya que 
ejecutamos Dijkstra (O(A*log V)) para la aldea 1, aldea 2, y el pueblo (3 veces), y luego hacemos un bucle que recorre todos
los nodos (O(V)).

 @ </answer> */


 //@ <answer>

class Dijkstra
{
public:
	Dijkstra(GrafoValorado<int> const& g, int orig) : origen(orig),
		dist(g.V(), INF), ulti(g.V()), pq(g.V())
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
	void relajar(Arista<int> a, int v)
	{
		int w = a.otro(v);

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

	// leer los datos de la entrada
	int N, C, aldea1, aldea2, pueblo;
	cin >> N >> C >> aldea1 >> aldea2 >> pueblo;
	aldea1--; aldea2--; pueblo--;

	GrafoValorado<int> g(N);

	int a, b, c;
	for (int i = 0; i < C; i++)
	{
		cin >> a >> b >> c;
		g.ponArista({ a - 1, b - 1, c });
	}

	Dijkstra d1(g, aldea1);
	Dijkstra d2(g, aldea2);
	Dijkstra d3(g, pueblo);

	int minim = std::numeric_limits<int>::max();
	for (int i = 0; i < g.V(); i++) {
		minim = min(minim, d1.distancia(i) + d2.distancia(i) + d3.distancia(i));
	}

	cout << minim << '\n';
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main()
{
	// entrada/salida rápida
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// ajustes para que cin extraiga directamente de un fichero (solamente en local)
// #ifndef DOMJUDGE
//     ifstream in("casos.txt");
//     if (!in.is_open())
//     {
//         cout << "Error: no se ha podido abrir el archivo de entrada." << endl;
//         // sin fichero no hay nada que leer, y cin >> ... dejaría las
//         // variables sin tocar, con su valor basura
//         return 1;
//     }
//     cin.rdbuf(in.rdbuf());
// #endif

	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	return 0;
}
