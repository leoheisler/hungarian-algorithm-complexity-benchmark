#ifndef UNDIRECTED_GRAPH_H
#define UNDIRECTED_GRAPH_H
#include <vector>
#include <iostream>
#include <climits>

class undirected_graph
{
private:
  int num_rows;
  int num_columns;
  std::vector<std::vector<int>> graph_mem;

public:
  undirected_graph(int num_rows, int num_columns)
      : num_rows(num_rows), num_columns(num_columns),
        graph_mem(num_rows, std::vector<int>(num_columns, 0)){}

  int get_rows_num(){ return num_rows; }
  int get_columns_num(){ return num_columns; }
  int get_vertex_num(){ return num_columns + num_rows; }
  std::vector<std::vector<int>>  get_graph_mem(){ return graph_mem; }
  void add_edge(int src, int target, int weight){
    graph_mem[src][target] = weight;
  }

  static std::vector<int> init_potentials(undirected_graph &g) {
    int rows_num = g.get_rows_num();
    int cols_num = g.get_columns_num();

    std::vector<int> potentials( rows_num + cols_num, 0 );

    //get haviest edge
    int haviest = INT_MIN;
    auto graph_mem = g.get_graph_mem();
    for(int i = 0; i < rows_num; i++){
      for(int j = 0; j < cols_num; j++){
        if(graph_mem[i][j] > haviest){
          haviest = graph_mem[i][j];
        }
      }
    }
    //set all potentials for T graphs = - W
    std::fill(potentials.begin() + (rows_num + cols_num)/ 2, potentials.end(), -haviest);
    return potentials;
  }


  template <typename T>

  static void print_vector(const std::vector<T>& vec) {
    int i = 0;
    std::cout << "[ ";
    for (const T& val : vec) {
      int e = val == INT_MAX ? -1 : val;
      std::cout << i << ":"<< e << " ";
      i++;
    }
    std::cout << "]\n";
  }

  static void update_potentials(std::vector<int> &potentials, const std::vector<int>& dist) {
    for (int v = 0; v < potentials.size(); v++) {
      if (dist[v] != INT_MAX) {
        potentials[v] += dist[v];
      }
    }
  }

  void print_graph(){
    for(int i = 0; i < num_rows; i++){
      for(int j = 0; j < num_columns; j++){
        std::cout << graph_mem[i][j] << " ";
      }
      std::cout << "\n";
    }
  }

    
};
#endif // UNDIRECTED_GRAPH_H