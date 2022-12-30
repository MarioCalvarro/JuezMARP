// DG, Mario Calvarro Marines

#include <functional>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"

std::pair<bool, size_t> kruskal(const GrafoValorado<size_t> &gr,
    std::priority_queue<Arista<size_t>, std::vector<Arista<size_t>>, std::greater<Arista<size_t>>> minq1)
{
    size_t coste = 0;
    std::queue<Arista<size_t>> mst;
    ConjuntosDisjuntos uf(gr.V());
    while(!minq1.empty() && mst.size() < gr.V() - 1)
    {
        Arista<size_t> e = minq1.top(); minq1.pop();
        size_t v = e.uno(), w = e.otro(v);
        if (!uf.unidos(v, w))
        {
            uf.unir(v, w);
            coste += e.valor();
            mst.push(e);
        }
    }

    if(mst.size() < gr.V() - 1)
        return {false, 0};
    else 
        return {true, coste};
}

bool resuelveCaso() 
{
    //Leer
    size_t V, A; std::cin >> V >> A;

    if (!std::cin)
        return false;

    GrafoValorado<size_t> gr(V); size_t origen, destino, valor;
    std::priority_queue<Arista<size_t>, std::vector<Arista<size_t>>, std::greater<Arista<size_t>>> minq1;
    for (size_t i = 0; i < A; ++i)
    {
        std::cin >> origen >> destino >> valor;
        Arista<size_t> e(origen - 1, destino - 1, valor);
        gr.ponArista(e);
        minq1.push(e);
    }

    auto [posible, coste] = kruskal(gr, minq1);

    if (posible) 
        std::cout << coste;
    else 
        std::cout << "No hay puentes suficientes";

    std::cout << '\n';

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
