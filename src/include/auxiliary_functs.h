#include "undirected_graph.h"
#include "directed_graph.h"
class auxiliary_functs
{
public:
  static void print_path(const std::vector<int>& path, int dst) {
    std::vector<int> full_path;
    for (int at = dst; at != -1; at = path[at])
      full_path.push_back(at);

    std::reverse(full_path.begin(), full_path.end());
    std::cout << "Caminho: ";
    for (int v : full_path)
      std::cout << v << " -> ";
    std::cout << "fim\n";
  }

  static void build_HM_graph(undirected_graph& g, std::vector<int>& match, std::vector<int>& potentials, directed_graph& H_M) {
    H_M = directed_graph(g.get_vertex_num());
    auto original_edges = g.get_graph_mem();
    int T = g.get_rows_num(); 
  
    for (int u = 0; u < g.get_rows_num(); u++) {
      for (int v = 0; v < g.get_columns_num(); v++ ){
        int weight = original_edges[u][v];
        if(is_matched(u,v + T, match)){
          H_M.add_edge(v + T, u,  weight + potentials[T + v] - potentials[u]); //must add T to src vertex to fit array value
        }else{
          H_M.add_edge(u, v + T,  -weight + potentials[u] - potentials[T + v]);   
        }
      }
    }
  }

  static int calc_matching_value(undirected_graph& g, const std::vector<int>& matching){
    std::cout << "CALCULANDO O PESO DO MATCHING: " << std::endl;
    undirected_graph::print_vector(matching);
    int result = 0;
    int T = matching.size()/2;
    auto weights = g.get_graph_mem();
    for(int i = 0; i < g.get_rows_num(); i++){
      for(int j = 0; j < g.get_columns_num(); j++){
        if(is_matched(i,j + T,matching)){
          std::cout << weights[i][j] << std::endl;
          result += weights[i][j];
        }
      }
    }

    return result;
  }

  static void xor_matching(std::vector<int>& matching, const std::vector<int>& path, int dest) {
    std::vector<int> new_matching = matching;
    auxiliary_functs::print_path(path,dest);

    std::cout << "matching before: ";
    undirected_graph::print_vector(matching);
    int curr = dest;
    while (path[curr] != -1) {
      int match = path[curr];

      if (is_matched(match, curr, matching)) {
        new_matching[match] = -1;
      }else{
        new_matching[curr] = match;
        new_matching[match] = curr;
      }
      curr = match;
    }
    std::cout << "matching after: ";
    matching = new_matching;
    undirected_graph::print_vector(matching);
    std::cout << " \n";
  }

  // returns if edge is present in current matching
  static bool is_matched(int u, int v, const std::vector<int>& M) {
    return M[u] != -1 && 
          M[v] != -1 && 
          M[u] == v  &&
          M[v] == u;
  }
  
};
