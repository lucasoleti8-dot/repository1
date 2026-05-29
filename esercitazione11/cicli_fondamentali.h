#pragma once
#include "undirected_graph.h"
#include "algoritmi_visita.h"
#include <vector> 
#include <set>
#include <algorithm> //serve per std::count e std::find

//METODO BASATO SU DFS

template <typename T>
bool findpath(const undirected_graph<T>& DFS_tree, const T& u, const T& v,
 std::vector<T>& path, std::set<T>& visitati) {
	visitati.insert(u);
	path.push_back(u);
	if (u == v) {
		return true; 
	}
	for(auto& n : DFS_tree.neighbours(u)) {
		if(visitati.find(n) == visitati.end()) {
			if (findpath(DFS_tree, n, v, path, visitati)) {
				return true; 
			}
		}
	}
	path.pop_back();
	return false; 
}

template <typename T>
std::vector<std::vector<T>> DFS_cicli(undirected_graph<T>& G) {
	std::vector<std::vector<T>> cicli_fondamentali; 
	T root = G.all_nodes()[0]; //parto da nodo qualsiasi per effettuare visita DFS
	undirected_graph<T> DFS_tree = recursive_dfs(G, root);
	undirected_graph<T> C = G - DFS_tree; 
	for(auto& edge : C.all_edges()) {
		std::vector<T> ciclo; 
		std::set<T> visitati; 
		findpath(DFS_tree, edge.from(), edge.to(), ciclo, visitati); 
		ciclo.push_back(edge.from());
		cicli_fondamentali.push_back(ciclo);
	}
	return cicli_fondamentali; 
}

//ALGORITMO DE PINA

int prod_scalare_bool(std::vector<int>& S, std::vector<int>& P) {
	int sum = 0; 
	for(size_t i = 0; i < S.size(); i++) {
		sum += (S[i] * P[i]);
	}
	return (sum % 2);
}

std::vector<int> differenza_simmetrica_bool(std::vector<int>& S, std::vector<int>& P) {
	std::vector <int> vettore_diff(S.size());
	for(size_t i = 0; i < S.size(); i++) {
		if ((S[i] == 0 && P[i] == 1) || (S[i] == 1 && P[i] == 0)) {
			vettore_diff[i] = 1; 
		}
		else {
			vettore_diff[i] = 0;
		}
	}
	return vettore_diff;
}

template <typename T>
std::vector<std::vector<T>> DePina_cicli(undirected_graph<T>& G) {
	int n = G.all_nodes().size(); // n é numero di nodi
	int m = G.all_edges().size(); // m è numero di archi
	int k = m - n + 1; // #cicli fondamentali
	std::vector<undirected_edge<T>> archiG = G.all_edges(); //OSS: archi già ordinati
	std::vector<T> nodiG = G.all_nodes();
	
	
	//inzializzazione k vettori di supporto di lugnhezza m
	std::vector<std::vector<int>> vettori_supporto(k); 
	for(int i = 0; i < k; i++) {
		std::vector<int> s(m, 0);
		vettori_supporto[i] = s; 
	}
	
	//riempimento vettori di supporto
	T root = nodiG[0]; 
	undirected_graph<T> DFS_tree = recursive_dfs(G, root);
	undirected_graph<T> C = G - DFS_tree;
	std::vector<undirected_edge<T>> archi_C = C.all_edges();
	for(int i = 0; i < k; i++) { //per ogni arco del coalbero (e quindi vettore di supporto)
		for(int j = 0; j < m; j++) { //per ogni arco di G
			if(archiG[j] == archi_C[i]) {
				vettori_supporto[i][j] = 1; 
			}
			else {
				vettori_supporto[i][j] = 0; 
			}
		}	
	}
	
	std::vector<std::vector<T>> cicli_fondamentali; 
	//vettore che conterrà la mia base di cicli fondamentali
	
	for(int i = 0; i < k; i++) {
		// --> I INDICIZZA VETTORE DI SUPPORTO SU CUI STO LAVORANDO 
		//----------------------------------------------------------------------------------
		//TROVIAMO CICLO MINIMO CUI PRODOTTO SCALARE CON S_i = 1
		//----------------------------------------------------------------------------------
		
		//CREAZIONE GRAFO AUSILIARIO
		undirected_graph<std::pair<T,int>> grafo_ausiliario; 
		//OSS: per convenzione u+ è la coppia (u,1) u- è la coppia (u,-1)
		// --> GESTISCO SEGNO ASSOCIATO AL NODO TRAMITE COPPIA
		
		for(int j = 0; j < m; j++) {
			//QUI J INDICIZZA ARCO (u,v) DI G ORIGINALE CHE STO CONSIDERANDO
			
			T u = archiG[j].from();
			T v = archiG[j].to();
			std::pair<T,int> u_più = {u,1};
			std::pair<T,int> u_meno = {u,-1};
			std::pair<T,int> v_più = {v,1};
			std::pair<T,int> v_meno = {v,-1};
			
			if(vettori_supporto[i][j] == 1) {
				//arco j-esimo di G attivo nel vettore di supporto i-esimo
				grafo_ausiliario.add_edge(u_più, v_meno); 
				grafo_ausiliario.add_edge(u_meno, v_più); 
			}
			else {
				grafo_ausiliario.add_edge(u_più, v_più); 
				grafo_ausiliario.add_edge(u_meno, v_meno); 
			}
		}
		
		//CALCOLO CICLI POTENZIALI
		std::vector<std::vector<int>> cicli_potenziali(nodiG.size(), std::vector<int>(m, 0));
		//vettore in cui salvo cicli potenziali in formato booleano
		std::vector<std::vector<T>> cammini_potenziali(nodiG.size());
		//vettore in cui salvo cicli potenziali effettivi su G (vettori sono di tipo T, non int)
		//OSS: ne trovo tanti quanti sono i nodi del grafo G
		for(int j = 0; j < n; j++) {
			//QUI J INDICIZZA NODO DI G ORIGINALE CHE STO CONSIDERANDO
			
			// calcolo cammino minimo tra v+ e v- per ogni v nodo di G
			std::vector<std::pair<T,int>> cammino; 
			//OSS: è un cammino di "coppie" perché viene fatto sul grafo ausiliario G'
			T v = nodiG[j];
			std::pair<T,int> v_più = {v,1};
			std::pair<T,int> v_meno = {v,-1};
			undirected_graph<std::pair<T,int>> Dijkstra_grafo_ausiliario = Dijkstra(grafo_ausiliario, v_più);	
			std::set<std::pair<T,int>> visitati; 
			findpath(Dijkstra_grafo_ausiliario, v_più, v_meno, cammino, visitati);
			size_t len_cammino = cammino.size();
			cammini_potenziali[j].resize(len_cammino);
			for(size_t c = 0; c < len_cammino; c++) {
				cammini_potenziali[j][c] = cammino[c].first;
			}
			
			// calcolo ciclo potenziale associato al cammino del nodo v
			std::vector<undirected_edge<T>> archi_cammino;
			archi_cammino.reserve(len_cammino);
			for(size_t c = 0; c < len_cammino - 1; c++) {
				undirected_edge<T> edge(cammino[c].first, cammino[c+1].first);
				archi_cammino.push_back(edge);
			}
			for(int h = 0; h < m; h ++) {
				//cammino lungo l -> abbiamo l-1 archi
				for(size_t c = 0; c < len_cammino - 1; c++) {
					if(archiG[h] == archi_cammino[c]) {
						cicli_potenziali[j][h] = (cicli_potenziali[j][h] + 1) % 2; 
						//incremento di 1, e faccio modulo 2
					}
				}
			}
		}
		
		//prendiamo come ciclo fondamentale quello con meno uni
		std::vector<int> ciclo_minimo = cicli_potenziali[0];
		std::vector<T> cammino_ciclo_minimo = cammini_potenziali[0];
		auto numero_minimo_uni = std::count(ciclo_minimo.begin(), ciclo_minimo.end(), 1);
		for(int j = 1; j < n; j++) {
			auto numero_uni = std::count(cicli_potenziali[j].begin(), cicli_potenziali[j].end(), 1); 
			if(numero_uni < numero_minimo_uni) {
				ciclo_minimo = cicli_potenziali[j];
				cammino_ciclo_minimo = cammini_potenziali[j];
				numero_minimo_uni = numero_uni; 
			}
		}
		
		//----------------------------------------------------------------------------------
		//----------------------------------------------------------------------------------
		cicli_fondamentali.push_back(cammino_ciclo_minimo);
		
		//aggiornamento vettori supporto successivi
		for(int j = i+1; j < k; j++) {
			if(prod_scalare_bool(ciclo_minimo, vettori_supporto[j]) == 1) {
				vettori_supporto[j] = differenza_simmetrica_bool(vettori_supporto[j], vettori_supporto[i]);
			}
		}
	}
	
	return cicli_fondamentali;
}	
