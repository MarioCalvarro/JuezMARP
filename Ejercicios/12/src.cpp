// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <vector>

#include "Grafo.h"

size_t dfs(const Grafo &gr, const size_t k, std::vector<bool> &marcados) 
{
    size_t res = 1;
    marcados[k] = true;
    for (size_t i = 0; i < gr.ady(k).size(); ++i) 
    {
        if (!marcados[gr.ady(k)[i]]) 
            res += dfs(gr, gr.ady(k)[i], marcados);
    }
    return res;
}

size_t resolver(const Grafo &datos, std::vector<bool> &marcados)
{
    size_t auxAmigos, maxAmigos = 0;
    for (size_t i = 0; i < datos.V(); ++i) 
    {
        if(!marcados[i]) 
        {
            auxAmigos = dfs(datos, i, marcados);
            if (auxAmigos > maxAmigos) 
                maxAmigos = auxAmigos;
        }
    }
    return maxAmigos;
}

void resuelveCaso() 
{
    Grafo gr = Grafo(std::cin);
    std::vector<bool> marcados(gr.V(), false);

    std::cout << resolver(gr, marcados) << '\n';
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
