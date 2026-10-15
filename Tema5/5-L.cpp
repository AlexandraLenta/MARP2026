/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

/*@ <answer>

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

class DFS
{
public:
    DFS(vector<pair<char, int>> const &vec) : vec(vec), visited(vec.size(), false), queued(vec.size(), false)
    {
        dfs(vec, 1, vec.size());
    }

    bool end()
    {
        return reachedEnd;
    }

    bool cycle()
    {
        return isCycle;
    }

private:
    vector<pair<char, int>> const &vec;
    vector<bool> visited;
    bool isCycle = false;
    vector<bool> queued;
    bool reachedEnd = false;

    void dfs(vector<pair<char, int>> const &vec, int v, int destino)
    {
        visited[v] = true;
        queued[v] = true;

        if (vec[v].second == destino)
        {
            reachedEnd = true;
            return;
        }

        if (vec[v].first == 'C')
        {
            if (!visited[v + 1])
                dfs(vec, v + 1, destino);
            else if (queued[v + 1])
            {
                isCycle = true;
            }
        }

        if (!visited[vec[v].second])
            dfs(vec, vec[v].second, destino);
        else if (queued[vec[v].second])
            isCycle = true;

        queued[v] = false;
    }
};

void resuelveCaso()
{

    int L;
    cin >> L;

    char instr;
    int n;

    vector<pair<char, int>> vec(L + 2);
    vec[0] = {'x', 1};

    for (int i = 1; i <= L; i++)
    {
        cin >> instr;
        if (instr == 'C' || instr == 'J')
        {
            cin >> n;
            vec[i] = {instr, n};
        }
        else if (instr == 'A')
        {
            vec[i] = {instr, i + 1};
        }
    }

    vec[L + 1] = {'x', L + 2};

    DFS res(vec);

    if (res.cycle() && res.end())
    {
        cout << "A VECES\n";
    }
    else if (res.cycle() && !res.end())
        cout << "NUNCA\n";
    else if (!res.cycle() && res.end())
        cout << "SIEMPRE\n";
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main()
{
    // ajustes para que cin extraiga directamente de un fichero
    // #ifndef DOMJUDGE
    //     ifstream in("casos.txt");
    //     if (!in.is_open())
    //         cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
    //     auto cinbuf = cin.rdbuf(in.rdbuf());
    // #endif

    int numCasos;
    cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
    // #ifndef DOMJUDGE
    //     cin.rdbuf(cinbuf);
    // #endif
    return 0;
}
