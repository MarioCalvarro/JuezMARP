// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <utility>

#include "Digrafo.h"

std::pair<bool, size_t> resolver(const Digrafo &gr) 
{
    std::vector<size_t> posibles_sumideros;
    for ()
    return {false, 1};
}

bool resuelveCaso() 
{
    //Leer
    Digrafo gr = Digrafo(std::cin);

    if (!std::cin)
        return false;

    auto [posible, res] = resolver(gr);

    //Escribir
    if (posible) 
    {
        std::cout << res << '\n';
    }
    else 
    {
        std::cout << "NO\n";
    }

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
