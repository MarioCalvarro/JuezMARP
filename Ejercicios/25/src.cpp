// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"

//Coste mínimo y nº aeropuertos
std::pair<size_t, size_t> kruskal(const GrafoValorado<size_t> &gr, const size_t coste_aeropuerto,
    std::priority_queue<Arista<size_t>, std::vector<Arista<size_t>>, std::greater<Arista<size_t>>> minpq) 
{
    size_t coste = 0, aeropuertos = 0;
    std::queue<Arista<size_t>> mst;
    std::vector<bool> marcados(gr.V(), false);
    ConjuntosDisjuntos uf(gr.V());
   
    while(!minpq.empty() && mst.size() < gr.V() - 1)
    {
        auto e = minpq.top(); minpq.pop();
        auto v = e.uno(), w = e.otro(v);
        if (!uf.unidos(v, w))
        {
            if (!marcados[v] || !marcados[w])
            {
                //Si ambos son nuevos, construimos un aeropuerto en alguno
                if (!marcados[v] && !marcados[w]) {
                    ++aeropuertos; coste += coste_aeropuerto;
                }

                if (coste_aeropuerto <= e.valor()) {
                    ++aeropuertos; coste += coste_aeropuerto;
                } else {
                    coste += e.valor();
                }
            }
            else //Ambos ya marcados
            {
                //Si sobra un aeropuerto (tenemos uno por cada vértice), 
                //lo quitamos y construimos una carretera
                if (coste_aeropuerto > e.valor())
                {
                    --aeropuertos; coste -= coste_aeropuerto;
                    coste += e.valor();
                }
            }

            uf.unir(v, w);
            mst.push(e);
            marcados[v] = true;
            marcados[w] = true;
        }
    }

    for (auto pos : marcados)
    {
        //No hemos pasado por un sitio -> ponemos un aeropuerto
        if (!pos)
        {
            ++aeropuertos; coste += coste_aeropuerto;
        }
    }

    return {coste, aeropuertos};
}

bool resuelveCaso() 
{
    //Leer
    size_t N, M, A;
    std::cin >> N >> M >> A;

    if (!std::cin)
        return false;

    GrafoValorado<size_t> gr(N);
    std::priority_queue<Arista<size_t>, std::vector<Arista<size_t>>, std::greater<Arista<size_t>>> minpq;

    size_t origen, destino, coste;
    for (size_t i = 0; i < M; ++i)
    {
        std::cin >> origen >> destino >> coste;
        --origen; --destino;
        Arista<size_t> e(origen, destino, coste);
        gr.ponArista(e);
        minpq.push(e);
    }

    auto [pago, min_ae] = kruskal(gr, A, minpq);

    std::cout << pago << ' ' << min_ae << '\n';

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
