#pragma once
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

//CLASSE RAPPRESENTA ARCO
template<typename T>
class undirected_edge {
	//arco non diretto caratterizzato unicamente da due nodi che collega: --> solo questi 
	//due attributi
		T nodeA;
		T nodeB;
	public:
		undirected_edge(T i, T j) { //costruttore user_defined -> arco tra nodi j ed i
			if (i < j) {
				nodeA = i; 
				nodeB = j; 	
			}
			else { //permessi anche archi da nodo in sè stesso
				nodeA = j; 
				nodeB = i; 
			}
		}
		
		//metodi restituiscono due nodi
		const T& from() const {
			return nodeA;
		}
		
		const T& to() const {
			return nodeB; 
		}
		
		bool operator<(const undirected_edge& other) const{
			if ((nodeA < other.nodeA) || ( (nodeA == other.nodeA) && (nodeB < other.nodeB))) {
				return true;
			}
			else {
				return false;
			}
		}
		
		bool operator==(const undirected_edge& other) const{
			if (nodeA == other.nodeA && (nodeB == other.nodeB)) {
				return true; 
			}
			else {
				return false; 
			}
		}
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const undirected_edge<T>& edge) {
//oss: qui nell'input della funzione devo specificare <T> -> siamo fuori dalla classe
	os << "(" << edge.from() << "," << edge.to() << ")";
	return os; 
}

//CLASSE RAPPRESENTA GRAFO

template<typename T> 
class undirected_graph {
	std::map<T, std::set<T>> mappa_adiacenza; 
	//per ogni nodo salvo insieme dei vicini -> uso set perché non voglio duplicati
	
	std::vector<undirected_edge<T>> vettore_archi; 
	
	public:
	//costruttore default -> inizializza mappa adiacenza vuota
	undirected_graph() { 
	}
	
	//costruttore di copia
	undirected_graph(const undirected_graph& other) {
		mappa_adiacenza = other.mappa_adiacenza; 
		vettore_archi = other.vettore_archi;
	}
	
	const std::set<T>& neighbours(const T& node) const {
		auto itor = mappa_adiacenza.find(node);
		//OSS: find restituisce iteratore, se non trova nodo restituisce iteratore all'
		//elemento succcessivo all'ultimo della mappa (quello che trovo con .end()
		
		if (itor == mappa_adiacenza.end()) {
			static const std::set<T> set_vuoto; //aggiungo static -> altrimenti 
			//set_vuoto eliminato quando termina funzione, ma voglio restituire
			//riferimento per evitare copie 
			return set_vuoto; //ritorna set vuoto se nodo non trovato
		}
		
		return itor->second; //secoond permette accedere al secondo elemento della coppia
		//(chiave,valore) cui puntava l'iteratore
		
		//APPROCCIO ALTERNATIVO: 
		//return mappa_adiacenza.at(node) programma lancia eccezione se non trova nodo
	}
	
	void add_edge(T i, T j) {
		undirected_edge<T> edge(i,j); //creo arco -> classe definita sopra
		if (mappa_adiacenza[i].count(j) == 0) {//se arco non già presente 
			//aggiorno lista adiacenza
			mappa_adiacenza[i].insert(j);
			mappa_adiacenza[j].insert(i);
			//uso operatore [] di std::map -> voglio poter creare nuovo nodo se non già 
			//presente; metodo insert -> aggiungere elemento al set dei vicini
			vettore_archi.push_back(edge);
		}
		std::sort(vettore_archi.begin(), vettore_archi.end()); //ordino vettore degli archi 
		//rispetto ordinamento della classe undirected_edge
	}
	
	const std::vector<undirected_edge<T>>& all_edges() const {
		return vettore_archi;
	}
	
	std::vector<T> all_nodes() const {
		std::vector<T> nodes;
		//OSS: oggetto nodes costruito dentro la funzione -> non posso restituire
		//riferimento, perché distrutto quando funzione termina, alternativa
		//sarebbe usare static e set come sopra, ma vector più rapido per inserire 
		//elementi: unico scopo di questo metodo
		for (const auto& itor : mappa_adiacenza) {
			nodes.push_back(itor.first); 
			//OSS: nel range_based for, itor è proprio riferimento 
			//ad elemento della mappa, non puntatore da dereferenziare
		}
		return nodes; 
	}
	
	int edge_number(const undirected_edge<T>& edge) const {
		int size = vettore_archi.size();
		for (int i = 0; i < size; i++) {
			if (vettore_archi[i] == edge) {
				return i+1;
			}
		}
		return -1; //restituisce -1 se arco non trovato
	}
	
	const undirected_edge<T>& edge_at(size_t i) {
		
		if ((i > 0) && (i <= vettore_archi.size())) {
			return vettore_archi[i-1];
		}
		return vettore_archi[0]; //se richiesto arco non esistente, restituisco
		//primo arco, suppongo che metodo chiamato con vettore_archi non vuoto
	}
	
	undirected_graph<T> operator-(const undirected_graph& other) const{
		undirected_graph<T> grafo_differenza; 
		for(size_t i = 0; i < vettore_archi.size(); i++) {
			bool presente_entrambi = false; 
			for (size_t j = 0; j < other.vettore_archi.size(); j++) {
				if (vettore_archi[i] == other.vettore_archi[j]) {
					presente_entrambi = true;
				}
			}
			
			if (! presente_entrambi) {
				grafo_differenza.add_edge(vettore_archi[i].from(), vettore_archi[i].to());
			}
		}
		
		return grafo_differenza;
	}
};