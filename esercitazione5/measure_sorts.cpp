#include <iostream>
#include <vector>
#include <algorithm>
#include "randfiller.h"
#include "algoritmi_ordinamento.h"
#include "timecounter.h"


int main(void) {
	randfiller rf;
	timecounter tc;
	for (int k = 2; k <= 100; k ++) {
		std::cout << "DIMENSIONE : " << k << " ";
		std::vector<std::vector<int>> vecs(100); 
		
		//per ogni k (dimensione) creo 100 vettori di numeri casuali e li metto in vecs
		for (int j = 0; j < 100; j++) {
			std::vector<int> int_v(k);
			vecs[j] = int_v;
			rf.fill(vecs[j], -40, 40);
		}

		//misuro tempi facendo media tra questi 100 vettori
		tc.tic();
		for (int j = 0; j < 100; j++) {
			bubble_sort(vecs[j]);
		}
		std::cout << "SECS BUBBLESORT: " << tc.toc() / 100 << " "; 
		
		tc.tic();
		for (int j = 0; j < 100; j++) {
			selection_sort(vecs[j]);
		}
		std::cout << "SECS SELECTIONSORT: " << tc.toc() / 100 << " "; 
		
		tc.tic();
		for (int j = 0; j < 100; j++) {
			insertion_sort(vecs[j]);
		}
		std::cout << "SECS INSERTIONSORT: " << tc.toc() / 100 << " "; 
		
		tc.tic();
		for (int j = 0; j < 100; j++) {
			merge_sort(vecs[j], 0, k-1);
		}
		std::cout << "SECS MERGESORT: " << tc.toc() / 100 << " "; 
		
		tc.tic();
		for (int j = 0; j < 100; j++) {
			quick_sort(vecs[j], 0, k-1);
		} 
		std::cout << "SECS QUICKSORT: " << tc.toc() / 100 << " "; 
		
		tc.tic();
		for (int j = 0; j < 100; j++) {
			std::sort(vecs[j].begin(), vecs[j].end());
		} 
		std::cout << "SECS STANDARDSORT: " << tc.toc() / 100 << "\n"; 
		
		tc.tic();
		for (int j = 0; j < 100; j++) {
			faster_quick_sort(vecs[j], 0, k-1);
		} 
		std::cout << "SECS FASTER_QUICKSORT: " << tc.toc() / 100 << "\n"; 
		
		
	}
	return 0;
}