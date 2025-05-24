#include <cassert>
#include <iostream>
#include <vector>
#include "../src/include/_Heap.h"
int main(){
    // Teste 1: Inserção e extração simples com atualização
    {
      Heap heap(2);

      // Insere alguns nós: (distância, vértice)
      heap.insert(10, 1);
      heap.insert(5, 2);
      heap.insert(20, 3);
      heap.insert(3, 4);
      heap.insert(8, 5);

      // Atualiza o vértice 3 com uma distância menor (deve atualizar o valor de 20 para 2)
      heap.insert(2, 3);

      // Ordem esperada após as operações:
      // vértice 3: distância 2
      // vértice 4: distância 3
      // vértice 2: distância 5
      // vértice 5: distância 8
      // vértice 1: distância 10
      std::vector<Heap::Node> expected = {
          {2, 3},
          {3, 4},
          {5, 2},
          {8, 5},
          {10, 1}
      };

      std::cout << "Teste 1: Extração em ordem de distância" << std::endl;
      for (size_t i = 0; i < expected.size(); ++i) {
        assert(!heap.is_empty());
        Heap::Node node = heap.extract_min();
        std::cout << "Extraído -> Vértice: " << node.vertex << ", Distância: " << node.distance << std::endl;
        // Verifica se o nó extraído corresponde ao esperado
        assert(node.vertex == expected[i].vertex);
        assert(node.distance == expected[i].distance);
      }
      assert(heap.is_empty());

      heap.clear();

      // Insere alguns nós: (distância, vértice)
      heap.insert(10, 1);
      heap.insert(5, 2);
      heap.insert(20, 3);
      heap.insert(3, 4);
      heap.insert(8, 5);

      // Atualiza o vértice 3 com uma distância menor (deve atualizar o valor de 20 para 2)
      heap.insert(2, 3);

      std::cout << "Teste 1: Extração em ordem de distância" << std::endl;
      for (size_t i = 0; i < expected.size(); ++i) {
        assert(!heap.is_empty());
        Heap::Node node = heap.extract_min();
        std::cout << "Extraído -> Vértice: " << node.vertex << ", Distância: " << node.distance << std::endl;
        // Verifica se o nó extraído corresponde ao esperado
        assert(node.vertex == expected[i].vertex);
        assert(node.distance == expected[i].distance);
      }
      assert(heap.is_empty());
    }

    // Teste 2: Inserir elementos em ordem decrescente e extrair em ordem crescente
    {
      Heap heap(2);

      // Inserindo nós em ordem decrescente de distância
      heap.insert(50, 1);
      heap.insert(40, 2);
      heap.insert(30, 3);
      heap.insert(20, 4);
      heap.insert(10, 5);

      // Ordem esperada: (10,5), (20,4), (30,3), (40,2), (50,1)
      std::vector<Heap::Node> expected = {
          {10, 5},
          {20, 4},
          {30, 3},
          {40, 2},
          {50, 1}
      };

      std::cout << "\nTeste 2: Extração com inserção em ordem decrescente" << std::endl;
      for (size_t i = 0; i < expected.size(); ++i) {
          assert(!heap.is_empty());
          Heap::Node node = heap.extract_min();
          std::cout << "Extraído -> Vértice: " << node.vertex << ", Distância: " << node.distance << std::endl;
          assert(node.vertex == expected[i].vertex);
          assert(node.distance == expected[i].distance);
      }
      assert(heap.is_empty());

      heap.clear();
      // Inserindo nós em ordem decrescente de distância
      heap.insert(50, 1);
      heap.insert(40, 2);
      heap.insert(30, 3);
      heap.insert(20, 4);
      heap.insert(10, 5);

      std::cout << "\nTeste 2: Extração com inserção em ordem decrescente" << std::endl;
      for (size_t i = 0; i < expected.size(); ++i) {
          assert(!heap.is_empty());
          Heap::Node node = heap.extract_min();
          std::cout << "Extraído -> Vértice: " << node.vertex << ", Distância: " << node.distance << std::endl;
          assert(node.vertex == expected[i].vertex);
          assert(node.distance == expected[i].distance);
      }
      assert(heap.is_empty());
    }

    // Teste 3: Atualização de distância de um nó já existente
    {
      Heap heap(2);

      // Insere nós
      heap.insert(15, 1);
      heap.insert(25, 2);
      heap.insert(35, 3);

      // Atualiza o vértice 2 para uma distância menor
      heap.insert(5, 2); // agora o vértice 2 deve sair primeiro

      std::cout << "\nTeste 3: Atualização de distância" << std::endl;
      Heap::Node node = heap.extract_min();
      std::cout << "Extraído -> Vértice: " << node.vertex << ", Distância: " << node.distance << std::endl;
      assert(node.vertex == 2);
      assert(node.distance == 5);

      // limpa o heap
      heap.clear();
      // Insere nós
      heap.insert(15, 1);
      heap.insert(25, 2);
      heap.insert(35, 3);

      // Atualiza o vértice 2 para uma distância menor
      heap.insert(5, 2); // agora o vértice 2 deve sair primeiro

      std::cout << "\nTeste 3: Atualização de distância" << std::endl;
      node = heap.extract_min();
      std::cout << "Extraído -> Vértice: " << node.vertex << ", Distância: " << node.distance << std::endl;
      assert(node.vertex == 2);
      assert(node.distance == 5);

    }
    std::cout << "\nTodos os testes foram executados com sucesso." << std::endl;
    return 0;
}