
/*@ <answer>
 *
 * Nombre y Apellidos: Lucía Alonso Mozo
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

/*@ <answer>

  Comentario general sobre la solucion:

  Coste de la solucion:

 @ </answer> */

//@ <answer>

void dfs(std::vector <vector <int> > & g, int v, std::vector <bool>& visitado, std::vector <bool> & apilado, bool& hayCiclo, bool & alcanzadoFinal){
    apilado[v] = true;
    visitado[v] = true;

    for(int w: g[v]) {
        if(w < g.size()){
            if(!visitado[w]){ //nuevo nodo
                dfs(g, w, visitado, apilado, hayCiclo, alcanzadoFinal);
            }
            else if (visitado[w] && apilado[w]){ //encontramos ciclo
                hayCiclo = true; 
            }
        }
        else {
           alcanzadoFinal = true;
        }
    }
    apilado[v] = false;
}

bool resuelveCaso() {
   
   // leer los datos de la entrada
   int num;
   std::cin >> num;

   if (!cin)  // fin de la entrada
      return false;  

    std::vector < vector <int> > g (num);

    for(int i = 0; i < num; i++){
        char tipo;
        std::cin >> tipo;
        if(tipo == 'A'){
            g[i].push_back(i + 1);
        }
        else if(tipo == 'J'){
            int salto;
            std::cin >> salto;
            g[i].push_back(salto-1);
        }
        else{
            int salto;
            std::cin >> salto;
            g[i].push_back(i+1);
            g[i].push_back(salto-1); //dependiendo de la vez sigue un camino u otro
            
        }
    }
   // resolver el caso posiblemente llamando a otras funciones
    std::vector <bool> visitado (num);
    std::vector <bool> apilado (num);
    bool hayCiclo = false;
    bool alcanzadoFinal = false;

    dfs(g, 0, visitado, apilado, hayCiclo, alcanzadoFinal);
   // escribir la solución

    if(hayCiclo && alcanzadoFinal) std::cout << "A VECES" << "\n";
    else if(hayCiclo && !alcanzadoFinal) std::cout << "NUNCA" << "\n";
    else std::cout << "SIEMPRE" << "\n";
   
   return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   ifstream in("casos.txt");
   auto cinbuf = cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
