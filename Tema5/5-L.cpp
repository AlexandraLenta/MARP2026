/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 * MARP71 Zhiyi Zhou
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

/*@ <answer>
Complejidad: O(V + E), donde V es el numero de instrucciones y E es el numero total de conexiones entre las instrucciones. 
Para cada instruccion, puede haber 1 o 2 aristas.

En este problema, se trata de un grafo dirigido, ya que de una instrucción solo 
se puede pasar a la siguiente indicada, en una dirección.

Podemos construir el grafo de manera implícita, como un vector de pares <char, int>,
donde el char es el tipo de instruccion (A, J, o C), y el int es la siguiente instruccion 
a ejecutar.

Leemos las instrucciones y las metemos en el vector. Si la instruccion es una A, 
la siguiente es la siguiente en el orden (i + 1). Si es J o C, la siguiente 
instruccion será la indicada a continuación.

Como las instrucciones en el input se enumeran desde 1 a L (siendo L el número total de instr.),
hemos decidido meter una instruccón de relleno en la posición 0, para mantener esos números.
También metemos una instrucción después de la última del input, que consideramos la 
instrucción final, ya que en el enunciado se especifica que el programa tiene que terminar la 
última instrucción indicada.

El problema se puede resolver mediante un DFS, ya que estamos buscando un camino hasta el destino,
que sería la instrucción final que hemos metido en el vector.

Las tres posibles soluciones son "SIEMPRE", "A VECES", y "NUNCA". 
"SIEMPRE" termina el programa cuando no hay ciclos y hemos llegado al final, es decir, cuando
llegar al final no depende de una instrucción condicional.

"A VECES" termina el programa cuando hay ciclos pero hemos conseguido llegar al final, lo que
significa que depende de una instrucción conidiconal.

"NUNCA" termina el programa cuando hay ciclos y no se puede llegar al final, lo que significa 
que independientemente de alguna condición, el programa nunca termina de ejecutar.

Sabiendo esto, en el dfs, queremos ver si hay ciclos y si hemos llegado al destino, por lo que
utilizamos los vectores visited y queued. No queremos parar cuando encontramos un ciclo, ya que
aún así podriamos conseguir llegar al final. Tampoco queremos parar la busqueda si llegamos al
destino, porque podría haber un ciclo en un camino no explorado y eso significaría que el 
programa se ejecuta "A VECES" en vez de "SIEMPRE".

Empezamos en el nodo 1 del grafo.


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
