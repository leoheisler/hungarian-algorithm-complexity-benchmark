#include <vector>
#include "_Heap.h"
#include "directed_graph.h"
#include <climits>

bool dijkstra_with_path(
  directed_graph& g, 
  const std::vector<int>&matching,
  std::vector<int>&distances,
  std::vector<int>&curr_path,
  int& dst,
  int& sum_updates,
  int& sum_inserts,
  int& sum_deletes
) {
  
  Heap kHeap(2);
  int num_vertices = g.get_num_vertex();

  std::vector<int> dist(num_vertices, INT_MAX);
  std::vector<int> path(num_vertices, -1);

  //add to djikstra map all free S fonts
  for(int i = 0; i < num_vertices/2; i++){
    if(matching[i] == -1){
      dist[i] = 0;
      kHeap.insert(0, i);
    }
  }


  while (!kHeap.is_empty()) {
    Heap::Node heap_head = kHeap.extract_min();

    for (directed_graph::edge edge : g.get_neighbors(heap_head.vertex)) {
      if (heap_head.distance + edge.weight < dist[edge.target]) {
        dist[edge.target] = heap_head.distance + edge.weight;
        path[edge.target] = heap_head.vertex;
        kHeap.insert(dist[edge.target], edge.target);
      }
    }
  }
  //log inserts,updates and deletes
  sum_inserts += kHeap.get_num_inserts();
  sum_updates += kHeap.get_num_updates();
  sum_deletes += kHeap.get_num_deletes();
  
  // finding closest free vertex
  int min_dist = INT_MAX;
  int best_target = -1;

  for (int v = num_vertices/2; v < num_vertices; v++) {
    if (matching[v] == -1 && dist[v] < min_dist) {
      min_dist = dist[v];
      best_target = v;
    }
  }

  if(best_target != -1){
    dst = best_target;
    distances = dist;
    curr_path = path;
    return true;
  }
  return false;
}


std::vector<unsigned> dijkstra( int num_vertices, directed_graph g, Heap& kHeap, unsigned source_index){
  //start funct
  std::vector<unsigned> dist(num_vertices, INT_MAX); 
  dist[source_index] = 0;

  //insert source node
  kHeap.insert(0, source_index);

  while (!kHeap.is_empty()) {
    Heap::Node heap_head = kHeap.extract_min();

    //get heap_neighbors, if distance is less than previously saved
    //update distance and insert neighbor in heap
    for (directed_graph::edge edge : g.get_neighbors(heap_head.vertex)) {
      if (heap_head.distance + edge.weight < dist[edge.target]) {
        dist[edge.target] = heap_head.distance + edge.weight;
        kHeap.insert(dist[edge.target], edge.target);
      }
    }
  }
  return dist;
}


std::vector<int> bellman_ford( directed_graph& g, unsigned source_index){
  // Init distances
  int num_vertexes = g.get_num_vertex();
  std::vector<int> dist(num_vertexes, INT_MAX);
  dist[source_index] = 0;

  // Bellman-Ford
  bool changed;
  for (int i = 0; i < num_vertexes; i++) {
    changed = false;

    //goes trough all edges
    for (int u = 0; u < num_vertexes; u++) {
      for (const auto& edge : g.get_neighbors(u)) {
        int v = edge.target;
        int w = edge.weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
          dist[v] = dist[u] + w;
          changed = true;
        }
      }
    }
    if (!changed) break;
  }

  // Verify negative circles
  // if runned n-1 times bellman-ford algortihm distances must already be minimal
  // if in one more iteration distance updates, cicle identified
  for (int u = 0; u < num_vertexes; ++u) {
      for (const auto& edge : g.get_neighbors(u)) {
          int v = edge.target;
          int w = edge.weight;
          if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
              throw std::runtime_error("Ciclo negativo detectado no grafo.");
          }
      }
  }
  return dist;
}