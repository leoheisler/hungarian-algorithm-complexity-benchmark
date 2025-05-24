#include "_Read.h"
#include "_Paths.h"
#include <fstream>
#include <chrono>
#include <algorithm>
#include "auxiliary_functs.h"

bool find_augmenting_path(
  directed_graph& H_M, 
  std::vector<int>& matching, 
  std::vector<int>& distances,
  std::vector<int>& potentials,
  std::vector<int>& path,
  int& dst

) {
  
  bool result = dijkstra_with_path(H_M, matching, distances, path, dst);


  return result;
}

std::vector<int> hungarian_algorithm(undirected_graph g) {
  directed_graph H_M;
  std::vector<int> matching(g.get_vertex_num(),-1);
  std::vector<int> potentials = undirected_graph::init_potentials(g);
  std::vector<int> distances(g.get_vertex_num(),INT_MAX);
  std::vector<int> path(g.get_vertex_num(),-1);
  int dst;
  while (true) {
    auxiliary_functs::build_HM_graph(g, matching, potentials, H_M);
    if (!find_augmenting_path(H_M ,matching ,distances, potentials, path, dst)) {
      break;
    }
  
    std::cout << "DISTANCIA ENCONTRADA: " << distances[dst] << std::endl;
    //update matching
    auxiliary_functs::xor_matching(matching,path,dst);
    undirected_graph::update_potentials(potentials,distances);
  } 
  return matching;   
} 

 
int main(int argc, char* argv[]){   
  undirected_graph g = Read::read_bipartite_graph(std::cin);
  try{
    std::vector<int> matching = hungarian_algorithm(g);
    int value = auxiliary_functs::calc_matching_value(g,matching);
    std::cout << value;
  }catch(const std::exception& e){
      std::cout << "Exceção capturada: " << e.what() << std::endl;
  }

  return 0;
}  