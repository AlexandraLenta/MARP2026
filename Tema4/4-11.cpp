/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <queue>

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

constexpr char WHITE = '.';

constexpr char BLACK = 'X';

class Solucion
{
public:
    Solucion(vector<string> const &g)
    {
        visitados = vector<vector<bool>>(g.size(), vector<bool>(g[0].size(), false));
        negrosVisitados = vector<vector<bool>>(g.size(), vector<bool>(g[0].size(), false));

        queue<pair<int, int>> q;
        
        q.push({0, 0}); // start in cell 0,0
        visitados[0][0] = true;

        while (!q.empty()) {
            auto v = q.front(); q.pop();
            int i = v.first, j = v.second;
            
            visitados[i][j] = true;

            for (auto d : dirs4) {
                int ni = i + d.first, nj = j + d.second;
                if (isValid(g, ni, nj) && !visitados[ni][nj] && g[ni][nj] == WHITE) {
                    visitados[ni][nj] = true;
                    q.push({ni, nj});
                }
            }
        }

        int F = g.size(), C = g[0].size();
        for (int i = 0; i < F; i++) {
            for (int j = 0; j < C; j++) {
                white = false;
                if (!negrosVisitados[i][j] && g[i][j] == BLACK) {
                    dfs(g, i, j);
                    if (white) whiteSheep++;
                }
            }
        }
    }

    int whiteNr() {
        return whiteSheep;
    }

private:
    vector<vector<bool>> visitados;
    vector<vector<bool>> negrosVisitados;
    bool white;
    int whiteSheep = 0;
    const vector<pair<int, int>> dirs4 = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    const vector<pair<int, int>> dirs8 = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};

    bool isValid(vector<string> const& g, int i, int j) {
        return i >= 0 && i < g.size() && j >= 0 && j < g[0].size();
    }

    void dfs(vector<string> const& g, int i, int j) {
        negrosVisitados[i][j] = true;

        for (auto d : dirs4) {
            int ni = i + d.first, nj = j + d.second;
            if (isValid(g, ni, nj) && g[ni][nj] == WHITE && !visitados[ni][nj]) {
                white = true;
                break;
            }
        }

        for (auto d : dirs8) {
            int ni = i + d.first, nj = j + d.second;
            if (isValid(g, ni, nj) && g[ni][nj] == BLACK && !negrosVisitados[ni][nj]) {
                dfs(g, ni, nj);
            }
        }
    }
};

void resuelveCaso()
{
    int W, H;
    cin >> W >> H;

    string line;
    vector<string> lines;

    for (int i = 0; i < H; i++)
    {
        cin >> line;
        lines.push_back(line);
    }

    Solucion sol(lines);

    cout << sol.whiteNr() << '\n';
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
