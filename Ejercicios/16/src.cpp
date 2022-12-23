// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <vector>

using Adyacentes = std::vector<size_t>;

size_t dfs(const std::vector<Adyacentes> &grafo, const std::vector<size_t> &oros, const size_t k, std::vector<bool> &marcados)
{
    size_t res = oros[k];
    marcados[k] = true;
    for (auto personaje : grafo[k])
    {
        if (!marcados[personaje])
        {
            res = std::min(res, dfs(grafo, oros, personaje, marcados));
        }
    }
    return res;
}

bool resuelveCaso() 
{
    //Leer
    size_t N, M;
    std::cin >> N >> M;

    if (!std::cin)
        return false;

    std::vector<size_t> oro_pedido(N);
    for(auto &oro : oro_pedido)
        std::cin >> oro;

    std::vector<Adyacentes> grafo(N);
    size_t primero, segundo;
    for (size_t i = 0; i < M; ++i)
    {
        std::cin >> primero >> segundo;
        --primero; --segundo;
        grafo[primero].push_back(segundo);
        grafo[segundo].push_back(primero);
    }

    std::vector<bool> marcados(N, false);
    size_t sol = 0;
    for (size_t i = 0; i < N; ++i)
    {
        if (!marcados[i])
        {
            sol += dfs(grafo, oro_pedido, i, marcados);
        }
    }

    std::cout << sol << '\n';

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
