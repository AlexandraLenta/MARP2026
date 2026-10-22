/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include <vector>
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"
using namespace std;

/*@ <answer>

 Complejidad: O(A*log A)

 En este problema se pide averiguar la forma más barata de 
 construir aeropuertos y carreteras que conecten todas las localidades,
 con una condición: a cada localidad se debe poder llegar desde un aeropuerto 
 (ya sea por carretera desde la localidad con el aeropuerto o desde el aeropuerto).

 Vamos a utilizar un el algoritmo de Kruksal para construir el árbol 
 de recubrimiento mínimo sobre el grafo que creamos a partir de las 
 carreteras.

 Empezamos con 0 aeropuertos y un coste total 0.

 Recorremos las aristas en orden ascendiente de su valor. 
 Para cada arista, si su coste es menor que el de construir un aeropuerto,
 construimos la carretera en vez del aeropuerto (sumamos su coste al total).
 Si el valor de la arista es mayor que el coste del aeropuerto, nos saldría 
 más barato construir el aeropuerto en vez de la arista, así que sumamos
 al total el coste del aeropuerto y añadimos un aeropuerto al contador. 
 No se piden las localidades donde construimos los aeropuertos, así que no
 guardamos ese dato.
 
 Después de haber visitado todas las aristas, la clase ConjuntosDisjuntos
 contiene todas las componentes conexas del grafo. Cada componente tiene que
 tener al menos un aeropuerto, y las variables costeTotal y aeropuertos solo  
 han tenido en cuenta los aeropuertos construidos en los casos en que ha sido
 más barato construir uno en vez de una carretera. Por eso, por cada conjunto 
 dentro de los ConjuntosDisjuntos, añadimos un aeropuerto y sumamos el coste de esos 
 al coste total.

 @ </answer> */

//@ <answer>

class Solution
{
public:
    Solution(GrafoValorado<int> const &g, int costeAeropuerto) : costeTotal(0), aeropuertos(0)
    {
        PriorityQueue<Arista<int>> pq(g.aristas());

        ConjuntosDisjuntos cjtos(g.V());

        while (!pq.empty())
        {
            auto a = pq.top();
            pq.pop();

            int v = a.uno();
            int u = a.otro(v);

            if (!cjtos.unidos(v, u))
            {
                cjtos.unir(v, u);

                arm.push_back(a);

                if (a.valor() < costeAeropuerto)
                {

                    costeTotal += a.valor();
                }
                else
                {
                    costeTotal += costeAeropuerto;
                    aeropuertos++;
                }

                if (arm.size() == g.V() - 1)
                    break;
            }
        }

        aeropuertos += cjtos.num_cjtos();
        costeTotal += cjtos.num_cjtos() * costeAeropuerto;
    }

    int coste() {
        return costeTotal;
    }

    int numAeropuertos() {
        return aeropuertos;
    }

private:
    vector<Arista<int>> arm;
    int costeTotal;
    int aeropuertos;
};

void resuelveCaso()
{

    int N, M, A;

    cin >> N >> M >> A;

    GrafoValorado<int> g(N);

    int x, y, c;
    for (int i = 0; i < M; i++)
    {
        cin >> x >> y >> c;
        g.ponArista({x - 1, y - 1, c});
    }

    Solution sol(g, A);

    cout << sol.coste() << ' ' << sol.numAeropuertos() << '\n';
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
