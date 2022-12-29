// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

size_t resolver(const size_t V, const std::vector<size_t> &pilas) 
{
    size_t sol = 0;
    size_t i = 0, j = pilas.size() - 1;

    while (i < j)
    {
        if (pilas[i] + pilas[j] >= V)
        {
            ++i; --j; ++sol;
        }
        else 
            ++i;
    }
    
    return sol;
}

void resuelveCaso() 
{
    //Leer
    size_t N, V;
    std::cin >> N >> V;

    std::vector<size_t> pilas(N);

    for (auto &pila : pilas)
        std::cin >> pila;
    
    std::sort(pilas.begin(), pilas.end());

    //Escribir
    std::cout << resolver(V, pilas) << '\n';
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (size_t i = 0; i < numCasos; ++i) 
        resuelveCaso();

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#endif

    return 0;
}
