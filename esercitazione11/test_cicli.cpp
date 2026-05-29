#include <iostream>
#include "undirected_graph.h"
#include "cicli_fondamentali.h"

int main(void) {
	undirected_graph<int> G; 
	G.add_edge(1,2);
	G.add_edge(1,3);
	G.add_edge(2,3);
	G.add_edge(2,4);
	G.add_edge(3,4);
	//std::vector<std::vector<int>> cicli_fondamentali = DFS_cicli(G);
	std::vector<std::vector<int>> cicli_fondamentali = DePina_cicli(G);
	
	for(size_t i = 0; i < cicli_fondamentali.size(); i++) {
		std::cout << "Ciclo fondamentale " << i + 1 << std::endl; 
		for(size_t j = 0; j < cicli_fondamentali[i].size(); j++) {
			std::cout << cicli_fondamentali[i][j]; 
		}
		std::cout << "\n"; 
	}
	return 0; 
}