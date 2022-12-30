// Grupo XYZ, Fulano y Mengano
// Comentario general sobre la solución,
// explicando cómo se resuelve el problema
#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
#include <string>
#include<iomanip>
// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
using namespace std;


// Resuelve un caso de prueba, leyendo de la entrada la
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
class Camiones {
public:
	Camiones(GrafoValorado<int> const& dg, int inicio, int f, int anchura) : marcados(dg.V(), false), fin(f) {
		ok = false;
		dfs(dg, inicio,anchura);
	}

	bool cabe() {
		return ok;
	}

private:
	bool ok;
	vector<bool> marcados;
	int fin;

	void dfs(GrafoValorado<int> const& dg, int inicio, int anchura) {
		marcados[inicio] = true;
		for (auto a : dg.ady(inicio)) {
			if (anchura <= a.valor()) {
				int w = a.uno();
				if (w == inicio) {
					w = a.otro(inicio);
				}
				if (!marcados[w]) {
					if (w == fin) {
						ok = true;
						return;
					}
					dfs(dg, w, anchura);
				}
			}
		}

	}
 };



bool resuelveCaso() {
	int vertices, aristas;

	cin >> vertices;

	if (!cin)
		return false;

	cin >> aristas;

	GrafoValorado<int> digrafo(vertices);
	
	int a1, a2, v;

	for (int i = 0; i < aristas; i++) {
		cin >> a1 >> a2 >> v;
		digrafo.ponArista({ a1 - 1,a2 - 1,v });
	}

	int camiones;

	int ini, fin, anchura;

	cin >> camiones;

	for (int i = 0; i < camiones; i++) {
		cin >> ini >> fin >> anchura;
		Camiones c(digrafo, ini - 1, fin - 1, anchura);
		bool ok = c.cabe();
		if (ok)
			cout << "SI" << '\n';
		else {
			cout << "NO" << '\n';
		}
	}



	return true;
}
int main() {
#ifndef DOMJUDGE
	std::ifstream in("casos.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif

	return 0;
}