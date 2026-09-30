/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include "Grafo.h"
#include <vector>
#include <queue>
using namespace std;

using Map = vector<string>;

class Manchas
{
public:
    Manchas(Map const &m) : F(m.size()), C(m[0].size()), nrManchas(0), maxim(0)
    {
        visitados = vector<vector<bool>>(F, vector<bool>(C, false));

        for (int i = 0; i < F; i++)
        {
            for (int j = 0; j < C; j++)
            {
                if (!visitados[i][j] && m[i][j] == '#')
                { // si es un principio de mancha
                    nrManchas++;
                    int tam = dfs(m, i, j);
                    maxim = max(maxim, tam);
                }
            }
        }
    }

    int maximo()
    {
        return maxim;
    }

    int manchas()
    {
        return nrManchas;
    }

private:
    vector<vector<bool>> visitados;
    int maxim;
    int nrManchas;
    int F;
    int C;

    const vector<pair<int, int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    int dfs(Map const &m, int i, int j)
    {
        visitados[i][j] = true;
        int tam = 1;

        for (auto d : dirs)
        {
            int ni = i + d.first, nj = j + d.second;
            if (valido(ni, nj) && m[ni][nj] == '#' && !visitados[ni][nj]) {
                tam += dfs(m, ni, nj);
            }
        }

        return tam;
    }

    bool valido(int i, int j)
    {
        return 0 <= i && i < F && 0 <= j && j < C;
    }
};

void resuelveCaso()
{

    int n, m;
    cin >> n >> m;

    Map map(n);

    for (string& line : map) {
        cin >> line;
    }

    Manchas man = Manchas(map);

    cout << man.manchas() << ' ' << man.maximo() << '\n';
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main()
{
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    ifstream in("casos.txt");
    if (!in.is_open())
        cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
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
