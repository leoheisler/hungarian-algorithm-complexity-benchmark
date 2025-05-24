#include <istream>
#include <iostream>
#include <sstream>
#include <string>
#include "undirected_graph.h"

class Read
{
public:

  static undirected_graph read_bipartite_graph(std::istream& in) {
    std::string line="", dummy;
    int vertex_num;
  
    // (1) get total_nodes
    getline(in,line);
    std::stringstream linestr;
    linestr.str(line);
    linestr >> vertex_num;
    undirected_graph g(vertex_num,vertex_num);
    for(int i = 0; i < vertex_num; i++){
      getline(in,line);
      std::stringstream row(line);
      int edge_value;
      int j = 0;
      while(row >> edge_value){
        g.add_edge(i, j, edge_value);
        j++;
      }
    }

    return g;
  }
};



