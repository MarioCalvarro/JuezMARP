// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>

const std::pair<int, int> DIRECCIONES_POSIBLES[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}

// 0 agua, -1 mancha sin clasificar, i > 0 mancha en 
// la componente conexa i
using MatrizMar = std::vector<std::vector<int>>;
using MatrizComponentes = std::vector<std::vector<std::pair<size_t, size_t>>>;

size_t resolver(MatrizMar &mar, MatrizComponentes &componentes, const std::pair<int, int> &posicion) 
{
    size_t componente_conexa = -1;
    for (auto it : DIRECCIONES_POSIBLES)
    {
        auto [i, ii] = posicion + it;
        if (i >= 0 && i < mar.size() &&
            ii >= 0 && ii < mar[i].size() &&
            mar[i][ii] != 0)
        {
            if (componente_conexa == -1)
            {
                componente_conexa = mar[i][ii];
                mar[posicion.first][posicion.second] = componente_conexa;
                componentes[componente_conexa].push_back(posicion);
            }
            else if (componente_conexa != mar[i][ii]) 
            {
                size_t componente_cambiar = mar[i][ii];
                for (int i = componentes[componente_cambiar].size() - 1; i >= 0; --i)
                {   
                    auto [j, jj] = componentes[componente_cambiar][i];
                    
                    mar[j][jj] = componente_conexa;
                    componentes[componente_conexa].push_back({j, jj});

                    componentes[componente_cambiar].pop_back();
                }
            }
        }
    }

    if (componente_conexa == -1)
    {
        componentes.push_back(std::vector<std::pair<size_t, size_t>>());
        componentes[componentes.size() - 1].push_back(posicion);
        mar[posicion.first][posicion.second] = componentes.size() - 1;
    }

    size_t sol = 0;
    for (size_t i = 0; i < componentes.size(); ++i)
    {
        if(componentes[i].size() > sol)
            sol = componentes[i].size();
    }

    return sol;
}

void dfs(MatrizMar &mar, const std::pair<int, int> &posicion, const int componente_conexa, 
        std::vector<std::pair<size_t, size_t>> &componente)
{
    componente.push_back(posicion); 
    mar[posicion.first][posicion.second] = componente_conexa;

    for (auto it : DIRECCIONES_POSIBLES)
    {
        auto [i, ii] = posicion + it;
        if (i >= 0 && i < mar.size() &&
            ii >= 0 && ii < mar[i].size() &&
            mar[i][ii] == -1)
        {
            dfs(mar, {i, ii}, componente_conexa, componente);
        }
    }
}

size_t inicial (MatrizMar &mar, MatrizComponentes &componentes) 
{
    size_t componente_conexa = 1;
    componentes.push_back(std::vector<std::pair<size_t, size_t>>()); //La componente del 0 es vacía
    for (size_t i = 0; i < mar.size(); ++i)
    {
        for (size_t ii = 0; ii < mar[i].size(); ++ii)
        {
            if(mar[i][ii] == -1)
            {
                componentes.push_back(std::vector<std::pair<size_t, size_t>>());
                dfs(mar, {i, ii}, componente_conexa, componentes[componente_conexa]);
                ++componente_conexa;
            }
        }
    }

    size_t sol = 0;
    for (size_t i = 0; i < componentes.size(); ++i)
    {
        if(componentes[i].size() > sol)
            sol = componentes[i].size();
    }

    return sol;
}

bool resuelveCaso() 
{
    //Leer
    size_t F, C;
    std::cin >> F >> C;

    if (!std::cin)
        return false;

    char aux; std::cin.get(aux); //Salto de línea
    MatrizMar mar (F, std::vector<int> (C));
    MatrizComponentes componentes;
    for (size_t i = 0; i < F; ++i)
    {
        for (size_t ii = 0; ii < C; ++ii)
        {
            std::cin.get(aux);
            if (aux == ' ')
                mar[i][ii] = 0;
            else 
                mar[i][ii] = -1;
        }
        std::cin.get(aux); //Salto de línea
    }

    std::cout << inicial(mar, componentes) << ' '; 

    size_t N, pos1, pos2;
    std::cin >> N;
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> pos1 >> pos2;
        --pos1; --pos2;

        // for (size_t i = 0; i < F; ++i)
        // {
        //     for (size_t ii = 0; ii < C; ++ii)
        //     {
        //         std::cout << mar[i][ii] << ' ';
        //     }
        //     std::cout << '\n';
        // }

        std::cout << resolver(mar, componentes, {pos1, pos2}) << ' ';
    }

    //Escribir
    std::cout << '\n';

    return false;
    
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
