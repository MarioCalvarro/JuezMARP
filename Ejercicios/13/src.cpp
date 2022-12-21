// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using matrix = std::vector<std::vector<bool>>;

const size_t POSIBLES_MOVIMIENTOS = 4;
std::pair<int, int> CAMBIOS_POSICION[POSIBLES_MOVIMIENTOS] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

std::pair<int, int> operator+(const std::pair<int, int> lhs, const std::pair<int, int> rhs) 
{
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

size_t dfs(matrix &datos, const std::pair<int, int> pos) 
{
    size_t res = 1;
    datos[pos.first][pos.second] = false;
    for (size_t i = 0; i < POSIBLES_MOVIMIENTOS; ++i)
    {
        std::pair<int, int> nueva_pos = pos + CAMBIOS_POSICION[i];
        if (nueva_pos.first >= 0  && nueva_pos.first < datos.size() && nueva_pos.second >= 0 && nueva_pos.second < datos[0].size() && datos[nueva_pos.first][nueva_pos.second]) 
        {
            res += dfs(datos, nueva_pos); 
        }
    }
    return res;
}

std::pair<size_t, size_t> resolver(matrix &datos) 
{
    size_t auxComponente, maxComponente = 0;
    size_t numManchas = 0;
    for (size_t i = 0; i < datos.size(); ++i) 
    {
        for (size_t ii = 0; ii < datos[i].size(); ++ii) 
        {
            auxComponente = 0;
            if(datos[i][ii])
            {
                ++numManchas;
                auxComponente = dfs(datos, {i, ii});
                if (auxComponente > maxComponente)
                    maxComponente = auxComponente;
            }
        }
    }
    return {numManchas, maxComponente};
}

bool resuelveCaso() 
{
    //Leer
    size_t F, C;
    std::cin >> F >> C;

    if (!std::cin)
        return false;

    char aux;
    matrix datos (F, std::vector<bool>(C));
    for (size_t i = 0; i < F; ++i) 
    {
        for (size_t ii = 0; ii < C; ++ii) 
        {
            std::cin >> aux;
            datos[i][ii] = aux == '#'? true : false;
        }
    }

    auto [res1, res2] = resolver(datos);

    //Escribir
    std::cout << res1 << ' ' << res2 << '\n';

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
