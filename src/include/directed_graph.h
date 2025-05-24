#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H
#include <vector>
#include <iostream>
#include <climits>
#include "undirected_graph.h"

class directed_graph
{
public:
  struct edge {
    int weight;
    int target;
    int src;

    bool operator==(const edge &other) const{
      return weight == other.weight &&
             target == other.target &&
             src == other.src;
    }

    bool operator!=(const edge &other) const{
      return !(*this == other);
    }
  };

private:
  int num_vertex;
  int num_edges;
  std::vector<std::vector<edge>> graph_mem;

public:
  // constructors
  directed_graph() : num_vertex(0), num_edges(0) {}
  directed_graph(int n) : num_vertex(n), num_edges(0) { graph_mem.resize(n); }

  // getters & setters
  int get_num_edges() { return num_edges; }
  int get_num_vertex() { return num_vertex; }
  std::vector<std::vector<edge>> get_graph_mem() { return graph_mem; }
  std::vector<edge> get_neighbors(int i) { return graph_mem[i]; }

  // functs
  void add_vertex(int i){
    std::vector<edge> vertex = {};
    this->graph_mem[i] = vertex;
  }

  void resize_mem(int n_mem){
    this->num_vertex = n_mem;
    graph_mem.resize(n_mem);
  }

  void add_edge(int source, int target, int weight){
    edge new_edge = {weight, target, source};
    this->num_edges++;
    graph_mem[source].push_back(new_edge);
  }

  void print_graph() {
    const auto& mem = graph_mem;
    for (int u = 0; u < mem.size(); ++u) {
      for (const auto& e : mem[u]) {
        std::cout << e.src << " -> " << e.target << " (w=" << e.weight << ")\n";
      }
    }
  }

  directed_graph deep_copy(){
    directed_graph copy;

    int new_num_vertex = this->num_vertex;
    copy.resize_mem(new_num_vertex);

    // Copia as arestas
    for (int i = 0; i < this->num_vertex; ++i)
    {
      for (const edge &e : this->graph_mem[i])
      {
        copy.add_edge(e.src, e.target, e.weight);
      }
    }

    return copy;
  }

  void extend_graph(int n){
    this->graph_mem.resize(this->num_vertex + n);
    this->num_vertex = this->num_vertex + n;
  }

  void reduce_graph(int n){
    int mem_len = this->num_vertex - n;
    this->graph_mem.resize(mem_len);
    this->num_vertex = mem_len;
  }
};

#endif //DIRECTED_GRAPH_H
