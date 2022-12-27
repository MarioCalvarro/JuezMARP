// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <utility>

#include "Digrafo.h"

std::pair<bool, size_t> resolver(const Digrafo &gr) 
{
    std::vector<size_t> aristas_entrada (gr.V());

    for (size_t i = 0; i < gr.V(); ++i) 
    {
        for(auto ite : gr.ady(i)) 
            ++aristas_entrada[ite];
    }

    for (size_t i = 0; i < aristas_entrada.size(); ++i)
    {
        if (gr.ady(i).size() == 0 && aristas_entrada[i] == (gr.V() - 1))
            return {true, i};
    }

    return {false, 0};
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
        std::cout << "SI " << res << '\n';
    else 
        std::cout << "NO\n";

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
