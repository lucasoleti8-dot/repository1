#include <iostream>
#include <vector>
#include <algorithm>
#include "randfiller.h"
#include "algoritmi_ordinamento.h"
#include "timecounter.h"

int main(void) {
	randfiller rf;
	timecounter tc;
	for (int k = 4; k <= 8192; k = 2*k) {
		std::cout << "DIMENSIONI VETTORE: " << k << " ";
		std::vector<int> int_v;
		int_v.resize(k);
		rf.fill(int_v, -40, 40);
		tc.tic();
		bubble_sort(int_v);
		std::cout << "SECS BUBBLESORT: " << tc.toc();
		tc.tic();
		insertion_sort(int_v);
		std::cout << " SECS INSERTIONSORT: " << tc.toc();
		tc.tic();
		selection_sort(int_v);
		std::cout << " SECS SELECTIONSORT: " << tc.toc();
		tc.tic();
		std::sort(int_v.begin(), int_v.end());
		std::cout << " SECS STANDARDSORT: " << tc.toc() << "\n";
	}
	
	//osservo che per k molto grande l'altoritmo di insertionsort è nell'ordine di 10^-5
	// standardsort di 10^-3 mentre bubblesort e selectionsort di 10^-1
	
	return 0;
}