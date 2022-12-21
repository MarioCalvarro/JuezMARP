// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>

#include "Grafo.h"

bool resolver(const Grafo& gr, const size_t k, const size_t anterior, std::vector<bool>& marcados) 
{
    bool res = true;
    marcados[k] = true;
    size_t i = 0;
    while(res && i < gr.ady(k).size())
    {
        if (anterior != gr.ady(k)[i])
        {
            if (marcados[gr.ady(k)[i]])
                return false;
            else 
                res &= resolver(gr, gr.ady(k)[i], k, marcados);
        }
        ++i;
    }
    return res;
}

bool resuelveCaso() 
{
    //Leer
    Grafo gr = Grafo(std::cin);
    std::vector<bool> marcados (gr.V());

    if (!std::cin)
        return false;

    //Escribir
    bool res = resolver(gr, 0, 0, marcados);
    size_t i = 0; 
    while (res && i < marcados.size())
    {
        res &= marcados[i];
        ++i;
    }   

    std::cout << (res? "SI" : "NO") << '\n';

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
