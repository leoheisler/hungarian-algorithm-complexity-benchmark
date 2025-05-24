#include "../src/include/_Paths.h"
#include <cassert>
#include "../src/include/_Read.h"
#include "../src/include/auxiliary_functs.h"
#include <stack>
#include <iostream>
#include <vector>
#include <optional>
#include <algorithm>

using namespace std;

void print_path(const std::vector<int>& path, int dst) {
  std::vector<int> full_path;
  for (int at = dst; at != -1; at = path[at])
    full_path.push_back(at);

  std::reverse(full_path.begin(), full_path.end());
  std::cout << "Caminho: ";
  for (int v : full_path)
    std::cout << v << " -> ";
  std::cout << "\n";
}
// Teste principal
void test_dijkstra_with_path() {
  // Grafo bipartido de 6 vértices: S = {0,1}, T = {2,3}
  directed_graph g(4);

  // Adiciona arestas de S para T
  g.add_edge(0, 2, 0);
  g.add_edge(0, 3, 5);
  g.add_edge(1, 2, 8);
  g.add_edge(1, 3, 2);


  // emparelhamento parcial: 0->4, 1->3, 2 e 5 livres
  std::vector<int> matching = {-1,-1,-1,-1};

  std::vector<int> distances, curr_path;
  int dst;

  bool found = dijkstra_with_path(g, matching, distances, curr_path, dst);

  assert(found);

  undirected_graph::print_vector(distances);
  undirected_graph::print_vector(curr_path);
  std::cout << dst<< "\n";

  auxiliary_functs::xor_matching(matching,curr_path,dst);
  undirected_graph::print_vector(matching);

  found = dijkstra_with_path(g, matching, distances, curr_path, dst);

  std::cout << "djik 2\n";
  undirected_graph::print_vector(distances);
  undirected_graph::print_vector(curr_path);
  std::cout << dst<< "\n";

  auxiliary_functs::xor_matching(matching,curr_path,dst);
  undirected_graph::print_vector(matching);

  found = dijkstra_with_path(g, matching, distances, curr_path, dst);

  std::cout << "djik 3\n";
  std::cout << found;


}


int main(){
  test_dijkstra_with_path();
  std::cout << "✅ Todos os testes passaram com sucesso.\n";
}
