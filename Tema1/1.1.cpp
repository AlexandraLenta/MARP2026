/*@ <authors>
 *
 * MARP86 Nombre Apellidos
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;

#include "bintree.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo
// ================================================================
//@ <answer>

template <typename T>
struct Info {
   bool is_valid;
   int height;
   T minimum;
   T maximum;
};

template <typename T> 
Info<T> solve(const BinTree<T>& tree) {
   if (tree.empty()) {
      return {true, 0, T{}, T{}};
   }

   BinTree<T> leftT = tree.left();
   BinTree<T> rightT = tree.right();

   Info<T> left = solve(leftT);

   if (!left.is_valid) {
      return {false, 0, T{}, T{}};
   }

   Info<T> right = solve(rightT);

   if (!right.is_valid) {
      return {false, 0, T{}, T{}};
   }

   if (!leftT.empty() && left.maximum >= tree.root()) {
      return {false, 0, T{}, T{}};
   }

   if (!rightT.empty() && right.minimum <= tree.root()) {
      return {false, 0, T{}, T{}};
   }


   if (abs(left.height - right.height) > 1) {
      return {false, 0, T{}, T{}};
   }
   
   // calcular altura
   int height = max(left.height, right.height) + 1;

   T min = tree.root();
   T max = tree.root();

   if (!leftT.empty()) {
      min = left.minimum;
   }

   if (!rightT.empty()) {
      max = right.maximum;
   }

   return {true, height, min, max};
}

bool resuelveCaso() {
   char c;
   std::cin >> c;

   if (!std::cin)  // fin de la entrada
      return false;
   
   bool is_avl;

   if (c == 'N') {
      BinTree tree = read_tree<int>(std::cin);
      is_avl = solve(tree).is_valid;
   }
   else if (c == 'P') {
      BinTree tree = read_tree<string>(std::cin);
      is_avl = solve(tree).is_valid;
   }


   // escribir la solución

   if (is_avl) {
      std::cout << "SI" << std::endl;
   }
   else {
      std::cout << "NO" << std::endl;
   }

   return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("casos.txt");
   if (!in.is_open())
      cout << "Error: no se ha podido abrir el archivo de entrada." << std::endl;
   auto cinbuf = cin.rdbuf(in.rdbuf());
#endif

   while (resuelveCaso());

   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
#endif
   return 0;
}
