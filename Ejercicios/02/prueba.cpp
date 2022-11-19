#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

bool resuelveCaso() {
    size_t N;
    std::cin >> N;
    if (N == 0)
        return false;

    std::vector<size_t> cosa(N);

    for (size_t i = 0; i < N; ++i)
        std::cin >> cosa[i];

    std::sort(cosa.begin(), cosa.end());
    cosa.erase( unique( cosa.begin(), cosa.end() ), cosa.end() );

    size_t M, el;
    std::cin >> M;
    
    for (size_t i = 0; i < M; ++i) {
        std::cin >> el; --el;
        if (el > cosa.size() - 1)
            std::cout << "??\n";
        else
            std::cout << cosa[el] << '\n';
    }

    std::cout << "---\n";

    return true;
}

int main() {
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());

    while(resuelveCaso());

    std::cin.rdbuf(cinbuf);
}
