#include <iostream>
#include <vector>

//VERIFICA VETTORE ORDINATO
template<typename T>
int is_sorted(const std::vector<T>& vec)
{
	if (vec.size() > 0) {
		for (size_t i = 0; i < vec.size() - 1; i++) {
			//oss size_t è tipo dato: è dimensione oggetto in memoria (-> senza segno: non può essere negativo)
			if (vec[i] > vec[i+1]) {
				return 0;
			}
		}
	}		
		
	return 1;
}