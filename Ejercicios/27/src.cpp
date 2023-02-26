// DG, Mario Calvarro Marines

#include <climits>
#include <iostream>
#include <fstream>
#include <bits/stdc++.h>

#include "GrafoValorado.h"
#include "IndexPQ.h"

std::pair<size_t, size_t> resolver(const GrafoValorado<size_t> &gr, const size_t origen, const size_t destino) 
{
    //Coste de viaje, nº de calles
    std::vector<std::pair<size_t, size_t>> distTo(gr.V(), {INT_MAX, INT_MAX});
    IndexPQ<std::pair<size_t, size_t>> pq(gr.V());

    pq.push(origen, {0, 0});
    distTo[origen] = {0, 0};
    while(!pq.empty())
    {
        auto aux = pq.top().elem; pq.pop();

        for (auto e : gr.ady(aux))
        {
            auto v = aux; auto w = e.otro(v);

            //Si el valor es menor o si el valor es el mismo, pero con un paso menos
            if (distTo[w].first > distTo[v].first + e.valor() ||
                (distTo[w].first == distTo[v].first + e.valor() && distTo[w].second > distTo[v].second + 1))
            {
                distTo[w] = {distTo[v].first + e.valor(), distTo[v].second + 1};
                pq.update(w, distTo[w]);
            }
        }
    }

    return distTo[destino];
}

bool resuelveCaso() 
{
    //Leer
    size_t N, C;
    std::cin >> N >> C;

    if (!std::cin)
        return false;

    GrafoValorado<size_t> gr(N);
    GrafoValorado<size_t> grUnos(N);

    size_t origen, destino, valor;
    for (size_t i = 0; i < C; ++i)
    {
        std::cin >> origen >> destino >> valor;
        --origen; --destino;
        Arista<size_t> e(origen, destino, valor);
        gr.ponArista(Arista<size_t> (origen, destino, valor));
        grUnos.ponArista(Arista<size_t> (origen, destino, 1));
    }

    size_t K; std::cin >> K;
    for (size_t i = 0; i < K; ++i)
    {
        std::cin >> origen >> destino;
        --origen; --destino;

        auto [coste_camino, calles_camino] = resolver(gr, origen, destino);
        if (coste_camino == INT_MAX) std::cout << "SIN CAMINO\n";
        else 
        {
            std::cout << coste_camino << ' ';
            auto [calles_min, nada] = resolver(grUnos, origen, destino);

            if (calles_camino == calles_min) std::cout << "SI\n";
            else std::cout << "NO\n";
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
