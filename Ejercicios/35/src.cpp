// DG, Mario Calvarro Marines

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>

std::pair<bool, size_t> resolver(const size_t C, const size_t F, const std::vector<std::pair<size_t, size_t>> &intervalos) 
{
    size_t res = 0;
    size_t final_actual = C; 
    std::stack<std::pair<size_t, size_t>> pila;

    size_t i = 0;
    bool end = false;
    while (i < intervalos.size() && !end)
    {
        if (intervalos[i].first > final_actual && !pila.empty())
        {
            if (pila.top().first <= final_actual)
            {
                ++res;
                final_actual = pila.top().second;
                pila.pop();
            }
            else { return {false, 0}; }
        }

        if (final_actual >= F) end = true;

        if (intervalos[i].first <= final_actual && !end &&
            (pila.empty() || intervalos[i].second >= pila.top().second)) 
        {
            pila.push(intervalos[i]);
        }
        ++i;
    }

    if (!pila.empty() && !end)
    {
        if (pila.top().first <= final_actual)
        {
            ++res;
            final_actual = pila.top().second;
            pila.pop();
        }
        else { return {false, 0}; }
    }

    if (final_actual < F) return { false, 0 };

    return {true, res};
}

bool resuelveCaso() 
{
    //Leer
    size_t C, F, N;
    std::cin >> C >> F >> N;

    if (C == 0 && F == 0 && N == 0)
        return false;

    std::vector<std::pair<size_t, size_t>> intervalos(N);

    size_t aux1, aux2;
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> aux1 >> aux2;
        intervalos[i] = {aux1, aux2};
    }
    std::sort(intervalos.begin(), intervalos.end());

    //Escribir
    auto [posible, res] = resolver(C, F, intervalos);

    if(posible)
        std::cout << res << '\n';
    else 
        std::cout << "Imposible\n";

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
