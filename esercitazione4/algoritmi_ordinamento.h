#include <vector>

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