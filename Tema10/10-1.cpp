/*@ <authors>
 *
 * MARP39 Alexandra Lenta
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
using namespace std;
#include <vector>

const int MODULO = 1000000007;

//@ <answer>

// filas (i): tipo de sellos que tenemos
// columnas (j): la cantidad a sumar

// CASOS BASE:
// sellos[i][j] = numero de formas de sumar exactamente j, usando los primeros i tipos de sellos
// sellos[0][0] = 1 - una forma de sumar 0, utilizando 0 sellos
// sellos[i][0] = 1 - una forma de sumar 0, es no pegar nada
// sellos[0][j] = 0 - no se puede sumar j con 0 sellos (j > 0)

// CASOS DE RECURRENCIA
// 1 : no puedo usar ningun sello de tipo i  -> uso solo los de tipo i - 1
// 2 : puedo usar al menos un sello de tipo i -> uso 1 de tipo i, me queda por sumar la cantidad j - valor[i - 1], con el mismo tipo de sellos + sumar las formas que podiamos pagar con los tipos anteriores

// Pasar a unidimensional: sellos[j] siempre va a contener el valor sellos[i - 1][j] del array bidimensional, es decir, va a tener el nr de formas de sumar j con los sellos i - 1,
// porque ya hemos actualizado el vector entero para i - 1. empieza en 0, ya que hay 0 formas de sumar cualquier cantidad utilizando ningun sello, y va construyendo sobre eso.
// ya no tenemos que comprobar si se puede utiliar el tipo i, porque empezamos el segundo bucle en valor[i - 1], lo que significa que solo vamos a mirar desde la cantidad que
// se puede pagar. a esa cantidad sellos[i - 1][j], le sumamos las maneras en las que sumamos la cantidad j - valor[i - 1].

// Para la reconstruccion, no se puede usar sellos, ya que no hay manera de saber si hay solucion o no, porque si hacemos el modulo de la suma con 10^9 + 7, nos podria dar 0.
// ultimo[j] = el valor de un sello con el que se pudo alcanzar j por primera vez

vector<int> devolverCombinaciones(int C, vector<int> const& valor, int& formas) {
    int n = valor.size();

    vector<int> sellos1D(C + 1, 0);

    vector<int> ultimo(C + 1, -1); 

    sellos1D[0] = 1; // una forma de sumar 0: ningun sello
    ultimo[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = valor[i - 1]; j <= C; j++) {
            sellos1D[j] = (sellos1D[j - valor[i - 1]] + sellos1D[j]) % MODULO;

            // si j - valor[i - 1] se pudo alcanzar ya, entonces j se puede alcanzar tambien, con un sello de valor[i - 1]
            if (ultimo[j - valor[i - 1]] != -1) {
                ultimo[j] = valor[i - 1];
            }
        }
    }

    formas = sellos1D[C];

    vector<int> sol;
    if (ultimo[C] != -1) {
        int i = n, j = C;

        while (j > 0) {
            sol.push_back(ultimo[j]);
            j = j - ultimo[j];
        }
    }

    return sol;
}

void resuelveCaso()
{
    int N, T;
    cin >> N >> T;

    vector<int> sellos(N);

    int a;
    for (int i = 0; i < N; i++) {
        cin >> a;
        sellos[i] = a;
    }

    int formas;
    vector<int> sol = devolverCombinaciones(T, sellos, formas);

    cout << formas << '\n';

    if (sol.empty()) {
        cout << "NO HAY\n";
        return;
    }
    
    for (auto& i : sol) {
        cout << i << ' ';
    }
    cout << '\n';
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
