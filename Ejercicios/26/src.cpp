// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <queue>
#include <utility>
#include <bits/stdc++.h>

#include "DigrafoValorado.h"
#include "IndexPQ.h"

//Posible y tiempo total
std::pair<bool, size_t> resolver(const DigrafoValorado<size_t> &gr, const size_t carga_inicial) 
{
    std::vector<int> dist(gr.V(), INT_MAX);
    IndexPQ<size_t> pq(gr.V());
    pq.push(0, carga_inicial);
    dist[0] = carga_inicial;

    size_t aux;
    while(!pq.empty())
    {
        aux = pq.top().elem; pq.pop();

        for (auto e : gr.ady(aux))
        {
            auto v = e.desde(); auto w = e.hasta();
            
            if (dist[w] > dist[v] + e.valor())
            {
                dist[w] = dist[v] + e.valor();
                pq.update(w, dist[w]);
            }
        }
    }

    return {dist[gr.V() - 1] < INT_MAX, dist[gr.V() - 1]};
}

bool resuelveCaso() 
{
    //Leer
    size_t N; std::cin >> N;

    if (N == 0)
        return false;

    DigrafoValorado<size_t> gr(N);
    std::vector<size_t> tiempos_carga(N);
    for (auto &carga : tiempos_carga)
        std::cin >> carga;

    size_t M; std::cin >> M;
    size_t origen, destino, coste;
    for (size_t i = 0; i < M; ++i)
    {
        std::cin >> origen >> destino >> coste;
        --origen; --destino;
        AristaDirigida<size_t> e(origen, destino, coste + tiempos_carga[destino]);
        gr.ponArista(e);
    }

    //Escribir
    auto [posible, sol] = resolver(gr, tiempos_carga[0]);

    if(posible) 
        std::cout << sol << '\n';
    else 
        std::cout << "IMPOSIBLE\n";

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
