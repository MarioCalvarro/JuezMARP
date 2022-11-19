// DG, Mario Calvarro Marines
//
// Solución:
// Explicación en los lugares donde se ha modificado código de TreeSet_AVL

#include <iostream>
#include <fstream>
#include <stdexcept>

#include "TreeSet_AVL.h"

bool resuelveCaso() 
{
    //Leer
    size_t N;
    std::cin >> N;

    if (N == 0)
        return false;

    Set<size_t> conjunto; 
    size_t el;

    for (size_t i = 0; i < N; ++i){
        std::cin >> el; 
        conjunto.insert(el); 
    }

    size_t M, consulta;
    std::cin >> M;
    for (size_t i = 0; i < M; ++i)
    {
        std::cin >> consulta;
        try {
            std::cout << conjunto.kesimo(consulta) << '\n';
        } catch(std::domain_error e){
            std::cout << e.what() << '\n';
        }
    }

    std::cout << "---\n";

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while(resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
