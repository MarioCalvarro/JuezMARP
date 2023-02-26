// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <vector>

#include "DigrafoValorado.h"
#include "IndexPQ.h"

void dijkstra(const DigrafoValorado<size_t> &gr, const size_t origen, 
        std::vector<size_t> &distTo) 
{
    IndexPQ<size_t> pq(gr.V());

    pq.push(origen, 0);
    distTo[origen] = 0;
    while(!pq.empty())
    {
        auto aux = pq.top().elem; pq.pop();

        for (auto e : gr.ady(aux))
        {
            auto v = e.desde(); auto w = e.hasta();
            if (distTo[w] > distTo[v] + e.valor())
            {
                distTo[w] = distTo[v] + e.valor();
                pq.update(w, distTo[w]);
            }
        }
    }

    return;
}

bool resuelveCaso() 
{
    //Leer
    size_t N, S, T, P;
    std::cin >> N >> S >> T >> P; --S;

    if (!std::cin)
        return false;

    DigrafoValorado<size_t> gr(N);
    size_t origen, destino, valor;
    for (size_t i = 0; i < P; ++i)
    {
        std::cin >> origen >> destino >> valor;
        --origen; --destino;
        gr.ponArista(AristaDirigida<size_t>(origen, destino, valor));
    }

    size_t count = 0;
    std::vector<size_t> distTo(gr.V(), INT_MAX);
    dijkstra(gr.inverso(), S, distTo);
    for (size_t i = 0; i < N; ++i)
    {
        if (i != S && distTo[i] <= T)
            ++count;
    }

    std::cout << count << '\n';

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
