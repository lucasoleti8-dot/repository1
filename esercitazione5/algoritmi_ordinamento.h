#include <vector>
#include <limits>

//ALGORITMO MERGESORT

template<typename T>
void merge(std::vector<T>& A, int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;
	
	std::vector<T> L(n1);
	std::vector<T> R(n2);
	for (int i = 0; i < n1; i++) {
		L[i] = A[p + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = A[q + j + 1];
	}
	int i = 0; 
	int j = 0;
	for (int k = p; k <= r; k++) {
		// OSS: ho inizializzato vettori di supporto (L, R) senza l'elemento aggiuntivo per il valore limite 
	    // +inf proposto nello pseudocodice -> devo poter gestire anche vettori di stringhe
		// ---> devo gestire manualmente gli indici i,j
        if ((i < n1) && ((j == n2) || (L[i] <= R[j]))) {
		// se i = n1 --> ho finito tutti elementi vettore L -> vado sicuramente nell'else
		// se non ho finito vettore L ci sono due casi:
		//    - se j = n2 (ho finito vettore R) --> prendo sicuramente da L
		//    - se j != n2 (non ho finito entrambi vettori) --> faccio confronto tra L[i] ed R[j] e capisco da dove prendere
            A[k] = L[i];
            i++;
        } 
		else {
            A[k] = R[j];
            j++;
        }
	}
}

template<typename T>
void merge_sort(std::vector<T>& A, int p, int r) { // p ed r indicano sinistra e destra 
// -> identificano blocco su cui sto applicando algoritmo
	if (p < r) {
		int q = p + (r - p) / 2;
		merge_sort(A, p, q); //applico merge_sort alla prima metà
		merge_sort(A, q + 1, r); //applico merge_sort alla seconda metà
		merge(A, p, q, r); //ricomposizione
	}
} 

// ALGORITMO QUICKSORT

template<typename T>
int partition(std::vector<T>& A, int p, int r) {
	T x = A[r]; 
	//OSS: implementato scegliendo come pivot sempre l'ultimo elemento
	int i = p - 1;
	for (int j = p; j <= r-1; j++) {
		if (A[j] <= x) {
			i++; 
			std::swap(A[i], A[j]); 
		}
	}
	std::swap(A[i+1], A[r]);
	return i+1;
}

template<typename T>
void quick_sort(std::vector<T>& A, int p, int r) {
	if (p < r) {
		int q = partition(A, p, r);
		quick_sort(A, p, q-1);
		quick_sort(A, q+1, r);
	}
}

//ALGORITMO INSERTIONSORT
template<typename T>
void insertion_sort(std::vector<T>& vec) {
	for (size_t i = 1; i < vec.size(); i++) {
		T value = vec[i];
		int j = i-1; //oss: ora uso tipo int -> voglio che j possa essere anche negativo
		while ((j >= 0) && (vec[j] > value)) {
			std::swap(vec[j+1], vec[j]);
			j = j-1;
		} 
		vec[j+1] = value; 
	}
}

//ALGORITMO BUBBLESORT
template<typename T>
void bubble_sort(std::vector<T>& vec) {
	for (size_t i = 0; i < vec.size() - 1; i++) {
		for (size_t j = vec.size() - 1; j > i; j--) { //oss: metto j sempre di tipo size_t per evitare
			//warning compilatore legato alla comparazione dati di diverso tipo
			if (vec[j] < vec[j-1]) {
				std::swap(vec[j], vec[j-1]);
			}
		}
	}
}
	
//ALGORITMO SELECTIONSORT
template<typename T>
void selection_sort(std::vector<T>& vec) {
	for (size_t i = 0; i < vec.size(); i++) {
		size_t min_index = i;
		for (size_t j = i + 1; j < vec.size(); j++) {
			if (vec[j] < vec[min_index]) {
				min_index = j;
			}
		}
		std::swap(vec[i], vec[min_index]);
	}
}

// ALGORIRTMO QUICKSORT POTENZIATO PER VETTORI PICCOLE DIMENSIONI

template<typename T>
void faster_quick_sort(std::vector<T>& A, int p, int r) {
	//se vettore più lungo di 60 implemento quicksort
	if (r - p + 1 > 25) { 
		int q = partition(A, p, r);
		faster_quick_sort(A, p, q-1);
		faster_quick_sort(A, q+1, r);
	}
	//altrimenti implemento algoritmo quadratico che abbiamo visto essere più rapido:
	//l'INSERTIONSORT, ma solo sulla porzione di A tra p ed r
	else { 
		for (int i = p +1; i <= r ; i++) { //scorro vettore tra p+1 ed r
		//(devo sempre andare dal secondo all'ultimo)
		T value = A[i];
		int j = i-1; 
		while ((j >= p) && (A[j] > value)) { 
		//mi muovo a sinistra ma non superando posizione p (non devo superare posizione iniziale)
			std::swap(A[j+1], A[j]);
			j = j-1;
		} 
		A[j+1] = value; 
	}
	}
}

