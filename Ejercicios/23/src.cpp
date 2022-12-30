// DG, Mario Calvarro Marines

#include "GrafoValorado.h"
#include <iostream>
#include <fstream>

bool resolver(const GrafoValorado<size_t> &gr, std::vector<bool> &marcados,
        const size_t origen, const size_t destino, const size_t anchura) 
{
    bool res = false;
    marcados[origen] = true;

    if (origen == destino) res = true;
    else 
    {
        for(auto v : gr.ady(origen))
        {
            size_t w = v.otro(origen);
            if (!marcados[w] && v.valor() >= anchura)
                res |= resolver(gr, marcados, w, destino, anchura);
        }
    }

    return res;
}

bool resuelveCaso() 
{
    //Leer
    GrafoValorado<size_t> gr = GrafoValorado<size_t>(std::cin);

    if (!std::cin)
        return false;

    size_t n;
    size_t origen, destino, anchura;
    std::cin >> n;
    for (size_t i = 0; i < n; ++i)
    {
        std::vector<bool> marcados(gr.V(), false);
        std::cin >> origen >> destino >> anchura;
        --origen; --destino;
        std::cout << (resolver(gr, marcados, origen, destino, anchura)? "SI" : "NO") << '\n';
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
