// DG, Mario Calvarro Marines

#include <cstddef>
#include <iostream>
#include <fstream>
#include <vector>

using Adyacentes = std::vector<size_t>;

size_t dfs (const std::vector<Adyacentes> &grafo, const size_t k, const size_t original, std::vector<int> &marcados)
{
    size_t sol = 1;
    
    //Ponemos todos en la componente conexa del original
    marcados[k] = original;
    for (size_t i = 0; i < grafo[k].size(); ++i) 
    {
        if(marcados[grafo[k][i]] == -1)
        {
            sol += dfs(grafo, grafo[k][i], original, marcados);
        }
    }
    return sol;
}

bool resuelveCaso() 
{
    //Leer
    size_t N, M;
    std::cin >> N >> M;

    if (!std::cin)
        return false;

    std::vector<Adyacentes> grafo (N); 

    size_t tamGrupo, miembro1, miembro2;
    for (size_t i = 0; i < M; ++i)
    {
        std::cin >> tamGrupo;
        if (tamGrupo > 0) 
        {
            std::cin >> miembro1;
            for (size_t ii = 0; ii < tamGrupo - 1; ++ii)
            {
                std::cin >> miembro2;
                grafo[miembro1 - 1].push_back(miembro2 - 1);
                grafo[miembro2 - 1].push_back(miembro1 - 1);
                miembro1 = miembro2;
            }
        }  
    }
    
    std::vector<int> marcados(N, -1);
    std::vector<size_t> soluciones(N);

    //Escribir
    for(size_t i = 0; i < N; ++i)
    {
        if(marcados[i] == -1) 
        {
            //DFS: pone en marcados la posición de i 
            //porque todos los elementos de la misma
            //componente conexa tienen el mismo valor
            size_t sol = dfs(grafo, i, i, marcados);
            soluciones[i] = sol;
        }
        std::cout << soluciones[marcados[i]] << ' ';
    }

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
