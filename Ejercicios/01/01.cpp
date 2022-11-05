// Mario Calvarro Marines. MARP I. DG
//
// Resolvemos recursivamente el ejercicio:
//
// CB: Si el árbol es vacío, directamente es AVL.
//     Si el árbol no tiene hijos es AVL, el mín y máx son la raíz y la altura es 1.
//
// CR: Si falta un hijo (der. o izq.) se comprueba recursivamente el otro.
//     Si tiene los dos hijos se realiza la recursión sobre los dos y nos queda que 
//     - Será AVL si: lo son ambos hijos, la diferencia de alturas entre ellos es como mucho 1
//       y si izqMax < root < derMin.
//     - El mín. será el mín. de la izq. (si no fuese así no sería AVL por lo que daría igual)
//     - El máx. será el máx. de la der. (si no fuese así no sería AVL por lo que daría igual)
//     - La altura será el máx. entre las de los hijos más 1 por la raíz.
//
// Coste: O(n) al ejecutarse operaciones de coste constante sobre todos los elementos del 
//        árbol. (n nº de elementos del árbol).
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <tuple>

#include "bintree.h"

//Equilibrado, min, max, altura
template<typename T>
std::tuple<bool, T, T, size_t> AVL(const BinTree<T>& tree) {
    if (tree.left().empty() && tree.right().empty()) {
        return {true, tree.root(), tree.root(), 1};
    }
    else if (tree.left().empty()) {
        auto [derAVL, derMin, derMax, derAltura] = AVL(tree.right());

        bool resAVL = derAVL && derAltura <= 1 && tree.root() < derMin;
        return {resAVL, tree.root(), derMax, derAltura + 1};
    }
    else if (tree.right().empty()) {
        auto [izqAVL, izqMin, izqMax, izqAltura] = AVL(tree.left());

        bool resAVL = izqAVL && izqAltura <= 1 && tree.root() > izqMax;
        return {resAVL, izqMin, tree.root(), izqAltura + 1};
    }
    else {
        auto [izqAVL, izqMin, izqMax, izqAltura] = AVL(tree.left());
        auto [derAVL, derMin, derMax, derAltura] = AVL(tree.right());

        bool resAVL = izqAVL && derAVL &&
                    1 >= std::abs((int)izqAltura - (int)derAltura) &&
                    izqMax < tree.root() && tree.root() < derMin;

        return {resAVL, izqMin, derMax, std::max(izqAltura, derAltura) + 1};
    }
}

bool esAVL(const BinTree<int>& tree){
    if (tree.empty()) return true;

    return std::get<0>(AVL(tree));
} 

void resuelveCaso() {
    BinTree<int> tree = read_tree<int>(std::cin);

    bool res = esAVL(tree);

    std::cout << (res? "SI" : "NO") << '\n';
}

int main() {
    size_t numCasos;
    std::cin >> numCasos;

    for (size_t i = 0; i < numCasos; ++i){ 
        resuelveCaso();
    }

    return 0;
}
