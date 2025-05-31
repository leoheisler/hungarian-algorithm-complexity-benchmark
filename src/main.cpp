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
  int& dst,
  int& sum_updates,
  int& sum_inserts,
  int& sum_deletes
) {
  
  bool result = dijkstra_with_path(H_M, matching, distances, path, dst, sum_updates,sum_inserts,sum_deletes);


  return result;
}

std::vector<int> hungarian_algorithm(undirected_graph g, std::ofstream& outfile) {
  directed_graph H_M;
  std::vector<int> matching(g.get_vertex_num(),-1);
  std::vector<int> potentials = undirected_graph::init_potentials(g);
  std::vector<int> distances(g.get_vertex_num(),INT_MAX);
  std::vector<int> path(g.get_vertex_num(),-1);
  int sum_updates = 0, sum_inserts = 0, sum_deletes = 0, total_itr = 0;

  int dst;
  while (true) {
    auxiliary_functs::build_HM_graph(g, matching, potentials, H_M);
    if (!find_augmenting_path(H_M ,matching ,distances, potentials, path, dst, sum_updates, sum_inserts, sum_deletes)) {
      break;
    }
  
    //update matching
    auxiliary_functs::xor_matching(matching,path,dst);
    undirected_graph::update_potentials(potentials,distances);
    total_itr++;
  } 
  sum_updates = sum_updates / (total_itr * (g.get_rows_num() * g.get_columns_num()));
  sum_inserts = sum_inserts / (total_itr * g.get_vertex_num());
  sum_deletes = sum_deletes / (total_itr * g.get_vertex_num());


  if (outfile.is_open()) {
    outfile << total_itr << ',';
    outfile << sum_inserts << ',';
    outfile << sum_updates << ',';
    outfile << sum_deletes << ',';
  }
  return matching;   
}  

 
int main(int argc, char* argv[]){   
  int eppm = 1; 
  std::ofstream outfile;
  if (argc > 1) {
      outfile.open(argv[1], std::ios::app);
  } else {
      outfile.open(""); 
  }
  undirected_graph g = Read::read_bipartite_graph(std::cin);
  undirected_graph eppm_g = g.eppm_instance();
  auto start = std::chrono::high_resolution_clock::now();

  try{
    std::vector<int> matching;
    if(eppm){
      matching = hungarian_algorithm(eppm_g, outfile);
    }else{
      matching = hungarian_algorithm(g, outfile);
    }
     
    int value = auxiliary_functs::calc_matching_value(g,matching); 
    std::cout << value << std::endl;
  }catch(const std::exception& e){
      std::cout << "Exceção capturada: " << e.what() << std::endl;
  }
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = finish - start;

  if (outfile.is_open()) {
    outfile << duration.count() << std::endl;
  }

  return 0;
}  