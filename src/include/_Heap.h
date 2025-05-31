#include <vector>
#include <unordered_map>
#include <math.h>

class Heap
{
public:
    struct Node{
        unsigned distance;
        unsigned vertex;
    };
private:
    //control vars
    int k;
    unsigned num_inserts = 0;
    unsigned num_updates = 0;
    unsigned num_deletes = 0;
    int sift_up_counter = 0;
    int sift_down_counter = 0;

    std::vector<double> r_values = {};

    std::vector<Node> heap_queue = {};
    std::unordered_map<int,int> vertex_heap_map;

    /*  PRIVATE FUNCTS */
    // Returns parent heap index
    // of child i
    int get_parent_index(int i) {
        return (i - 1) / k;
    }

    // Returns child node heap j index
    // if j == 2, returns second child from 
    // i parent
    int get_child_index(int i, int j) {
        return k * i + j + 1; 
    }
    
    // Reorders heap to preserve min_heap property
    // swaps child and father priority, sending child up
    // return number of sifts
    void sift_up(int child_index) {
        while (child_index > 0 && heap_queue[child_index].distance < heap_queue[get_parent_index(child_index)].distance) {
            std::swap(heap_queue[child_index], heap_queue[get_parent_index(child_index)]);
            this->sift_up_counter++;

            //swap mapping values
            vertex_heap_map[heap_queue[child_index].vertex] = child_index;
            vertex_heap_map[heap_queue[get_parent_index(child_index)].vertex] = get_parent_index(child_index);

            child_index = get_parent_index(child_index);
        }
    }

    // Reorders heap to preserve min_heap property
    // swaps child and father priority, sending father up
    // return number of sifts
    void sift_down(int parent_index) {
        int smallest_index = parent_index;

        //check if any children has a smaller distance
        for (int j = 0; j < k; ++j) {
            int c = get_child_index(parent_index, j);
            if (c < heap_queue.size() && heap_queue[c].distance < heap_queue[smallest_index].distance) {
                smallest_index = c;
            }
        }

        if (smallest_index != parent_index) {
            std::swap(heap_queue[parent_index], heap_queue[smallest_index]);
            this->sift_down_counter++;

            //swap mapping values
            vertex_heap_map[heap_queue[parent_index].vertex] = parent_index;
            vertex_heap_map[heap_queue[smallest_index].vertex] = smallest_index;
            sift_down(smallest_index);
        }

    }
    
public:
    //contructor
    Heap(int k): k(k) {}

    //getters
    unsigned get_num_inserts(){ return this->num_inserts; }
    unsigned get_num_deletes(){ return this->num_deletes; }
    unsigned get_num_updates(){ return this->num_updates; }

    //heap functions
    //Inserts node in heap 
    void insert(unsigned distance, unsigned vertex) {

        if (vertex_heap_map.count(vertex)) {
            //update distance if vertex is already in heap
            if (distance < heap_queue[vertex_heap_map[vertex]].distance) {
              num_updates++;
              heap_queue[vertex_heap_map[vertex]].distance = distance;
              sift_up(vertex_heap_map[vertex]);
            }
        } else {
            num_inserts++;

            Node new_vertex = {distance,vertex};
            heap_queue.push_back(new_vertex);
            
            int new_vertex_index = heap_queue.size() - 1;
            vertex_heap_map[vertex] = new_vertex_index;
            sift_up(new_vertex_index);
        }
    }
    
    //extract min
    Node extract_min() {
        num_deletes++;
        
        //release first node
        Node min_node = heap_queue[0];
        vertex_heap_map.erase(min_node.vertex);

        //send last node to first position
        heap_queue[0] = heap_queue.back();
        vertex_heap_map[heap_queue[0].vertex] = 0;
        
        //destroy last position
        heap_queue.pop_back();

        if (!heap_queue.empty()) {
            sift_down(0);
        }

        return min_node;
    }

    // cleans heap
    void clear(){
      this->heap_queue.clear();
      this->vertex_heap_map.clear();
    }

    // Returns heap state
    bool is_empty() {
        return heap_queue.empty();
    }
    
};

