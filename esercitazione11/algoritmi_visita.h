#pragma once
#include "undirected_graph.h"
#include <vector>
#include <set>
#include <limits> //usare infinito
#include <queue> //usare priority queue

//BFS, DFS
template <typename T, typename contenitore>
//T è tipo oggetti nodi dentro grafo, contenitore è tipo contenitore (coda/pila)
undirected_graph<T> graph_visit(const undirected_graph<T>& G, const T& v, contenitore& c) {
	undirected_graph<T> albero_visita; 
	std::set<T> visitati; //non ho numerazione nodi -> devo salvare così nodi visitati
	std::map<T,T> predecessore; //salvo predecessori: devo ricostruire albero visita
	c.put(v);
		
	while(! c.empty()) {
		T u = c.get(); 
		visitati.insert(u); //salvo nodo come visitato quando esce dalla pila
		for(auto& w : G.neighbours(u)) {
			if(visitati.find(w) == visitati.end()) { //se nodo non ancora stato visitato
				c.put(w); 
				//salvo come predecessore nodo che lo ha scoperto
				if (predecessore.find(w) == predecessore.end()) { 
					predecessore[w] = u;
				}
			}
		}
	}
	for(auto& nodo : predecessore) {
	  albero_visita.add_edge(nodo.first, nodo.second);
		}
	return albero_visita;
}

//DFS RICORSIVA
template <typename T>
void ricorsione(const undirected_graph<T>& G, const T& nodo_corrente,
 std::set<T>& visitati, undirected_graph<T>& albero_visita) {
	visitati.insert(nodo_corrente); 
	//considero visitato nodo_corrente della ricorsione
	for(auto& w : G.neighbours(nodo_corrente)) {
		if (visitati.find(w) == visitati.end()) {
			albero_visita.add_edge(nodo_corrente, w);
			ricorsione(G, w, visitati, albero_visita);
			//per ogni vicino non visitato "vado in profondità": (cfr. salto del cavallo)
			//aggiungo arco all'albero di visita e diventa lui nodo_corrente
		}
	}
 }

template <typename T>
//T è tipo oggetti nodi dentro grafo, contenitore è tipo contenitore (coda/pila)
undirected_graph<T> recursive_dfs(const undirected_graph<T>& G, const T& v) {
	undirected_graph<T> albero_visita; 
	std::set<T> visitati;
	ricorsione(G, v, visitati, albero_visita); //funzione che effettua effettivamente
	//ricorsione 
	return albero_visita;
}

//DIJKSTRA
template <typename T>
undirected_graph<T> Dijkstra(const undirected_graph<T>& G, const T& s) {
	undirected_graph<T> albero_visita; 
	std::vector<T> nodi = G.all_nodes();
	std::map<T,T> predecessore; 
	std::map<T,int> distanza_sorgente;
	
	int infinito = std::numeric_limits<int>::max();
	for(auto& nodo : nodi) {
		distanza_sorgente[nodo] = infinito;
	}
	predecessore[s] = s; 
	distanza_sorgente[s] = 0;
	std::priority_queue<std::pair<int,T>, std::vector<std::pair<int,T>>, std::greater<std::pair<int,T>>> coda_priorità; 
	//metto in coda coppie nodo-distanza, voglio ordinare rispetto elementi con distanza
	//minore --> utilizzo come comparatore greater
	for(auto& nodo : nodi) {
		coda_priorità.push({distanza_sorgente[nodo], nodo});
	}
	while(! coda_priorità.empty()) {
		T u = coda_priorità.top().second;
		int dist_u = coda_priorità.top().first;
		coda_priorità.pop();
		
		if (dist_u > distanza_sorgente[u]) {
			continue;
		}
		//non considero nodi con distanza maggiore di quella migliore trovata 
		
		for(auto& w : G.neighbours(u)) {
			if(distanza_sorgente[w] > (dist_u + 1)) {
				distanza_sorgente[w] = dist_u + 1;
				predecessore[w] = u;
				coda_priorità.push({distanza_sorgente[w], w});
				//salvo duplicato nella coda, avrà priorità più bassa di quello già presente
				//--> estratto prima
				//--> per non riconsiderarlo quando verrà estratto aggiungo controllo sopra:
				
			}
		}
	}
	for(auto& nodo : predecessore) {
		if(nodo.first != s)
		  albero_visita.add_edge(nodo.first, nodo.second);
			}
	return albero_visita;
	
	
}