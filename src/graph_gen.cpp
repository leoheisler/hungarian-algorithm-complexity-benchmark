#include <iostream>
#include <vector>
#include <random>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " n [max]\n";
        std::cerr << "  n: size of each partition (n x n bipartite graph)\n";
        std::cerr << "  max (optional): set to 1 for max-weight matching (negated weights)\n";
        return 1;
    }

    int n = std::stoi(argv[1]);
    bool max_mode = false;
    if (argc == 3) {
        max_mode = (std::string(argv[2]) == "1");
    } 

    int max_weight = n * n;

    // Random number generator setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, max_weight);

    // Print size
    std::cout << n << "\n";

    // Generate and print weights
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int w = dis(gen);
            if (max_mode) {
                w = -w;
            }
            std::cout << w;
            if (j < n - 1) std::cout << " ";
        }
        std::cout << "\n";
    }

    return 0;
}