// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

size_t resolver(const std::vector<size_t> &rivales, const std::vector<size_t> &broncos) 
{
    size_t sol = 0;
    size_t it_riv = 0, it_broncos = 0;
    bool end = false;

    while (!end && it_riv < rivales.size() && it_broncos < broncos.size())
    {
        if (broncos[it_broncos] > rivales[it_riv])  {
            sol += broncos[it_broncos] - rivales[it_riv];
        }
        else {
            end = true;
        }

        ++it_riv; ++it_broncos;
    }

    return sol;
}

bool resuelveCaso() 
{
    //Leer
    size_t n;
    std::cin >> n;

    if (n == 0)
        return false;

    std::vector<size_t> rivales (n);
    for (size_t i = 0; i < n; ++i)
    {
        std::cin >> rivales[i];
    }
    std::sort(rivales.begin(), rivales.end());

    std::vector<size_t> broncos (n);
    for (size_t i = 0; i < n; ++i)
    {
        std::cin >> broncos[i];
    }
    std::sort(broncos.begin(), broncos.end(), std::greater<size_t>());

    //Escribir
    std::cout << resolver(rivales, broncos) << '\n';

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
